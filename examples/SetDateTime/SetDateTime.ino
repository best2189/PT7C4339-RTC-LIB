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
  //วันศุกร์ ที่ 21 มีนาคม 2025 เวลา 14:10:10 ระบบเวลา 24 ชั่วโมง 
  Best_rtc.set24hrMode(Friday,21,March,2025,14,10,10);
  //วันศุกร์ ที่ 21 มีนาคม 2025 เวลา 11:59:55   AM ระบบเวลา 12 ชั่วโมง 
  //Best_rtc.set12hrMode(Friday,21,March,2025,11,59,55,sysTimeAM);
  //วันศุกร์ ที่ 21 มีนาคม 2025 เวลา 11:59:55   PM ระบบเวลา 12 ชั่วโมง 
  //Best_rtc.set12hrMode(Friday,21,March,2025,11,59,55,sysTimePM);
}

void loop(void) 
{
    String dateTime = Best_rtc.readDateTime();  // รับค่าวันที่และเวลาเป็นสตริง
    Serial.println(dateTime);                   // พิมพ์ออกทาง Serial
    delay(1000);
}
