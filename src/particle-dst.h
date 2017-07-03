#ifndef DST_h
#define DST_h
#include "application.h"

typedef struct
{
  int hour;
  int day;
  int month;
  int occurence;
} dst_limit_t;

class DST
{
  public:
    void init(dst_limit_t beginning_limit, dst_limit_t end_limit, int offset);
    bool check();
  private:
    int beginning;
    int end;
    int timestamp(dst_limit_t limit);
};

#endif
