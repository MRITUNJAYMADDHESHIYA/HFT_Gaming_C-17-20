#ifndef __VOLATILITY__
#define __VOLATILITY__

#include <vector>

class Volatility{
    public:
        Volatility();
        ~Volatility();
        Volatility(const Volatility &);
        Volatility &operator=(const Volatility &);

        void addPrice(double price);
        double rangeVolatility();
        double avgDailyRange();
        double stdDev();
        double mean();
    private:
        std::vector<double> m_prices;
};

#endif
