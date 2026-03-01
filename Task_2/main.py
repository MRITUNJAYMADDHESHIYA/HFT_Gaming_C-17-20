from dataclasses import dataclass
import math



@dataclass
class Prediction:
    user_id: str
    asset: str
    direction: int          # +1 BUY, -1 SELL
    score_hour: float       # S_h in [0,1]
    score_adj: float        # S_adj in [0,1]
    confidence: float       # [0,1]
    volatility: float       # intraday vol estimate
    horizon_hours: float
    time_elapsed: float     # hours since opened

def is_eligible(p: Prediction, time_to_eod: float) -> bool:
    return (
        p.score_hour >= 0.75 and
        p.score_adj >= 0.60 and
        time_to_eod >= p.horizon_hours
    )

def priority_score(p: Prediction) -> float:
    return 0.7 * p.score_hour + 0.3 * p.score_adj

def decayed_priority(p: Prediction) -> float:
    decay = max(0.0, 1.0 - p.time_elapsed / p.horizon_hours)
    return priority_score(p) * decay

REPLACE_THRESHOLD = 0.10
def should_replace(new_p, existing_positions):
    weakest = min(existing_positions, key=decayed_priority)
    delta = priority_score(new_p) - decayed_priority(weakest)
    return delta >= REPLACE_THRESHOLD, weakest

#########################################################################
TOTAL_CAPITAL = 100_000
MAX_POS = 0.30
MIN_POS = 0.10

def raw_weight(p: Prediction) -> float:
    return (p.score_hour * math.sqrt(p.confidence)) / p.volatility

def allocate_capital(positions):
    weights = [raw_weight(p) for p in positions]
    total = sum(weights)

    allocations = {}
    for p, w in zip(positions, weights):
        capital = (w / total) * TOTAL_CAPITAL
        capital = min(capital, MAX_POS * TOTAL_CAPITAL)
        capital = max(capital, MIN_POS * TOTAL_CAPITAL)
        allocations[p.asset] = capital

    return allocations


####################################################
ASSET_GROUPS = {
    "SPX": "equity_index",
    "ES": "equity_index",
    "NQ": "equity_index",
    "ETHUSDT": "crypto",
    "BTCUSDT": "crypto"
}

GROUP_CAP = 0.40
def enforce_group_caps(allocations):
    group_exposure = {}

    for asset, cap in allocations.items():
        group = ASSET_GROUPS.get(asset, asset)
        group_exposure[group] = group_exposure.get(group, 0) + cap

    for group, exposure in group_exposure.items():
        if exposure > GROUP_CAP * TOTAL_CAPITAL:
            scale = (GROUP_CAP * TOTAL_CAPITAL) / exposure
            for asset in allocations:
                if ASSET_GROUPS.get(asset, asset) == group:
                    allocations[asset] *= scale

    return allocations

def resolve_conflict(existing: Prediction, new: Prediction):
    dominance = priority_score(new) / decayed_priority(existing)

    if dominance >= 1.25:
        return "REVERSE"
    elif dominance >= 1.10:
        return "CLOSE_AND_WAIT"
    else:
        return "IGNORE"
    
def select_trades(predictions, open_positions, time_to_eod):
    candidates = [p for p in predictions if is_eligible(p, time_to_eod)]
    candidates.sort(key=priority_score, reverse=True)

    for p in candidates:
        if len(open_positions) < 5:
            open_positions.append(p)
        else:
            replace, weakest = should_replace(p, open_positions)
            if replace:
                open_positions.remove(weakest)
                open_positions.append(p)

    return open_positions
