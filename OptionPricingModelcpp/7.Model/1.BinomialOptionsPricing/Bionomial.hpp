#ifndef __Binomial__hpp
#define __Binomial__hpp

#include<vector>
#include<cmath>
using vec = std::vector<double>;

class BinomialModel{
    public:
        BinomialModel(const BinomialModel &p);
        virtual ~BinomialModel();
        BinomialModel &operator=(const BinomialModel &p);
        BinomialModel(double T,  //expiration time
                      double S,  //stock price
                      double r,  //interest rate
                      double sigma, //for volatility
                      double q,     //dividend yield
                      int n,        //number of steps
                      bool call     //true-call, false-put
        );
        
        double optionPriceForStrike(double k);
        virtual void computerPriceStep(int i, int j, double k, vec &prices, double p_u, double p_d, double u);
    
    protected:
        double getStockPrice(){return m_S;}
    private:
        double m_T;
        double m_S;
        double m_r;
        double m_sigma;
        double m_q;
        int m_n;
        bool m_call;
    
};

#endif