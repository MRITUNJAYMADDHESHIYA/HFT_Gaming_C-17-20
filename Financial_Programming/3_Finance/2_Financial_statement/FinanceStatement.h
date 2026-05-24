#pragma once

#include <vector>
#include <string>

class FinancialStatement{
    public:
        FinancialStatement();
        ~FinancialStatement();
        FinancialStatement(const FinancialStatement&);
        FinancialStatement &operator=(FinancialStatement &);

        double getReturn();
        void addTransaction(const std::string &security, double val);

    private:
        double m_return;
        std::vector<std::pair<std::string, double>> m_transactions;
};

std::unique_ptr<FinancialStatement> getSampleStatement();
void transferFinancialStatement(std::unique_ptr<FinancialStatement>& statement);

