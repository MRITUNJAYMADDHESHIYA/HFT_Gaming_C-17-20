#include "../1_Statical_Distributions/statistics.h"
#include "correlated_snd.h"
#include <iostream>
#include <vector>


int main(int argc, char **argv){
    int vals = 30;

    StandardNormalDistribution snd;
    std::vector<double> snd_uniform_draws(vals, 0.0);
    std::vector<double> snd_normal_draws(vals, 0.0);

    //random number
    for(int i=0; i<snd_uniform_draws.size(); i++){
        snd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    snd.random_draws(snd_uniform_draws, snd_normal_draws);

    double rho = 0.5;

    //create the correlated standard normal distribution
    CorrelatedSND csnd(rho, &snd_normal_draws);
    std::vector<double> csnd_unifrom_draws(vals, 0.0);
    std::vector<double> csnd_normal_draws(vals, 0.0);

    //uniform generation for the correlated snd
    for(int i=0; i<csnd_unifrom_draws.size(); i++){
        csnd_unifrom_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    csnd.random_draws(csnd_unifrom_draws,csnd_normal_draws);

    for(int i=0; i<snd_normal_draws.size(); i++){
        std::cout<< snd_normal_draws[i]<<", "<<csnd_normal_draws[i] <<std::endl;
    }

    return 0;
}

