#ifndef __STATISTICS_H
#define __STATISTICS_H

#include<vector>
#include<cmath>

class StaticalDistribution{
    public:
        StaticalDistribution();
        virtual ~StaticalDistribution();

        //Distribution funtion(probability and cumulative)
        virtual double pdf(const double& x) const = 0;
        virtual double cdf(const double& x) const = 0;

        //Inverse cumulative distribution functions
        virtual double inv_cdf(const double& quantile) const = 0;

        //statics
        virtual double mean() const = 0;
        virtual double var()  const = 0;
        virtual double stdev() const = 0;

        //obtain a sequence of random draw from this distribution
        virtual void random_draws(const std::vector<double>& uniform_draws, std::vector<double>& dist_draws) = 0;

};

class StandardNormalDistribution : public StaticalDistribution{
    public:
        StandardNormalDistribution();
        virtual ~StandardNormalDistribution();

        virtual double pdf(const double& x) const;
        virtual double cdf(const double& x) const;

        virtual double inv_cdf(const double& quantile) const;

        virtual double mean() cosnt;
        virtual double var()  const;
        virtual double stdev() cosnt;

        virtual void random_draws(const std::vector<double>& uniform_draws, std::vector<double>& dist_draws);
};
#endif