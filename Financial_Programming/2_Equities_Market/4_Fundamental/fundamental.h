#ifndef __FUNDAMENTAL__
#define __FUNDAMENTAL__

#include <string>

class Fundamental{
    public:
        Fundamental(const std::string &ticker, double price, double dividend);
        ~Fundamental();
        Fundamental(const Fundamental &);
        Fundamental &operator=(const Fundamental&);

        void setNumOfShare(int n);
        void setEarnings(double val);
        void setExpectedEarnings(double val);
        void setBookValue(double val);
        void setAssets(double val);
        void setLiabilitiesAndIntangibles(double val);
        void setEpsGrowth(double val);
        void setNetIncome(double val);
        void setShareHoldersEquity(double val);

        double PE();
        double forwardPE();
        double bookValue();
        double priceToBookRatio();
        double priceEarningsToGrowth();
        double returnOnEquity();
        double getDividend();

    private:
        std::string m_ticker;
        double m_price;
        double m_dividend;
        double m_earningsEstimate;
        int    m_numShares;
        double m_earnings;
        double m_bookValue;
        double m_assets;
        double m_liabilitiesAndIntangibles;
        double m_epsGrowth;
        double m_netIncome;
        double m_shareholdersEquity;
};

#endif