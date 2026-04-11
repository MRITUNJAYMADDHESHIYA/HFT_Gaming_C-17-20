from typing import Dict, List
from datamodel import OrderDepth, TradingState, Order
import json
import numpy as np

class Trader:

    def __init__(self):
        self.position_limits = {
            "EMERALDS": 80,
            "TOMATOES": 80
        }

    def run(self, state: TradingState):
        result: Dict[str, List[Order]] = {}

        # ================= MEMORY =================
        if state.traderData:
            data = json.loads(state.traderData)
        else:
            data = {
                "prices": {"TOMATOES": []},
                "ema": {}
            }

        prices = data["prices"]
        ema = data["ema"]

        # ================= LOOP PRODUCTS =================
        for product in state.order_depths:

            order_depth: OrderDepth = state.order_depths[product]
            orders: List[Order] = []

            position = state.position.get(product, 0)
            limit = self.position_limits[product]

            # Skip empty books
            if not order_depth.buy_orders or not order_depth.sell_orders:
                result[product] = orders
                continue

            best_bid = max(order_depth.buy_orders.keys())
            best_ask = min(order_depth.sell_orders.keys())

            bid_vol = order_depth.buy_orders[best_bid]
            ask_vol = -order_depth.sell_orders[best_ask]

            # ================= MICROPRICE =================
            microprice = (best_bid * ask_vol + best_ask * bid_vol) / (bid_vol + ask_vol)
            spread = best_ask - best_bid

            # Avoid bad markets
            if spread > 4:
                result[product] = orders
                continue

            ############################################################
            # ================= EMERALDS (HYBRID MM) ===================
            ############################################################
            if product == "EMERALDS":

                fair = microprice

                # Inventory control (moderate)
                skew = position / limit
                fair -= skew * 2

                buy_vol = min(8, limit - position)
                sell_vol = min(8, limit + position)

                # ===== AGGRESSIVE =====
                if fair > best_ask + 0.5 and buy_vol > 0:
                    orders.append(Order(product, int(best_ask), buy_vol))

                elif fair < best_bid - 0.5 and sell_vol > 0:
                    orders.append(Order(product, int(best_bid), -sell_vol))

                # ===== PASSIVE (ensure fills happen) =====
                else:
                    if buy_vol > 0:
                        orders.append(Order(product, int(best_bid + 1), max(1, buy_vol // 2)))

                    if sell_vol > 0:
                        orders.append(Order(product, int(best_ask - 1), -max(1, sell_vol // 2)))

            ############################################################
            # ================= TOMATOES (ALPHA + MM) ==================
            ############################################################
            if product == "TOMATOES":

                prices["TOMATOES"].append(microprice)
                if len(prices["TOMATOES"]) > 30:
                    prices["TOMATOES"].pop(0)

                if len(prices["TOMATOES"]) >= 10:

                    arr = np.array(prices["TOMATOES"])
                    mean = arr.mean()
                    std = arr.std() + 1e-6

                    z = (microprice - mean) / std

                    # EMA (trend detection)
                    if product not in ema:
                        ema[product] = microprice
                    else:
                        ema[product] = 0.9 * ema[product] + 0.1 * microprice

                    trend = microprice - ema[product]

                    buy_vol = min(10, limit - position)
                    sell_vol = min(10, limit + position)

                    # ===== STRONG SIGNAL → AGGRESSIVE =====
                    if z < -1.5 and buy_vol > 0:
                        orders.append(Order(product, int(best_ask), buy_vol))

                    elif z > 1.5 and sell_vol > 0:
                        orders.append(Order(product, int(best_bid), -sell_vol))

                    # ===== WEAK SIGNAL → PASSIVE =====
                    else:
                        if buy_vol > 0:
                            orders.append(Order(product, int(best_bid + 1), max(1, buy_vol // 2)))

                        if sell_vol > 0:
                            orders.append(Order(product, int(best_ask - 1), -max(1, sell_vol // 2)))

            result[product] = orders

        # ================= SAVE MEMORY =================
        traderData = json.dumps({
            "prices": prices,
            "ema": ema
        })

        return result, 0, traderData