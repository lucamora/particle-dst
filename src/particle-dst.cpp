#include "particle-dst.h"

void DST::begin(dst_limit_t beginning_limit, dst_limit_t end_limit, int offset)
{
  // save beginning and end limits
  beginning_l = beginning_limit;
  end_l = end_limit;

  // set DST offset
  Time.setDSTOffset(offset);

  // create timer for automatic switching
  timer = new Timer(3600 * 1000, &DST::auto_check, *this);
}

void DST::automatic(bool enable)
{
  if (enable) {
    timer->start();
  }
  else {
    timer->stop();
  }
}

void DST::auto_check()
{
  check();
}

bool DST::check()
{
  if (!Time.isValid()) {
    // if time is not valid, sync it
    Particle.syncTime();
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

  // check if beginning and end are in the same year
  if (beginning < end) {
    // DST starts and ends in the same year
    if (now >= beginning && now < end) {
      // now is DST so enable DST mode
      Time.beginDST();
      return true;
    }
  }
  // or beginning is in a year and end is in the next one
  else {
    // DST ends next year or has started last year
    if (now >= beginning || now < end) {
      // now is DST so enable DST mode
      Time.beginDST();
      return true;
    }
  }

  return false;
}

int DST::beginning()
{
  return timestamp(beginning_l);
}

char* DST::beginning(String format)
{
  return format_limit(beginning_l, format);
}

int DST::end()
{
  return timestamp(end_l);
}

char* DST::end(String format)
{
  return format_limit(end_l, format);
}

char* DST::format_limit(dst_limit_t limit, String format)
{
  String s = Time.format(timestamp(limit), format);
  buf = new char[s.length() + 1];
  s.toCharArray(buf, s.length() + 1);
  return buf;
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
