#ifndef __MA__
#define __MA__

#include <vector>
class MA{
    public:
        MA(int period);
        MA(const MA &);
        MA &operator = (const MA &);
        ~MA();

        void addPriceQuote(double close);
        std::vector<double> SMA();
        std::vector<double> EMA();

    private:
        int m_numPeriods;
        std::vector<double> m_prices;
};

#endif
