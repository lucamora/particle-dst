#include "particle-dst.h"

DST dst;

dst_limit_t beginning;
dst_limit_t end;

bool done = false;

void setup() {
  beginning.hour = 2;
  beginning.day = 3;
  beginning.month = 2;
  beginning.occurrence = 2;

  end.hour = 3;
  end.day = 4;
  end.month = 10;
  end.occurrence = 2;

  dst.init(beginning, end, 1);
}

void loop() {
  delay(3000);
  if (!done) {
    done = true;

    dst.check();
  }
}
