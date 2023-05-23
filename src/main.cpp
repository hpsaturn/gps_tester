#include <Arduino.h>
#include "hal.h"
#include "sdcard.h"
#include "gps.h"


void setup(void) {
  Serial.begin(115200);
  Serial.flush();
  delay(1000);
  Serial.println("\n== INIT SETUP ==\n");
  gps_init();
  delay(500);
  sdcard_init();
  delay(500);
  printRootFiles();
}

void updateGuiStatus() {
  static uint_fast64_t sts = 0; // timestamp for GUI refresh
  if ((millis() - sts > 1000 * 1)) {
    sts = millis();
    if (gps.location.isValid()) Serial.println ("-->[AGPS] localization reached :)" );
    if (gps.satellites.isValid()) Serial.println ("-->[AGPS] satellites reached :)" );
    if (gps.time.isValid()) Serial.println ("-->[AGPS] Time reached :)" );
    if (gps.time.isValid()) Serial.println ("-->[AGPS] Time reached :)" );
    if (gps.speed.isValid()) Serial.println ("-->[AGPS] Speed is valid :)" );
    if (gps_log_loop()) Serial.println ("-->[AGPS] SD logging end.");
  }
}

void loop(void) {
  smartDelay(1000);
  updateGuiStatus();
}
