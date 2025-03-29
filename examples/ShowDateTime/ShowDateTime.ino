#include <Wire.h>
#include "PT7C4339.h"

PT7C4339 Best_rtc;

void setup(void) 
{
    Serial.begin(9600);
    Best_rtc.begin();
	Best_rtc.clearAllAlarm();
	Best_rtc.clearAlarmFlags();
	Best_rtc.enableOscillator();
}

void loop(void) 
{
    String dateTime = Best_rtc.readDateTime();  // รับค่าวันที่และเวลาเป็นสตริง
    Serial.println(dateTime);              // พิมพ์ออกทาง Serial
    delay(1000);
}
