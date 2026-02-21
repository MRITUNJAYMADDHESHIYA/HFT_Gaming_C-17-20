//The Interval Bisection algorithm for finding a root of the generic funtion g;

#ifndef __INTERVAL_BISECTION_H
#define __INTERVAL_BISECTION_H

#include<cmath>

//creating a function template
//trying to find an x such that |g(x) - y| < epsilon
//starting with the interval (m,n)
template<typename T>
double interval_bisection(double y_target, double m, double n, double epsilon, T g){
    double x = 0.5 * (m+n);
    double y = g(x);

    do{
        if(y < y_target){
            m = x;
        }

        if(y > y_target){
            n = x;
        }

        x = 0.5 * (m+n);
        y = g(x);
    }while(fabs(y - y_target) > epsilon);

    return x;
}

#endif