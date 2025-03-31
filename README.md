# สุพงศ์ เฉลิมชัยนุวงศ์ 

Arduino library of PT7C4339 Real-Time Clock/calendar

   พัฒนาโดย นาย สุพงศ์ เฉลิมชัยนุวงศ์ 
   วันที่ 20 มีนาคม 2568
   โดเนทเพื่อขวัญกำลังใจได้ที่ ธนาคารกสิกร 0718251311 
   
## Examples


# PT7C4339 Real-Time Clock Library


Arduino library for PT7C4339 I2C Real-Time Clock module with bilingual documentation (English/Thai).

## คุณสมบัติ (Features)
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

PT7C4339 rtc;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  rtc.set24hrMode(1, 1, 1, 2024, 12, 0, 0); // Set to 2024-01-01 12:00:00
}

void loop() {
  Serial.println(rtc.readDateTime());
  delay(1000);
