import pandas as pd
import ast
from src.mcap_filter import apply_mcap_filter
from src.sector_constraint import apply_sector_constraint


def process_portfolios(invest_df, sector_df, mcap_df):

    years = invest_df.columns[1:]

    output_rows = []

    for _, row in invest_df.iterrows():

        strat_name = row['strat_name']
        new_row = {'strat_name': strat_name + "_constrained"}

        for year in years:

            stocks = row[year]

            if pd.isna(stocks):
                new_row[year] = "[]"
                continue

            try:
                stock_list = ast.literal_eval(stocks)
            except:
                stock_list = []

            if len(stock_list) == 0:
                new_row[year] = "[]"
                continue

            # Step 1 MCAP Filter
            filtered = apply_mcap_filter(stock_list, year, mcap_df)

            # Step 2 Sector Constraint
            filtered = apply_sector_constraint(filtered, year, sector_df, mcap_df)

            new_row[year] = str(filtered)

        output_rows.append(new_row)

    return pd.DataFrame(output_rows)