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

            bid_vol = order_depth.buy_orders[best_bid]
            ask_vol = -order_depth.sell_orders[best_ask]

            ################################################## MICROPRICE
            microprice = (best_bid * ask_vol + best_ask * bid_vol) / (bid_vol + ask_vol)
            spread = best_ask - best_bid

            ################################################### IMBALANCE
            total_bid_vol = sum(order_depth.buy_orders.values())
            total_ask_vol = -sum(order_depth.sell_orders.values())
            imbalance = (total_bid_vol - total_ask_vol) / (total_bid_vol + total_ask_vol + 1e-6)

            ################################################### TREND DETECTION
            if len(tomato_prices) > 0:
                last_price = tomato_prices[-1]
                price_change = microprice - last_price
            else:
                price_change = 0

            ################################################### CONTROL FLAGS
            allow_buy = True
            allow_sell = True

            # Keep your original protections (DON'T OVERDO)
            if price_change < -2:
                allow_buy = False
            if price_change > 2:
                allow_sell = False

            if imbalance > 0.6:
                allow_sell = False
            if imbalance < -0.6:
                allow_buy = False

            if position > limit * 0.7:
                allow_buy = False
            if position < -limit * 0.7:
                allow_sell = False

            #######################################################
            # EMERALDS
            #######################################################
            if product == "EMERALDS":

                fair_price = microprice
                skew = position / limit

                fair_price -= skew * 1.2
                fair_price += imbalance * 1.5

                buy_volume = min(12, limit - position)
                sell_volume = min(12, limit + position)

                ###################################################
                # 🔥 SMALL EDGE IMPROVEMENT (NOT TOO STRICT)
                ###################################################
                if allow_buy and best_ask <= fair_price + 0.5:
                    orders.append(Order(product, best_ask, buy_volume))

                if allow_sell and best_bid >= fair_price - 0.5:
                    orders.append(Order(product, best_bid, -sell_volume))

                ###################################################
                # 🔥 INVENTORY MONETIZATION (BIG BOOST)
                ###################################################
                if position > 0 and best_bid > microprice:
                    orders.append(Order(product, best_bid, -min(6, position)))

                if position < 0 and best_ask < microprice:
                    orders.append(Order(product, best_ask, min(6, -position)))

                ###################################################
                # PASSIVE (SLIGHTLY SMARTER)
                ###################################################
                bid_price = best_bid + 1
                ask_price = best_ask - 1

                if imbalance > 0.3:
                    bid_price += 1
                elif imbalance < -0.3:
                    ask_price -= 1

                if allow_buy and buy_volume > 0:
                    orders.append(Order(product, bid_price, buy_volume))

                if allow_sell and sell_volume > 0:
                    orders.append(Order(product, ask_price, -sell_volume))

            #######################################################
            # TOMATOES
            #######################################################
            if product == "TOMATOES":

                tomato_prices.append(microprice)
                if len(tomato_prices) > 20:
                    tomato_prices.pop(0)

                if len(tomato_prices) >= 5:

                    avg_price = sum(tomato_prices) / len(tomato_prices)
                    signal = microprice - avg_price

                    skew = position / limit
                    fair_price = avg_price - skew * 1.0
                    fair_price += imbalance * 1.5

                    buy_volume = min(12, limit - position)
                    sell_volume = min(12, limit + position)

                    ###################################################
                    # 🔥 KEEP AGGRESSIVE BUT SLIGHTLY SMARTER
                    ###################################################
                    if allow_buy and (best_ask <= fair_price + 0.5 or signal < -2):
                        orders.append(Order(product, best_ask, buy_volume))

                    if allow_sell and (best_bid >= fair_price - 0.5 or signal > 2):
                        orders.append(Order(product, best_bid, -sell_volume))

                    ###################################################
                    # 🔥 INVENTORY EXIT
                    ###################################################
                    if position > 0 and best_bid > microprice:
                        orders.append(Order(product, best_bid, -min(6, position)))

                    if position < 0 and best_ask < microprice:
                        orders.append(Order(product, best_ask, min(6, -position)))

                    ###################################################
                    # PASSIVE
                    ###################################################
                    bid_price = best_bid + 1
                    ask_price = best_ask - 1

                    if imbalance > 0.3:
                        bid_price += 1
                    elif imbalance < -0.3:
                        ask_price -= 1

                    if allow_buy and buy_volume > 0:
                        orders.append(Order(product, bid_price, buy_volume))

                    if allow_sell and sell_volume > 0:
                        orders.append(Order(product, ask_price, -sell_volume))

            result[product] = orders

        traderData = json.dumps({"tomato_prices": tomato_prices})
        conversions = 0

        return result, conversions, traderData