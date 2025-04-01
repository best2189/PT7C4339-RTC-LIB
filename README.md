

## Arduino library of PT7C4339 Real-Time Clock/calendar

## พัฒนาโดย นาย สุพงศ์ เฉลิมชัยนุวงศ์ 
   วันที่ 20 มีนาคม 2568
   โดเนทเพื่อขวัญกำลังใจได้ที่ ธนาคารกสิกร 0718251311 
   

## Examples
## การต่อวงจร ครับผม 
![PT7C4339 RTC Module](https://github.com/best2189/PT7C4339-RTC-LIB/blob/1c416ceee9e9cccdf085514ce6fc06321af73a87/75736.jpg)  
c load สามารถใช้ในช่วง 2 pf ถึง 12 pf 


<br>

|บอร์ดที่ใช้งาน  |SDA    |SCL          |SQW/INT |                          
|------------|-------|-------------|---------------|
| mp3        | y     | y           | y             |                         
| aac        | n     | y           | y             |                          
| aacp       | n     | y (mono)    | y (+SBR, +PS) |                          
| wav        | y     | y           | y             |            
| flac       | n     | y           | y             |
| vorbis     | n     | y           | y             |
| m4a        | n     | y           | y             | 
| opus       | n     | y           | y             |
   
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
  Best.set24hrMode(1, 1, 1, 2024, 12, 0, 0); // Set to 2024-01-01 12:00:00
  Best_rtc.defaultTrickleCharger(0x00);
}

void loop() {
  Serial.println(Best.readDateTime());
  delay(1000);
}
