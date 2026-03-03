#ifndef __CORRELATION__
#define __CORRELATION__

class TimeSeries;
class Correlation{
    public:
        Correlation(TimeSeries &a, TimeSeries &b);
        ~Correlation();
        Correlation(const Correlation &);
        Correlation &operator = (const Correlation &);
        double correlation();

    private:
        TimeSeries &m_tsA;
        TimeSeries &m_tsB;
};

#endif