//1.avoid memory leaks of the returned data

#include "FinanceStatement.h"
#include<iostream>

int main(){
    std::unique_ptr<FinancialStatement> fs = getSampleStatement();
    return 0;
}

