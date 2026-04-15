from typing import Dict, List
from datamodel import OrderDepth, TradingState, Order
import json

class Trader:

    def __init__(self):
        self.position_limits = {
            "ASH_COATED_OSMIUM": 80,
            "INTARIAN_PEPPER_ROOT": 80
        }

    def run(self, state: TradingState):
        result: Dict[str, List[Order]] = {}

        ##################################### Load memory #################################
        if state.traderData:
            data = json.loads(state.traderData)
        else:
            data = {"pepper_prices": []}

        pepper_prices = data["pepper_prices"]

        for product in state.order_depths:

            if product not in self.position_limits:
                result[product] = []
                continue

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

            ################################################### TREND
            if len(pepper_prices) > 0:
                last_price = pepper_prices[-1]
                price_change = microprice - last_price
            else:
                price_change = 0

            ################################################### STORE PRICE
            if product == "INTARIAN_PEPPER_ROOT":
                pepper_prices.append(microprice)
                if len(pepper_prices) > 20:
                    pepper_prices.pop(0)

            ################################################### RISK FLAGS
            allow_buy = True
            allow_sell = True

            # 🚫 HARD STOP TRADING (very important)
            if abs(imbalance) > 0.7 or abs(price_change) > 3:
                allow_buy = False
                allow_sell = False

            # 🚫 Inventory control
            if position > limit * 0.7:
                allow_buy = False
            if position < -limit * 0.7:
                allow_sell = False

            ################################################### 🚨 FORCED EXIT (KEY FIX)
            if position > limit * 0.5:
                orders.append(Order(product, best_bid, -min(20, position)))
                result[product] = orders
                continue

            if position < -limit * 0.5:
                orders.append(Order(product, best_ask, min(20, -position)))
                result[product] = orders
                continue

            ################################################### FAIR PRICE
            fair_price = microprice

            skew = position / limit
            fair_price -= skew * 1.5

            # 🔥 stronger imbalance impact
            fair_price += imbalance * 3.0

            ################################################### SIZE CONTROL
            risk_factor = 1 - min(abs(imbalance), 0.8)

            buy_volume = max(0, int(min(12, (limit - position) * risk_factor)))
            sell_volume = max(0, int(min(12, (limit + position) * risk_factor)))

            ###################################################
            # ASH_COATED_OSMIUM (market making)
            ###################################################
            if product == "ASH_COATED_OSMIUM":

                edge = max(1, spread / 2)

                # ✅ Aggressive trades
                if allow_buy and best_ask < fair_price and buy_volume > 0:
                    orders.append(Order(product, best_ask, buy_volume))

                if allow_sell and best_bid > fair_price and sell_volume > 0:
                    orders.append(Order(product, best_bid, -sell_volume))

                # ✅ Passive only in safe conditions
                if abs(imbalance) < 0.3 and abs(price_change) < 2:

                    bid_price = best_bid + 1
                    ask_price = best_ask - 1

                    if imbalance > 0.3:
                        bid_price += 1
                    if imbalance < -0.3:
                        ask_price -= 1

                    if buy_volume > 0:
                        orders.append(Order(product, bid_price, buy_volume))

                    if sell_volume > 0:
                        orders.append(Order(product, ask_price, -sell_volume))

            ###################################################
            # INTARIAN_PEPPER_ROOT (mean reversion)
            ###################################################
            if product == "INTARIAN_PEPPER_ROOT":

                if len(pepper_prices) >= 5:

                    avg_price = sum(pepper_prices) / len(pepper_prices)
                    signal = microprice - avg_price

                    fair_price = avg_price - skew * 1.2
                    fair_price += imbalance * 3.0

                    edge = max(2, spread / 2)

                    # ✅ Aggressive trades
                    if allow_buy and (best_ask < fair_price or signal < -edge) and buy_volume > 0:
                        orders.append(Order(product, best_ask, buy_volume))

                    if allow_sell and (best_bid > fair_price or signal > edge) and sell_volume > 0:
                        orders.append(Order(product, best_bid, -sell_volume))

                    # ✅ Passive only when stable
                    if abs(imbalance) < 0.3 and abs(price_change) < 2:

                        bid_price = best_bid + 1
                        ask_price = best_ask - 1

                        if buy_volume > 0:
                            orders.append(Order(product, bid_price, buy_volume))

                        if sell_volume > 0:
                            orders.append(Order(product, ask_price, -sell_volume))

            result[product] = orders

        traderData = json.dumps({"pepper_prices": pepper_prices})
        conversions = 0

        return result, conversions, traderData