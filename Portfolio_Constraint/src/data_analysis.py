import pandas as pd

INVEST_FILE = "C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/Portfolio_Constraint/data/assignment_investment_rules.csv"
SECTOR_FILE = "C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/Portfolio_Constraint/data/assignment_sector_data.csv"
MCAP_FILE = "C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/Portfolio_Constraint/data/assignment_mcap.csv"

invest_df = pd.read_csv(INVEST_FILE)
sector_df = pd.read_csv(SECTOR_FILE)
mcap_df = pd.read_csv(MCAP_FILE)

print(sector_df.columns)
print(sector_df.head())