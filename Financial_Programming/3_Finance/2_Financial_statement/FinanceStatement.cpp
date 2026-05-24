#include "FinanceStatement.h"

FinancialStatement::FinancialStatement() : m_return(0) {}
FinancialStatement::~FinancialStatement() {}
FinancialStatement::FinancialStatement(const FinancialStatement &v) : m_return(v.m_return), m_transactions(v.m_transactions) {}
FinancialStatement &FinancialStatement::operator=(FinancialStatement &v){
    if(this != &v){
        m_return = v.m_return;
        m_transactions = v.m_transactions;
    }
    return *this;
}

double FinancialStatement::getReturn(){
    return m_return;
}

void FinancialStatement::addTransaction(const std::string &security, double val){
    m_transactions.push_back(std::make_pair(security, val));
}

std::unique_ptr<FinancialStatement> getSampleStatement(){
    std::unique_ptr<FinancialStatement> fs(new FinancialStatement);
    fs->addTransaction("IBM", 102.2);
    fs->addTransaction("AAPL", 523.0);
    return fs;
}

void transferFinancialStatement(std::unique_ptr<FinancialStatement> statement){
    //perform transfer here

    std::cout<<statement->getReturn() <<std::endl;
}
