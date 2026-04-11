from typing import Dict, List
from datamodel import OrderDepth, TradingState, Order
import json

class Trader:

    def __init__(self):
        self.position_limits = {
            "EMERALDS": 80,
            "TOMATOES": 80
        }

    def run(self, state: TradingState):
        result: Dict[str, List[Order]] = {}

        ##################################### Load memory #################################
        if state.traderData:
            data = json.loads(state.traderData)
        else:
            data = {"tomato_prices": []}

        tomato_prices = data["tomato_prices"]

        for product in state.order_depths:
            order_depth: OrderDepth = state.order_depths[product]
            orders: List[Order] = []

            position = state.position.get(product, 0)
            limit = self.position_limits[product]

            if not order_depth.buy_orders or not order_depth.sell_orders:
                result[product] = orders
                continue

            best_bid = max(order_depth.buy_orders.keys())
            best_ask = min(order_depth.sell_orders.keys())

            # Slightly aggressive quoting
            buy_price = best_bid + 1   # step inside spread
            sell_price = best_ask - 1  # step inside spread

            bid_vol = order_depth.buy_orders[best_bid]
            ask_vol = -order_depth.sell_orders[best_ask]

            ################################################## MICROPRICE (better fair value)
            microprice = (best_bid * ask_vol + best_ask * bid_vol) / (bid_vol + ask_vol)
            spread = best_ask - best_bid

            ################################################### Avoid bad markets
            if spread > 5:
                result[product] = orders
                continue

            ################################################### ORDER BOOK IMBALANCE
            total_bid_vol = sum(order_depth.buy_orders.values())
            total_ask_vol = -sum(order_depth.sell_orders.values())
            imbalance = (total_bid_vol - total_ask_vol) / (total_bid_vol + total_ask_vol + 1e-6)

            #######################################################
            # EMERALDS (SAFE MARKET MAKING)
            ##################################################
            if product == "EMERALDS":

                fair_price = microprice

                # Inventory skew
                skew = position / limit
                fair_price -= skew * 3

                edge = 1.5  # minimum edge to trade

                buy_volume = min(10, limit - position)
                sell_volume = min(10, limit + position)

                # BUY: only if good price
                if best_ask < fair_price - edge and buy_volume > 0:
                    orders.append(Order(product, best_ask, buy_volume))  # take liquidity

                else:
                    # passive buy (inside spread)
                    orders.append(Order(product, best_bid + 1, buy_volume))

                # SELL: only if good price
                if best_bid > fair_price + edge and sell_volume > 0:
                    orders.append(Order(product, best_bid, -sell_volume))  # take liquidity

                else:
                    # passive sell (inside spread)
                    orders.append(Order(product, best_ask - 1, -sell_volume))

            # =========================
            # TOMATOES (PASSIVE ALPHA)
            ###############################################
            if product == "TOMATOES":

                tomato_prices.append(microprice)
                if len(tomato_prices) > 20:
                    tomato_prices.pop(0)

                if len(tomato_prices) >= 5:

                    avg_price = sum(tomato_prices) / len(tomato_prices)
                    signal = microprice - avg_price

                    skew = position / limit
                    fair_price = avg_price - skew * 2

                    edge = 2  # tomatoes need bigger edge

                    buy_volume = min(10, limit - position)
                    sell_volume = min(10, limit + position)

                    # BUY
                    if signal < -edge and buy_volume > 0:
                        orders.append(Order(product, best_ask, buy_volume))  # aggressive

                    else:
                        orders.append(Order(product, best_bid + 1, buy_volume))  # passive

                    # SELL
                    if signal > edge and sell_volume > 0:
                        orders.append(Order(product, best_bid, -sell_volume))  # aggressive

                    else:
                        orders.append(Order(product, best_ask - 1, -sell_volume))  # passive

            result[product] = orders

        traderData = json.dumps({"tomato_prices": tomato_prices})
        conversions = 0

        return result, conversions, traderData
    
