#include<iostream>
#include<vector>

struct Candle{
    double open;
    double high;
    double low;
    double close;
};

std::vector<bool> BullishEngulfing(const std::vector<Candle>& bars){
    size_t n = bats.size();
    std::vector<bool> ans(n, false);

    if(n<2) return ans;
    bool flag = false;  //true when < and > instead of <= and >= (require strict body engulfing)

    for(size_t i=1; i<n; ++i){
        const Candle &prev = bars[i-1];
        const Candle &curr = bars[i];

        //prev berish and current bullish
        if(!(prev.close < prev.open)) continue;
        if(!(curr.close > curr.open)) continue;

        if(flag){
            if(curr.open < prev.close && curr.close > prev.open){
                ans[i] = true;
            }
        }else{
            if(curr.open <= prev.close && curr.close >= prev.open){
                ans[i] = true;
            }
        }
    }
    return ans;
}

//same as BearishEngulfing