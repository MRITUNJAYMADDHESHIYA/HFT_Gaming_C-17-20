#ifndef __CASHFLOW__
#define __CASHFLOW__

#include <vector>

class CashFlow{
    public:
        CashFlow(double rate);
        CashFlow(const CashFlow &v);
        CashFlow &operator = (const CashFlow &v);
        ~CashFlow();

        void addCashPayment(double value, int timePeriod);
        double presentValue();
    
    private:
        std::vector<double> m_cashPayments;
        std::vector<int> m_timePeriods;
        double m_rate;
        double presentValue(double futureValue, int timePeriod);
};

#endif