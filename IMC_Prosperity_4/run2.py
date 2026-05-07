from typing import Dict, List
from datamodel import OrderDepth, TradingState, Order
import json
import numpy as np

class Trader:

    def __init__(self):
        self.position_limits = {
            "ASH_COATED_OSMIUM": 80,
            "INTARIAN_PEPPER_ROOT": 80
        }

    def run(self, state: TradingState):
        result: Dict[str, List[Order]] = {}

        ################ LOAD MEMORY ################
        if state.traderData:
            data = json.loads(state.traderData)
        else:
            data = {"prices": {}}

        prices = data["prices"]

        ############################################################
        for product in state.order_depths:

            if product not in self.position_limits:
                result[product] = []
                continue

            if product not in prices:
                prices[product] = []

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

            ################ MICROPRICE ################
            microprice = (best_bid * ask_vol + best_ask * bid_vol) / (bid_vol + ask_vol)
            spread = best_ask - best_bid

            ################ STORE PRICE ################
            prices[product].append(microprice)
            if len(prices[product]) > 30:
                prices[product].pop(0)

            if len(prices[product]) < 10:
                result[product] = orders
                continue

            arr = np.array(prices[product])

            ################ FEATURES ################
            trend = arr[-1] - arr[0]
            vol = np.std(arr)

            total_bid = sum(order_depth.buy_orders.values())
            total_ask = -sum(order_depth.sell_orders.values())
            imbalance = (total_bid - total_ask) / (total_bid + total_ask + 1e-6)

            ################ RISK CONTROL ################
            if position > limit * 0.85:
                orders.append(Order(product, best_bid, -20))
                result[product] = orders
                continue

            if position < -limit * 0.85:
                orders.append(Order(product, best_ask, 20))
                result[product] = orders
                continue

            ###########################################################
            # 🚀 TREND MODE (NEW)
            ###########################################################
            if abs(trend) > 5 and vol > 2:
                
                #size = int(min(8, abs(trend)))

                if trend > 0 and position < limit:
                    orders.append(Order(product, best_ask, min(15, limit - position)))

                elif trend < 0 and position > -limit:
                    orders.append(Order(product, best_bid, -min(15, limit + position)))

                result[product] = orders
                continue

            ###########################################################
            # 🟢 ASH_COATED_OSMIUM → MARKET MAKING
            ###########################################################
            if product == "ASH_COATED_OSMIUM":

                fair_price = np.mean(arr)

                skew = position / limit
                fair_price -= skew * 1.5
                fair_price += imbalance * 2.0

                buy_volume = min(10, limit - position)
                sell_volume = min(10, limit + position)

                # Aggressive
                if best_ask < fair_price and buy_volume > 0:
                    orders.append(Order(product, best_ask, buy_volume))

                if best_bid > fair_price and sell_volume > 0:
                    orders.append(Order(product, best_bid, -sell_volume))

                # Passive (only in low vol)
                if vol < 3:
                    orders.append(Order(product, best_bid + 1, buy_volume))
                    orders.append(Order(product, best_ask - 1, -sell_volume))


            ###########################################################
            # 🔵 INTARIAN_PEPPER_ROOT → MEAN REVERSION
            ###########################################################
            elif product == "INTARIAN_PEPPER_ROOT":

                fair_price = np.mean(arr)

                skew = position / limit
                fair_price -= skew * 1.2
                fair_price += imbalance * 2.5

                edge = max(3, spread)

                buy_volume = min(12, limit - position)
                sell_volume = min(12, limit + position)

                # Aggressive
                if best_ask < fair_price - edge:
                    orders.append(Order(product, best_ask, buy_volume))

                if best_bid > fair_price + edge:
                    orders.append(Order(product, best_bid, -sell_volume))

                # Passive
                if vol < 3:
                    orders.append(Order(product, best_bid + 1, buy_volume))
                    orders.append(Order(product, best_ask - 1, -sell_volume))

            ###########################################################
            result[product] = orders

        ################ SAVE ################
        traderData = json.dumps({"prices": prices})
        conversions = 0

        return result, conversions, traderData

        