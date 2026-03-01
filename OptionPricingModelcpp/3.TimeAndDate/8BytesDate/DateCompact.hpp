#ifndef __CppOptions__DateCompact__
#define __CppOptions__DateCompact__

class DateCompact{
    public:
        DateCompact(int year, int month, int day);
        DateCompact(const DateCompact &p);
        ~DateCompact();
        DateCompact &operator=(const DateCompact &p);

        void setYear(int y);
        void setMonth(int m);
        void setDay(int d);

        int year();
        int month();
        int day();

        void print();

        bool operator==(const DateCompact &d) const;
        bool operator<(const DateCompact &d) const;
    
    private:
        char m_date[8];
};
#endif