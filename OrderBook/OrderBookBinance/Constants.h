#pragma once

#include<limits>
#include "Types.h"


//"This price is invalid, missing, or undefined."
struct Constants{
    static const Price InvalidPrice = std::numeric_limits<Price>::quiet_NaN();
};