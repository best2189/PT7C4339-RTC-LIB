

## Arduino library of PT7C4339 Real-Time Clock/calendar

## พัฒนาโดย นาย สุพงศ์ เฉลิมชัยนุวงศ์ 
   วันที่ 20 มีนาคม 2568
   โดเนทเพื่อขวัญกำลังใจได้ที่ ธนาคารกสิกร 0718251311 
   

## Examples
## การต่อวงจร ครับผม 

c load สามารถใช้ในช่วง 2 pf ถึง 12 pf 
<br>
![PT7C4339 RTC Module](https://github.com/best2189/PT7C4339-RTC-LIB/blob/1c416ceee9e9cccdf085514ce6fc06321af73a87/75736.jpg)  



การต่อใช้งานกับบอร์ดต่างๆ 
<br>
|บอร์ดที่ใช้งาน            |SDA    |SCL          |SQW/INT        |                          
|-----------------------|-------|-------------|---------------|
|Arduino uno            |  A4   |    A5       |     2,3         |                         
|ArduinoMega2560        |   20   |    21       |    2, 3, 18, 19       |                          
|Esp8266                |   D2   | D1    |  All GPIO pins |                          
|Esp32                  |   21  |    22       | All GPIO pins          |            
<br>


## ฟังก์ชั่นการใช้งานหลักๆ (Features)
- สนับสนุนทั้งโหมด 12/24 ชั่วโมง (12/24 hour mode support)
- การตั้งค่า Alarm 2 ช่อง (Dual alarm functionality)
- อ่านค่าเวลาแบบเต็มรูปแบบ (Full date-time reading)
- ตรวจสอบสถานะ Oscillator (Oscillator status check)

## การติดตั้ง (Installation)
1. Download ZIP
2. Arduino IDE: Sketch > Include Library > Add .ZIP Library...
3. Select the downloaded file

## ตัวอย่างโค้ด (Example)
```cpp
#include <Wire.h>
#include "PT7C4339.h"

PT7C4339 Best;

void setup() {
  Serial.begin(9600);
  Best.begin();
  Best.clearAllAlarm();
  Best.clearAlarmFlags();
  Best.enableOscillator();
  //วันศุกร์ ที่ 21 มีนาคม 2025 เวลา 14:10:10 ระบบเวลา 24 ชั่วโมง 
  Best_rtc.set24hrMode(Friday,21,March,2025,14,10,10);
  Best_rtc.defaultTrickleCharger(0x00);
}

void loop() {
  Serial.println(Best.readDateTime());
  delay(1000);
}
