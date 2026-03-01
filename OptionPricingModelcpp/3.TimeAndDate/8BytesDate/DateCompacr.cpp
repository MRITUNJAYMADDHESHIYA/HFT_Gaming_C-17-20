#include "DateCompact.hpp"
#include<iostream>
#include<cstring>

using std::cout;
using std::endl;

DateCompact::DateCompact(int year, int month, int day){
    setYear(year);
    setMonth(month);
    setDay(day);
}

DateCompact::DateCompact(const DateCompact &p){
    strcpy(m_date, p.m_date);
}

DateCompact::~DateCompact()
{}

DateCompact &DateCompact::operator=(const DateCompact &p){
    if(&p != this){
        strcpy(m_date, p.m_date);
    }
    return *this;
}


//Use string comparison to determine if the dates are equal
bool DateCompact::operator==(const DateCompact &d) const{
    return strncmp(m_date, d.m_date, 8) == 0;
}

// Use the strncmp function to determine if a date is less than the other.
bool DateCompact::operator<(const DateCompact &d) const{
    return strncmp(m_date, d.m_date, 8) < 0;
}


//year,month, day
int DateCompact::year(){
    return 1000*(m_date[0]-'0') + 100*(m_date[1]-'0') + 10*(m_date[2]-'0') + (m_date[3]-'0');
}
int DateCompact::month(){
    return 10*(m_date[4]-'0') + (m_date[5]-'0');
}
int DateCompact::day(){
    return 10*(m_date[6]-'0') + (m_date[7]-'0');
}

void DateCompact::print(){
    char s[9];  // Copy the m_date string into a NULL terminated
    strncpy(s, m_date, 8);
    s[8] = '\0';
    cout<< s <<endl;
}

//calculate string corresponding to the give numeric parameter
void DateCompact::setYear(int year){
    m_date[3] = '0' + (year%10);
    year /= 10;
    m_date[2] = '0' + (year%10);
    year /= 10;
    m_date[1] = '0' + (year%10);
    year /= 10;
    m_date[0] = '0' + (year%10);
}
void DateCompact::setMonth(int month){
    m_date[5] = '0' + (month%10);
    month /= 10;
    m_date[4] = '0' + (month%10);
    month /= 10;
}
void DateCompact::setDay(int day){
    m_date[7] = '0' + (day%10);
    day /= 10;
    m_date[6] = '0' + (day%10);
    day /= 10;
}


//for comparision
// #include "24BytesDate/Date.hpp"

int main(){
    DateCompact d(2024,10,7);
    DateCompact e(2024,10,10);
    cout<<" size of DateCompact: "<<sizeof(DateCompact) <<endl;

    d.print();
    e.print();

    if(d<e){
        cout<<" d is less than e "<<endl;
    }else{
        cout<<" d is not less than e "<<endl;
    }

    // Date date(2024,10,7);
    // cout<<"size of Date: "<< sizeof(Date) <<endl;
    return 0;
}