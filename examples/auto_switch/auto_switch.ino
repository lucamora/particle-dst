#include "particle-dst.h"

DST dst;

dst_limit_t beginning;
dst_limit_t end;

void setup() {
  Serial.begin(9600);

  beginning.hour = 2;
  beginning.day = 3; // tuesday
  beginning.month = 2; // february
  beginning.occurrence = 2;

  end.hour = 3;
  end.day = 4; // wednesday
  end.month = 10; // october
  end.occurrence = 2;

  dst.begin(beginning, end, 1);
  dst.automatic(true);
}

void loop() {

}
