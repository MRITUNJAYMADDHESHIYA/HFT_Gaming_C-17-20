# from typing import Dict, List
# from datamodel import OrderDepth, TradingState, Order
# import json
# import numpy as np

# class Trader:

#     def __init__(self):
#         self.position_limits = {
#             "ASH_COATED_OSMIUM": 80,
#             "INTARIAN_PEPPER_ROOT": 80
#         }

#     def run(self, state: TradingState):
#         result: Dict[str, List[Order]] = {}

#         ################ LOAD MEMORY ################
#         if state.traderData:
#             data = json.loads(state.traderData)
#         else:
#             data = {"prices": {}, "entry_price": {}}

#         prices = data["prices"]
#         entry_price = data["entry_price"]

#         ############################################################
#         for product in state.order_depths:

#             if product not in self.position_limits:
#                 result[product] = []
#                 continue

#             if product not in prices:
#                 prices[product] = []

#             order_depth: OrderDepth = state.order_depths[product]
#             orders: List[Order] = []

#             position = state.position.get(product, 0)
#             limit = self.position_limits[product]

#             if not order_depth.buy_orders or not order_depth.sell_orders:
#                 result[product] = orders
#                 continue

#             best_bid = max(order_depth.buy_orders.keys())
#             best_ask = min(order_depth.sell_orders.keys())

#             bid_vol = order_depth.buy_orders[best_bid]
#             ask_vol = -order_depth.sell_orders[best_ask]

#             ################ MICROPRICE ################
#             microprice = (best_bid * ask_vol + best_ask * bid_vol) / (bid_vol + ask_vol)
#             spread = best_ask - best_bid
#             mid_price = (best_bid + best_ask) / 2

#             ################ STORE PRICE ################
#             prices[product].append(microprice)
#             if len(prices[product]) > 30:
#                 prices[product].pop(0)

#             if len(prices[product]) < 10:
#                 result[product] = orders
#                 continue

#             arr = np.array(prices[product])

#             ################ FEATURES ################
#             short_trend = arr[-1] - arr[-5]
#             long_trend = arr[-1] - arr[0]
#             vol = np.std(arr)

#             total_bid = sum(order_depth.buy_orders.values())
#             total_ask = -sum(order_depth.sell_orders.values())
#             imbalance = (total_bid - total_ask) / (total_bid + total_ask + 1e-6)

#             is_trending = abs(short_trend) > 2 or abs(long_trend) > 4

#             ################ ENTRY PRICE TRACK ################
#             if product not in entry_price:
#                 entry_price[product] = mid_price

#             entry = entry_price[product]
#             unrealized = (mid_price - entry) * position

#             ################ STOP LOSS ################
#             if unrealized < -200:
#                 if position > 0:
#                     orders.append(Order(product, best_bid, -position))
#                 elif position < 0:
#                     orders.append(Order(product, best_ask, -position))
#                 result[product] = orders
#                 continue

#             ################ HARD POSITION CONTROL ################
#             if position > limit * 0.85:
#                 orders.append(Order(product, best_bid, -20))
#                 result[product] = orders
#                 continue

#             if position < -limit * 0.85:
#                 orders.append(Order(product, best_ask, 20))
#                 result[product] = orders
#                 continue

#             ################ FAIR PRICE ################
#             fair_price = 0.7 * arr[-1] + 0.3 * np.mean(arr)

#             ################ INVENTORY SKEW ################
#             skew = position / limit
#             fair_price -= skew * 2.0

#             ################ IMBALANCE ADJUST ################
#             fair_price += imbalance * 2.0

#             ################ SOFT INVENTORY CONTROL ################
#             if position > 30:
#                 fair_price -= 2
#             if position < -30:
#                 fair_price += 2

#             ################ DYNAMIC SIZE ################
#             size = 12
#             if vol > 4:
#                 size = 6
#             if abs(imbalance) > 0.5:
#                 size = 5

#             ###########################################################
#             # 🚀 TREND MODE
#             ###########################################################
#             if is_trending:

#                 if short_trend > 0 and position < limit:
#                     orders.append(Order(product, best_ask, min(size, limit - position)))

#                 elif short_trend < 0 and position > -limit:
#                     orders.append(Order(product, best_bid, -min(size, limit + position)))

#                 result[product] = orders
#                 continue

#             ###########################################################
#             # 🟢 ASH_COATED_OSMIUM → MARKET MAKING
#             ###########################################################
#             if product == "ASH_COATED_OSMIUM":

#                 buy_volume = min(size, limit - position)
#                 sell_volume = min(size, limit + position)

#                 # Aggressive
#                 if best_ask < fair_price and buy_volume > 0:
#                     orders.append(Order(product, best_ask, buy_volume))

#                 if best_bid > fair_price and sell_volume > 0:
#                     orders.append(Order(product, best_bid, -sell_volume))

#                 # Passive
#                 if vol < 3:
#                     orders.append(Order(product, best_bid + 1, buy_volume))
#                     orders.append(Order(product, best_ask - 1, -sell_volume))

#             ###########################################################
#             # 🔵 INTARIAN_PEPPER_ROOT → MEAN REVERSION
#             ###########################################################
#             elif product == "INTARIAN_PEPPER_ROOT":

#                 edge = max(3, spread)

#                 buy_volume = min(size, limit - position)
#                 sell_volume = min(size, limit + position)

