#include "particle-dst.h"

DST dst;

dst_limit_t beginning;
dst_limit_t end;

void setup() {
  Serial.begin(9600);

  beginning.hour = 2;
  //beginning.day = 3; // tuesday
  beginning.day = DST::days::tue;
  //beginning.month = 2; // february
  beginning.month = DST::months::feb;
  beginning.occurrence = 2;

  end.hour = 3;
  //end.day = 4; // wednesday
  end.day = DST::days::wed;
  //end.month = 10; // october
  end.month = DST::months::oct;
  end.occurrence = 2;

  dst.begin(beginning, end, 1);
  dst.automatic(true);

  Serial.printlnf("Beginning: %d, end: %d", dst.beginning(), dst.end());
  Serial.printlnf("Beginning: %s, end: %s", dst.beginning("%a, %d %B @ %R"), dst.end("%a, %d %B @ %R"));
}

void loop() {

}
