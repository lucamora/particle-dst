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
  private:
    int beginning;
    int end;
    int timestamp(dst_limit_t limit);
                        // j   f   m   a   m   j   j   a   s   o   n   d
    const int DAYS[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
};

#endif
