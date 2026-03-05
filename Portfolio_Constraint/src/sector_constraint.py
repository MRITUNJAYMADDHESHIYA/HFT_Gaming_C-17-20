import pandas as pd


def apply_sector_constraint(portfolio, year, sector_df, mcap_df):

    if len(portfolio) == 0:
        return []

    sector_map = sector_df.set_index('CO_NAME')['Sector'].to_dict()

    sector_buckets = {}

    for stock in portfolio:

        sector = sector_map.get(stock, "Unknown")

        if pd.isna(sector):
            sector = "Unknown"

        sector_buckets.setdefault(sector, []).append(stock)

    max_allowed = int(len(portfolio) * 0.25)

    final_portfolio = []

    for sector, stocks in sector_buckets.items():

        if len(stocks) <= max_allowed:
            final_portfolio.extend(stocks)
            continue

        mcap_vals = mcap_df[mcap_df['CO_NAME'].isin(stocks)][['CO_NAME', year]].dropna()

        mcap_vals = mcap_vals.sort_values(by=year, ascending=False)

        kept = list(mcap_vals.head(max_allowed)['CO_NAME'])

        final_portfolio.extend(kept)

    return final_portfolio