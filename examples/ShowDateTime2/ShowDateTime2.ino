#include <Wire.h>
#include "PT7C4339.h"

PT7C4339 Best_rtc;

void PT7C4339Disp(void) 
{
  static unsigned long Timer1 = millis();
  if ((millis() - Timer1) >= 1000) 
  {
    Timer1 = millis();
    char timeStrloop[20];
    char dateStrloop[20];
    char fullStrloop[50];
    const char* dayNamesloop[8] = {
      "Undefined",  // index 0 ไม่ใช้
      "Sunday",     // 1
      "Monday",     // 2
      "Tuesday",    // 3
      "Wednesday",  // 4
      "Thursday",   // 5
      "Friday",     // 6
      "Saturday"    // 7
    };
    if (Best_rtc.get12_24hr()) 
    {
      sprintf(timeStrloop, "%02d:%02d:%02d %s",   Best_rtc.getHour(),  Best_rtc.getMinute(),  Best_rtc.getSecond(), Best_rtc.getAM_PM() ? "PM" : "AM");
    } 
    else 
    {
      sprintf(timeStrloop, "%02d:%02d:%02d",   Best_rtc.getHour(),  Best_rtc.getMinute(),  Best_rtc.getSecond());
    }
    sprintf(dateStrloop, "%02d/%02d/20%02d",   Best_rtc.getDate(),   Best_rtc.getMonth(),   Best_rtc.getYear());
    const char* dayStr = ( Best_rtc.getDayOfWeek() >= 1 &&  Best_rtc.getDayOfWeek() <= 7) ? dayNamesloop[ Best_rtc.getDayOfWeek()] : "Invalid";
    sprintf(fullStrloop, "%s %s %s", dayStr, dateStrloop, timeStrloop);
    Serial.println(fullStrloop);
  }
}
void setup(void) 
{
  Serial.begin(9600);
  Best_rtc.begin();
  Best_rtc.clearAllAlarm();
  Best_rtc.clearAlarmFlags();
  Best_rtc.defaultTrickleCharger(0x00);
  Best_rtc.enableOscillator();
}

void loop(void) 
{
  PT7C4339Disp();
}
