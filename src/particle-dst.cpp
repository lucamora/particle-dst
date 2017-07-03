#include "particle-dst.h"

void DST::begin(dst_limit_t beginning_limit, dst_limit_t end_limit, int offset)
{
  // calculate timestamps of beginning and end limits
  beginning = timestamp(beginning_limit);
  end = timestamp(end_limit);

  // set DST offset
  Time.setDSTOffset(offset);
}

bool DST::check()
{
  if (Time.isDST()) {
    // disable DST to avoid problems
    // needed to compare local time
    Time.endDST();
  }

  Serial.printlnf("beginning: %d\nend: %d\nnow: %d", beginning, end, Time.local());

  if (Time.local() >= beginning && Time.local() < end) {
    // now is DST so enable DST mode
    Time.beginDST();
    Serial.println("DST: on");
    return true;
  }
  else {
    Serial.println("DST: off");
    return false;
  }
}

int DST::timestamp(dst_limit_t limit)
{
  time_t ts; //timestamp
  struct tm first_of_month; // date struct

  first_of_month.tm_sec = 0;
  first_of_month.tm_min = 0;
  first_of_month.tm_mday = 1; // first day of month

  first_of_month.tm_hour = limit.hour;
  first_of_month.tm_mon = limit.month - 1;

  // tm struct stores years since 1900
  first_of_month.tm_year = Time.year() - 1900;

  // convert time struct to timestamp
  // calculate timestamp of the first day of the month
  ts = mktime(&first_of_month);


  // number of days until the first occurrence
  int first_occurrence = (6 + limit.day - first_of_month.tm_wday) % 7;
  Serial.printlnf("first of month: %d | first occurrence: %d", first_of_month.tm_wday, first_occurrence);

  int weeks = limit.occurrence - 1;

  // seconds added to the first of month to get to the requested occurrence
  return ts + ((first_occurrence + (weeks * 7)) * 24 * 3600);
}
