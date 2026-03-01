#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
#include<chrono>
#include<ctime>

//15 and 9 ema for buy and sell
double calculateEMA(const std::vector<double>& prices, int period){
    if(prices.size() < period) return 0.0;

    double k = 2.0/(period + 1);
    double ema = prices[0];
    for(size_t i=1; i<prices.size(); ++i){
        ema = prices[i] * k + ema * (1-k);
    }
    return ema;
}

struct Trade{
    std::string type; //buy or sell
    double      entry;
    double      sl;
    double      tp;
    bool        active;
};


//time filter(trade in 19:15-21:00 IST, mon-fri)
bool isTradeAllowed(const std::string& timeStr){
    //time formate "YYYY-MM-DD HH:MM:SS"
    int hour   = std::stoi(timeStr.substr(11, 2));
    int minute = std::stoi(timeStr.substr(14, 2));

    //convert to total mintue
    int currentMinutes = hour * 60 + minute;
    int blockStart     = 19*60 + 15;
    int blockEnd       = 21*60;

    //if within block return true
    return (currentMinutes >= blockStart && currentMinutes <= blockEnd);
}

//read csv
std::vector<double> readClosePrices(const std::string& filename){
    std::vector<double> closes;
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr<<"Error: could not open file "<<filename <<"\n";
        return closes;
    }

    std::string line;
    getline(file, line);//skip header
    while(getline(file, line)){
        std::stringstream ss(line);
        std::string time, open, high, low, close, volume;
        getline(ss, time, ',');
        getline(ss, open, ',');
        getline(ss, high, ',');
        getline(ss, low, ',');
        getline(ss, close, ',');
        getline(ss, volume, ',');

        if(!close.empty()){
            closes.push_back(std::stod(close));
        }
    }
    return closes;
}


void runBacktest(const std::vector<double>& closes){
    int shortPeriod = 20;
    int longPeriod  = 50;
    Trade trade{"", 0, 0, 0, false};

    double risk = 100; //pips
    double reward = 2*risk;

    for(size_t i = longPeriod; i<closes.size(); ++i){
        std::vector<double> shortSlice(closes.begin()+i-shortPeriod, closes.begin()+i);
        std::vector<double> longSlice(closes.begin() + i - longPeriod, closes.begin() + i);

        double emaShort = calculateEMA(shortSlice, shortPeriod);
        double emaLong = calculateEMA(longSlice, longPeriod);
        double price = closes[i];

        if (trade.active) {
            if (trade.type == "BUY" && (price >= trade.tp || price <= trade.sl)) {
                std::cout << "[CLOSE BUY] at " << price << "\n";
                trade.active = false;
            }
            else if (trade.type == "SELL" && (price <= trade.tp || price >= trade.sl)) {
                std::cout << "[CLOSE SELL] at " << price << "\n";
                trade.active = false;
            }
            continue;
        }

        // Entry logic
        if (emaShort > emaLong) {
            trade = {"BUY", price, price - risk, price + reward, true};
            std::cout << "[BUY] Entry: " << trade.entry << " SL: " << trade.sl << " TP: " << trade.tp << "\n";
        }
        else if (emaShort < emaLong) {
            trade = {"SELL", price, price + risk, price - reward, true};
            std::cout << "[SELL] Entry: " << trade.entry << " SL: " << trade.sl << " TP: " << trade.tp << "\n";
        }
    }
}

int main() {
    std::string filename = "C:/Users/Mritunjay Maddhesiya/OneDrive/Desktop/C++HFT/DATA/XAUUSDm_5m.csv"; // <-- your CSV file path
    auto closes = readClosePrices(filename);

    if (closes.empty()) {
        std::cerr << "No data found.\n";
        return 1;
    }

    runBacktest(closes);
    return 0;
}