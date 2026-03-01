//The HestonEuler class is designed to accept the parameters of the Heston Model - k, 0, and then calculate both the volatility and asset price paths.


#ifndef __HESTON_MC_H
#define __HESTON_MC_H

#include<vector>
#include<cmath>
#include "option.h"

//Heston stochastic volatility model
class HestonEuler{
    private:
        Option* pOption;
        double kappa;
        double theta;
        double xi;
        double rho;

    public:
        HestonEuler(Option* _pOtion, double _kappa, double _theta, double _xi, double _rho);

        virtual ~HestonEuler();

        //calculate the volatility path
        void calc_vol_path(const std::vector<double>& vol_draws, std::vector<double>& vol_path);
        //calculate the asset price path
        void calc_spot_path(const std::vector<double>& spot_draws, const std::vector<double>& vol_path, std::vector<double>& spot_path);
};

#endif
