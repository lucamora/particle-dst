#ifndef DST_h
#define DST_h
#include "application.h"

typedef struct
{
  int hour;
  int day;
  int month;
  int occurrence;
} dst_limit_t;

class DST
{
  public:
    void begin(dst_limit_t beginning_limit, dst_limit_t end_limit, int offset);
    bool check();
    void automatic(bool enable);

    // return beginning and end limits in timestamps or formatted strings
    int beginning();
    char* beginning(String format);
    int end();
    char* end(String format);

    // days and months enumerators
    enum days { sun = 1, mon = 2, tue = 3, wed = 4, thu = 5, fri = 6, sat = 7 };
    enum months { jan = 1, feb = 2, mar = 3, apr = 4, may = 5, jun = 6, jul = 7, aug = 8, sep = 9, oct = 10, nov = 11, dec = 12 };
  private:
    dst_limit_t beginning_l;
    dst_limit_t end_l;
    int timestamp(dst_limit_t limit);
    Timer *timer;
    void auto_check();
    char* buf;
    char* format_limit(dst_limit_t limit, String format);
                        // j   f   m   a   m   j   j   a   s   o   n   d
    const int DAYS[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
};

#endif
