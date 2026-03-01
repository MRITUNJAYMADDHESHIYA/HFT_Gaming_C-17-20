#ifndef __COMPOUND_INTEREST__
#define __COMPOUND_INTEREST__

class CompoundIntRate{
    public:
        CompoundIntRate(double rate);
        CompoundIntRate(const CompoundIntRate &v);
        CompoundIntRate &operator = (const CompoundIntRate &v);
        ~CompoundIntRate();

        double multiplePeriod(double value, int numPeriods);
        double continuousCompounding(double value, int numperiods);

    private:
        double m_rate;
};

#endif