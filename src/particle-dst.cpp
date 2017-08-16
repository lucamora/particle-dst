#include "particle-dst.h"

void DST::begin(dst_limit_t beginning_limit, dst_limit_t end_limit, int offset)
{
  // save beginning and end limits
  beginning_l = beginning_limit;
  end_l = end_limit;

  // set DST offset
  Time.setDSTOffset(offset);
}

bool DST::check()
{
  if (!Time.isValid()) {
    Serial.println("[TIME]: time not synced");
    // if time is not valid, sync it
    Particle.syncTime();
    Serial.println("[TIME]: syncing time");
    waitUntil(Particle.syncTimeDone);
  }

  if (Time.isDST()) {
    // disable DST to avoid problems
    // needed to compare limits with local time
    Time.endDST();
  }

  int now = Time.local();
  // calculate beginning and end limits
  int beginning = timestamp(beginning_l);
  int end = timestamp(end_l);

  Serial.printlnf("beginning: %d\nend: %d\nnow: %d", beginning, end, now);

  // check if beginning and end are in the same year
  if (beginning < end) {
    // DST starts and ends in the same year
    if (now >= beginning && now < end) {
      // now is DST so enable DST mode
      Time.beginDST();
      Serial.println("DST: on");
      return true;
    }
  }
  // or beginning is in a year and end is in the next one
  else {
    // DST ends next year or has started last year
    if (now >= beginning || now < end) {
      // now is DST so enable DST mode
      Time.beginDST();
      Serial.println("DST: on");
      return true;
    }
  }

  Serial.println("DST: off");
  return false;
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

  int weeks;
  // check if occurrence from beginning or from end of the month
  if (limit.occurrence > 0) {
    weeks = limit.occurrence - 1;
  }
  else {
    // find days until the requested occurrence
    int from_end = (abs(limit.occurrence) - 1) * 7;

    // calculate number of weeks in the month
    weeks = round((DAYS[limit.month - 1] - 1 - first_occurrence - from_end) / 7);
  }

  // seconds added to the first of month to get to the requested occurrence
  return ts + ((first_occurrence + (weeks * 7)) * 24 * 3600);
}
