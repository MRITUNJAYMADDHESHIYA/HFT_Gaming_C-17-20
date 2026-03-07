import pandas as pd
from collections import Counter
from groq import Groq

####################### Groq api ####################################################
# i am already remove my api
client = Groq(api_key="")

def explain_portfolio(strategy, year, portfolio, sector_df, mcap_df):

    year = str(year)

    ################ Sector ################
    sector_map = sector_df.set_index("CO_NAME")["Sector"].to_dict()

    sectors = []
    for stock in portfolio:
        sector = sector_map.get(stock, "Unknown")
        sectors.append(sector)

    sector_count = Counter(sectors)
    sector_text = "\n".join([f"{k}: {v}" for k, v in sector_count.items()])


    ################ Market Cap ################
    mcap_map = mcap_df.set_index("CO_NAME")[year].to_dict()

    mcaps = []
    for stock in portfolio:
        mcap = mcap_map.get(stock, None)
        if pd.notna(mcap):
            mcaps.append(mcap)

    if mcaps:
        avg_mcap = sum(mcaps) / len(mcaps)
        max_mcap = max(mcaps)
        min_mcap = min(mcaps)
    else:
        avg_mcap = max_mcap = min_mcap = "No data"


    ################ Investment Rules ################
    #rules_text = "\n".join(rules_df.astype(str).agg(" : ".join, axis=1))
    # rules_text = rules_df.head(10).to_string(index=False)
    
    ################ Prompt ################
    prompt = f"""
You are a portfolio analysis assistant.

# Reference Investment Rules:
# rules_text

Strategy: {strategy}
Year: {year}

Portfolio Stocks:
{portfolio}

Sector Distribution:
{sector_text}

Market Cap Statistics:
Average MCap: {avg_mcap}
Maximum MCap: {max_mcap}
Minimum MCap: {min_mcap}

Tasks:
1. Sector concentration observation
2. Market capitalization observation
3. Brief portfolio risk commentary

Strict Instructions:
- Do NOT infer missing data
- Do NOT invent numbers
- Only use the data provided
"""


    ################ LLM Call ################
    response = client.chat.completions.create(
        model="llama-3.1-8b-instant",
        messages=[
            {"role": "user", "content": prompt}
        ],
        temperature=0.3
    )

    return response.choices[0].message.content


################ Run ################
if __name__ == "__main__":

    portfolio = [
        "Apollo Tyres",
        "Aruna Hotels",
        "Ashok Leyland"
    ]

    sector_df = pd.read_csv("C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/Portfolio_Constraint/data/assignment_sector_data.csv")
    mcap_df = pd.read_csv("C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/Portfolio_Constraint/data/assignment_mcap.csv")
    # rules_df = pd.read_csv("C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/Portfolio_Constraint/data/assignment_investment_rules.csv")

    result = explain_portfolio(
        strategy="Momentum",
        year=2022,
        portfolio=portfolio,
        sector_df=sector_df,
        mcap_df=mcap_df,
        # rules_df=rules_df
    )

    print(result)

#### Due to large amount of assignment_investment_rules.csv
#### I am not calling this file.
#### I will say hard coded
