#include <Wire.h>
#include "PT7C4339.h"

PT7C4339 Best_rtc;

void setup(void) 
{
  Serial.begin(9600);
  Best_rtc.begin();
  Best_rtc.clearAllAlarm();
  Best_rtc.defaultTrickleCharger(0x00);
  Best_rtc.enableOscillator();

/* 
  Best_rtc.setAlarm1_24_12(21,14,10,55,0,true,false);  // Day 21, 14:10:55 No mask, 24-hour mode
  Best_rtc.setAlarm2_24_12(21,14,11,0,true,false);     // Day 21, 14:11:00 No mask, 24-hour mode
  Best_rtc.enableAlarmInterruptSqw(1, 1);  // เปิดใช้ขา sqw .ให้เป็น high to low เมื่อถึงเวลาอาราม 
  Best_rtc.clearAlarmFlags();
  //วันศุกร์ ที่ 21 มีนาคม 2025 เวลา 14:10:50 ระบบเวลา 24 ชั่วโมง 
  Best_rtc.set24hrMode(Friday,21,March,2025,14,10,50);
*/ 

  Best_rtc.setAlarm1_24_12(21, 11, 59, 55, 0, false, true); // Day 21, 11:59:55 PM No mask, 12-hour mode, PM
  Best_rtc.setAlarm2_24_12(22, 12, 0, 0, false, false);     // Day 22, 12:00:00 AM No mask, 12-hour mode, AM
  Best_rtc.enableAlarmInterruptSqw(1, 1);  // เปิดใช้ขา sqw .ให้เป็น high to low เมื่อถึงเวลาอาราม 
  Best_rtc.clearAlarmFlags();
  //วันศุกร์ ที่ 21 มีนาคม 2025 เวลา 11:59:55   AM ระบบเวลา 12 ชั่วโมง 
  //Best_rtc.set12hrMode(Friday,21,March,2025,11,59,55,sysTimeAM);
  //วันศุกร์ ที่ 21 มีนาคม 2025 เวลา 11:59:55   PM ระบบเวลา 12 ชั่วโมง 
  Best_rtc.set12hrMode(Friday,21,March,2025,11,59,50,sysTimePM);

}

void loop(void) 
{
  static unsigned long Best_timer1 = millis();
  if((millis()-Best_timer1)>=1000)
  {
    Best_timer1 = millis();
    String dateTime = Best_rtc.readDateTime();  // รับค่าวันที่และเวลาเป็นสตริง
    Serial.println(dateTime);                   // พิมพ์ออกทาง Serial
  }
    if( Best_rtc.checkAlarm1Status())
    {
         Serial.println("Alarm1 ");
         Best_rtc.clearAlarmFlags();
    }
    if( Best_rtc.checkAlarm2Status())
    {
        Serial.println("Alarm2 ");
        Best_rtc.clearAlarmFlags();
    }
    
}
