import pandas as pd
import os
import ast
from src.portfolio_processor import process_portfolios

INVEST_FILE = "C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/Portfolio_Constraint/data/assignment_investment_rules.csv"
SECTOR_FILE = "C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/Portfolio_Constraint/data/assignment_sector_data.csv"
MCAP_FILE = "C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/Portfolio_Constraint/data/assignment_mcap.csv"

OUTPUT_FILE = "output/output.csv"


def main():

    invest_df = pd.read_csv(INVEST_FILE)
    sector_df = pd.read_csv(SECTOR_FILE)
    mcap_df = pd.read_csv(MCAP_FILE)

    result_df = process_portfolios(invest_df, sector_df, mcap_df)

    os.makedirs("output", exist_ok=True)
    result_df.to_csv(OUTPUT_FILE, index=False)

    print("Portfolio constraints applied successfully.")
    print("Output saved to:", OUTPUT_FILE)


if __name__ == "__main__":
    main()