#ifndef __TIME_SERIES__
#define __TIME_SERIES__

#include <vector>

class TimeSeries{
    public:
        TimeSeries();
        TimeSeries(const TimeSeries &);
        TimeSeries &operator=(const TimeSeries &);
        ~TimeSeries();

        void addValue(double val);
        double stdDev();
        double mean();
        size_t size();
        double elem(int i);
    private:
        std::vector<double> m_values;
};

#endif
