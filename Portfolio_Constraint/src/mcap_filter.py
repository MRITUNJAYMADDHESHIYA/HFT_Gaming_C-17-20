import pandas as pd


def apply_mcap_filter(portfolio, year, mcap_df):

    if year not in mcap_df.columns:
        return []

    year_mcap = mcap_df[['CO_NAME', year]].dropna()

    year_mcap = year_mcap.sort_values(by=year, ascending=False)

    year_mcap['rank'] = range(1, len(year_mcap) + 1)

    cutoff = int(len(year_mcap) * 0.8)

    allowed = set(year_mcap.iloc[:cutoff]['CO_NAME'])

    filtered = []

    for stock in portfolio:

        if stock not in allowed:
            continue

        mcap_value = year_mcap.loc[year_mcap['CO_NAME'] == stock, year]

        if mcap_value.empty:
            continue

        filtered.append(stock)

    return filtered