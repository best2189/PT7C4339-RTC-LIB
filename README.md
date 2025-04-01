# PT7C4339 Real-Time Clock Library
### โดย สุพงศ์ เฉลิมชัยนุวงศ์ (Suphong Chalermchaiwong)
![PT7C4339 RTC Module](https://example.com/path/to/rtc_image.jpg)  
*(รูปภาพโมดูล PT7C4339 - replace with actual image URL)*

**วันที่พัฒนา:** 20 มีนาคม 2568  
**สนับสนุนนักพัฒนา:**  
[![Donate](https://img.shields.io/badge/Donate-KBank-ff69b4)](https://example.com/donate)  
ธนาคารกสิกรไทย 071-8-2513-11

---

## ตัวอย่างการติดตั้ง (Installation)
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
  Best.set24hrMode(1, 1, 1, 2024, 12, 0, 0); // 2024-01-01 12:00:00
}

void loop() {
  Serial.println(Best.readDateTime());
  delay(1000);
}
