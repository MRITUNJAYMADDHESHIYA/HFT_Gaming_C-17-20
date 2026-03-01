#include<bits/stdc++.h>
using namespace std;

// vector<vector<double>> ticksizes(vector<vector<double>> raw) {
//     vector<vector<double>> result;
    
//     // Sort raw data by start price and remove duplicates
//     sort(raw.begin(), raw.end());
//     raw.erase(unique(raw.begin(), raw.end()), raw.end());
    
//     // Process raw data into rules
//     vector<pair<double, double>> rules;
//     for (const auto& row : raw) {
//         if (rules.empty() || row[2] != rules.back().second) {
//             rules.push_back({row[0], row[2]});
//         }
//     }
    
//     // Create result with lower bounds and tick sizes
//     for (const auto& rule : rules) {
//         result.push_back({rule.first, rule.second});
//     }
    
//     return result;
// }

vector<vector<double>> ticksizes(vector<vector<double>> raw) {
    // Sort raw data by start price and remove duplicates
    sort(raw.begin(), raw.end());
    raw.erase(unique(raw.begin(), raw.end()), raw.end());
    
    // Process raw data into rules
    vector<pair<double, double>> rules;
    for (const auto& row : raw) {
        if (rules.empty() || row[2] != rules.back().second) {
            rules.push_back({row[0], row[2]});
        }
    }
    
    // Extract prices from the raw data
    vector<double> prices;
    for (const auto& row : raw) {
        prices.push_back(row[0]);
        prices.push_back(row[1]);
    }
    sort(prices.begin(), prices.end());
    prices.erase(unique(prices.begin(), prices.end()), prices.end());
    
    vector<vector<double>> result;
    
    // Calculate next tick for each price
    for (double price : prices) {
        auto it = upper_bound(rules.begin(), rules.end(), price,
                              [](double p, const pair<double, double>& rule) {
                                  return p < rule.first;
                              });
        
        if (it != rules.begin()) --it;
        
        double tick_size = it->second;
        double next_price = ceil(price / tick_size) * tick_size;
        
        if (next_price <= price) next_price += tick_size;
        
        result.push_back({price, next_price});
    }
    
    return result;
}

int main(){
    // Sample input
    vector<vector<double>> raw_input = {
        {0.0, 0.1, 0.01},
        {0.1, 0.5, 0.02},
        {0.5, 1.0, 0.02},
        {1.0, 10.0, 1.0},
        {10.0, 50.0, 1.0},
        {50.0, 0.3, 1.0}
    };

    // Function call
    vector<vector<double>> result = ticksizes(raw_input);

    // Expected output
    // {{0.0, 0.01},
    //  {0.1, 0.02},
    //  {1.0, 1.0},
    //  {50.0, 2.0}}

    // Print the result
    cout << "Output:" << endl;
    for (const auto& row : result) {
        cout << "{" << row[0] << ", " << row[1] << "}" << endl;
    }
    return 0;
}