#ifndef __INTRATE__
#define __INTRATE__

#include <vector>

template <class T>
class IntRate{
    public:
        ~IntRate();
        IntRate(const IntRate<T> &a);
        IntRate<T> &operator = (const IntRate<T> &a);

        void setInstrument(T &inv);
        double getAnnualIntRate();
    private:
        T m_instrument;
};

template <class T>
IntRate<T>::~IntRate(){}

template<class T>
IntRate<T>::IntRate(const IntRate<T> &a):m_instrument(a.m_instrument) {}

template<class T>
IntRate<T> &IntRate<T>::operator=(const IntRate<T> &a){
    if(this != &a){
        m_instrument = a.m_instrument;
    }
    return *this;
}


template<class T>
void IntRate<T>::setInstrument(T &inv){
    m_instrument = inv;
}

template<class T>
double IntRate<T>::getAnnualIntRate(){
    double payment = m_instrument.getMonthlyPayment();
    double principal = m_instrument.getPrincipal();
    return (12 * payment) / principal;
}

#endif






