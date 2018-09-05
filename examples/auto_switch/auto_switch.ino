#include "particle-dst.h"

DST dst;

dst_limit_t beginning;
dst_limit_t end;

int one_hour = 3600 * 1000;
uint32_t last_check;

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

  // initialize library
  dst.begin(beginning, end, 1);
  // set timezone
  dst.timezone(1);

  // enable automatic mode
  dst.automatic(true);

  Serial.printlnf("Beginning: %d, end: %d", dst.beginning(), dst.end());
  Serial.printlnf("Beginning: %s, end: %s", dst.beginning("%a, %d %B @ %R"), dst.end("%a, %d %B @ %R"));
}

void loop() {
  if (millis() - last_check > one_hour || last_check == 0) {
    last_check = millis();

    Serial.print(Time.format(Time.local(), TIME_FORMAT_DEFAULT));
    Serial.printlnf(" | enabled: %s", dst.enabled() ? "yes" : "no");
  }
}