#                 # Aggressive
#                 if best_ask < fair_price - edge:
#                     orders.append(Order(product, best_ask, buy_volume))

#                 if best_bid > fair_price + edge:
#                     orders.append(Order(product, best_bid, -sell_volume))

#                 # Passive
#                 if vol < 3:
#                     orders.append(Order(product, best_bid + 1, buy_volume))
#                     orders.append(Order(product, best_ask - 1, -sell_volume))

#             ###########################################################
#             result[product] = orders

#         ################ SAVE ################
#         traderData = json.dumps({
#             "prices": prices,
#             "entry_price": entry_price
#         })
#         conversions = 0

#         return result, conversions, traderData




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
            data = {"prices": {}, "entry_price": {}, "cooldown": {}}

        prices = data["prices"]
        entry_price = data["entry_price"]
        cooldown = data["cooldown"]

        ############################################################
        for product in state.order_depths:

            if product not in self.position_limits:
                result[product] = []
                continue

            if product not in prices:
                prices[product] = []

            if product not in cooldown:
                cooldown[product] = 0

            order_depth: OrderDepth = state.order_depths[product]
            orders: List[Order] = []

            position = state.position.get(product, 0)
            limit = self.position_limits[product]

            # ⛔ Cooldown (prevents revenge trading)
            if cooldown[product] > 0:
                cooldown[product] -= 1
                result[product] = orders
                continue

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
            mid_price = (best_bid + best_ask) / 2

            ################ STORE PRICE ################
            prices[product].append(microprice)
            if len(prices[product]) > 30:
                prices[product].pop(0)

            if len(prices[product]) < 10:
                result[product] = orders
                continue

            arr = np.array(prices[product])

            ################ FEATURES ################
            short_trend = arr[-1] - arr[-5]
            long_trend = arr[-1] - arr[0]
            vol = np.std(arr)

            total_bid = sum(order_depth.buy_orders.values())
            total_ask = -sum(order_depth.sell_orders.values())
            imbalance = (total_bid - total_ask) / (total_bid + total_ask + 1e-6)

            is_trending = abs(short_trend) > 2 or abs(long_trend) > 4

            ################ ENTRY TRACK ################
            if product not in entry_price:
                entry_price[product] = mid_price

            entry = entry_price[product]
            unrealized = (mid_price - entry) * position

            ################ STOP LOSS ################
            if unrealized < -500:
                if position > 0:
                    orders.append(Order(product, best_bid, -position))
                elif position < 0:
                    orders.append(Order(product, best_ask, -position))

                cooldown[product] = 5  # prevent re-entry
                result[product] = orders
                continue

            ################ HARD POSITION CONTROL ################
            if position > limit * 0.85:
                orders.append(Order(product, best_bid, -20))
                result[product] = orders
                continue

            if position < -limit * 0.85:
                orders.append(Order(product, best_ask, 20))
                result[product] = orders
                continue

            ################ FAIR PRICE ################
            fair_price = microprice

            ################ INVENTORY SKEW ################
            skew = position / limit
            fair_price -= skew * 2.0

            ################ IMBALANCE ADJUST ################
            fair_price += imbalance * 1.5

            ################ NO-TRADE ZONE ################
            if abs(fair_price - mid_price) < 1:
                result[product] = orders
                continue

            ################ SIZE ################
            size = 8
            if vol > 4:
                size = 5
            if abs(imbalance) > 0.5:
                size = 4

            ###########################################################
            # 🚀 TREND MODE (SELECTIVE)
            ###########################################################
            if is_trending:

                if short_trend > 2 and imbalance > 0.2 and spread <= 3:
                    orders.append(Order(product, best_ask, min(6, limit - position)))

                elif short_trend < -2 and imbalance < -0.2 and spread <= 3:
                    orders.append(Order(product, best_bid, -min(6, limit + position)))

                result[product] = orders
                continue

            ###########################################################
            # 🟢 ASH_COATED_OSMIUM → MARKET MAKING
            ###########################################################
            if product == "ASH_COATED_OSMIUM":

                buy_volume = min(size, limit - position)
                sell_volume = min(size, limit + position)

                if best_ask < fair_price and buy_volume > 0:
                    orders.append(Order(product, best_ask, buy_volume))

                if best_bid > fair_price and sell_volume > 0:
                    orders.append(Order(product, best_bid, -sell_volume))

                if vol < 3:
                    orders.append(Order(product, best_bid + 1, buy_volume))
                    orders.append(Order(product, best_ask - 1, -sell_volume))

            ###########################################################
            # 🔵 INTARIAN_PEPPER_ROOT → MEAN REVERSION
            ###########################################################
            elif product == "INTARIAN_PEPPER_ROOT":

                edge = max(3, spread)

                buy_volume = min(size, limit - position)
                sell_volume = min(size, limit + position)

                if best_ask < fair_price - edge:
                    orders.append(Order(product, best_ask, buy_volume))

                if best_bid > fair_price + edge:
                    orders.append(Order(product, best_bid, -sell_volume))

                if vol < 3:
                    orders.append(Order(product, best_bid + 1, buy_volume))
                    orders.append(Order(product, best_ask - 1, -sell_volume))

            ###########################################################
            result[product] = orders

        ################ SAVE ################
        traderData = json.dumps({
            "prices": prices,
            "entry_price": entry_price,
            "cooldown": cooldown
        })
        conversions = 0

        return result, conversions, traderData

