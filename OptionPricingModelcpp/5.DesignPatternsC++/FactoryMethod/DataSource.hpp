#ifndef DataSource_hpp
#define DataSource_hpp

#include<string>
using namespace std;

class DataSource{
    private:
        DataSource(const string &name);
        DataSource(const DataSource &p);
        DataSource &operator=(const DataSource &p);
    public:
        ~DataSource(); //must be public so clients can use delete
        static DataSource *createInstance();
        void readData();
    private:
        string m_dataName;
        
};
#endif
