

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


# เอกสารประกอบไลบรารี PT7C4339 RTC


### `PT7C4339()`
```cpp
PT7C4339::PT7C4339()
```
**คำอธิบาย**: Constructor ของคลาส PT7C4339  
**พารามิเตอร์**: ไม่มี  
**คืนค่า**: ไม่มี

---

### `begin()`
```cpp
void PT7C4339::begin()
```
**คำอธิบาย**: เริ่มต้นการสื่อสาร I2C  
**พารามิเตอร์**: ไม่มี  
**คืนค่า**: ไม่มี  
**ตัวอย่างการใช้งาน**:
```cpp
PT7C4339 rtc;
rtc.begin();
```


## ฟังก์ชันการตั้งค่าเวลา

### `set24hrMode()`
```cpp
void PT7C4339::set24hrMode(uint8_t dayOfWeek, uint8_t date, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second)
```
**คำอธิบาย**: ตั้งค่าเวลาในโหมด 24 ชั่วโมง  
**พารามิเตอร์**:
- `dayOfWeek`: วันในสัปดาห์ (1-7)
- `date`: วันที่ (1-31)
- `month`: เดือน (1-12)
- `year`: ปี (2000-2099)
- `hour`: ชั่วโมง (0-23)
- `minute`: นาที (0-59)
- `second`: วินาที (0-59)  
**ตัวอย่าง**:
```cpp
rtc.set24hrMode(1, 15, 6, 2023, 14, 30, 0); // อาทิตย์ที่ 15 มิ.ย. 2023 14:30:00
```

---

### `set12hrMode()`
```cpp
void PT7C4339::set12hrMode(uint8_t dayOfWeek, uint8_t date, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second, uint8_t period)
```
**คำอธิบาย**: ตั้งค่าเวลาในโหมด 12 ชั่วโมง  
**พารามิเตอร์**:
- `period`: 0 = AM, 1 = PM  
**ตัวอย่าง**:
```cpp
rtc.set12hrMode(2, 15, 6, 2023, 2, 30, 0, 1); // จันทร์ที่ 15 มิ.ย. 2023 02:30:00 PM
```

---

## ฟังก์ชันการอ่านเวลา

### `readDateTime()`
```cpp
String PT7C4339::readDateTime()
```
**คำอธิบาย**: อ่านค่าวันที่และเวลาแบบเต็มรูปแบบ  
**คืนค่า**: สตริงรูปแบบ "Day MM/DD/YYYY HH:MM:SS"  
**ตัวอย่าง**:
```cpp
String datetime = rtc.readDateTime();
// ผลลัพธ์: "Sunday 06/15/2023 14:30:00"
```

นี่คือคำอธิบายแบบละเอียดสำหรับฟังก์ชันตั้งค่า Alarm แบบ 12/24 ชั่วโมง ในรูปแบบ Markdown ที่เหมาะสำหรับใส่ในไฟล์ README.md หรือเอกสารประกอบไลบรารี:

```markdown
## ⏰ ฟังก์ชันตั้งค่า Alarm แบบเลือกโหมดเวลา

### 1. `setAlarm1_24_12()`
```cpp
void setAlarm1_24_12(
    uint8_t day_date, 
    uint8_t hours, 
    uint8_t minutes, 
    uint8_t seconds, 
    uint8_t mask, 
    bool is_24hr, 
    bool is_pm
)
```

**คำอธิบาย**: ตั้งค่า Alarm 1 พร้อมเลือกโหมดเวลา 12 หรือ 24 ชั่วโมง

**พารามิเตอร์**:
| พารามิเตอร์ | ประเภท | ช่วงค่า | คำอธิบาย |
|------------|--------|---------|----------|
| `day_date` | uint8_t | 1-31 | วันที่ในเดือน (1-31) |
| `hours` | uint8_t | 1-12 (12hr) หรือ 0-23 (24hr) | ค่าชั่วโมง |
| `minutes` | uint8_t | 0-59 | ค่านาที |
| `seconds` | uint8_t | 0-59 | ค่าวินาที |
| `mask` | uint8_t | 0x00-0xFF | บิต mask สำหรับเงื่อนไขการเตือน |
| `is_24hr` | bool | true/false | โหมดเวลา (true = 24hr, false = 12hr) |
| `is_pm` | bool | true/false | ระบุช่วงเวลา (ใช้กับโหมด 12hr เท่านั้น) |

**รายละเอียดบิต mask**:
- บิต 7 (0x80): กำหนดให้ไม่สนใจฟิลด์นี้เมื่อเทียบค่า
- บิต 6-0: ค่าที่ต้องการตั้ง Alarm

**ตัวอย่างการใช้งาน**:
```cpp
// ตั้ง Alarm 1 ในโหมด 24 ชั่วโมง
rtc.setAlarm1_24_12(15, 14, 30, 0, 0x00, true, false);

// ตั้ง Alarm 1 ในโหมด 12 ชั่วโมง (PM)
rtc.setAlarm1_24_12(15, 2, 30, 0, 0x00, false, true);
```

---

### 2. `setAlarm2_24_12()`


**คำอธิบาย**: ตั้งค่า Alarm 2 พร้อมเลือกโหมดเวลา (ไม่มีฟิลด์วินาที)

**พารามิเตอร์**:
| พารามิเตอร์ | ประเภท | ช่วงค่า | คำอธิบาย |
|------------|--------|---------|----------|
| `day_date` | uint8_t | 1-31 | วันที่ในเดือน |
| `hours` | uint8_t | 1-12 (12hr) หรือ 0-23 (24hr) | ค่าชั่วโมง |
| `minutes` | uint8_t | 0-59 | ค่านาที |
| `mask` | uint8_t | 0x00-0xFF | บิต mask สำหรับเงื่อนไขการเตือน |
| `is_24hr` | bool | true/false | โหมดเวลา |
| `is_pm` | bool | true/false | ระบุช่วงเวลา |

**หมายเหตุสำหรับโหมด 12 ชั่วโมง**:
- ตั้งค่า `is_pm = true` สำหรับช่วงบ่าย (PM)
- ตั้งค่า `is_pm = false` สำหรับช่วงเช้า (AM)
- ระบบจะเพิ่มค่า 0x40 ในรีจิสเตอร์ให้อัตโนมัติเพื่อระบุโหมด 12hr

**ตัวอย่างการใช้งาน**:
```cpp
// ตั้ง Alarm 2 ในโหมด 12 ชั่วโมง (AM)
rtc.setAlarm2_24_12(15, 8, 0, 0x80, false, false);

// ตั้ง Alarm 2 ในโหมด 24 ชั่วโมง
rtc.setAlarm2_24_12(15, 16, 0, 0x00, true, false);
```

---

## 📝 ตัวอย่างการตั้งค่า Mask
```cpp
// ตัวอย่าง 1: Alarm ทำงานทุกวันเมื่อเวลาตรงกับ 07:30:00
setAlarm1_24_12(0, 7, 30, 0, 0x00, true, false);

// ตัวอย่าง 2: Alarm ทำงานทุกวันที่ 15 ของเดือน เมื่อเวลาตรงกับ 07:00 น.
setAlarm1_24_12(15, 7, 0, 0, 0x80, true, false);

// ตัวอย่าง 3: Alarm ทำงานทุกชั่วโมงที่ 30 นาที
setAlarm2_24_12(0, 0, 30, 0xC0, true, false);
```

---

## ⚠️ ข้อควรระวัง
1. สำหรับโหมด 12 ชั่วโมง:
   - ค่า `hours` ต้องอยู่ระหว่าง 1-12
   - ต้องระบุ `is_pm` ให้ถูกต้อง
2. โหมด 24 ชั่วโมง:
   - ค่า `hours` ต้องอยู่ระหว่าง 0-23
   - พารามิเตอร์ `is_pm` จะถูก忽略
3. ระบบจะแปลงค่าให้เป็น BCD อัตโนมัติ


###  checkAlarm1Status()

```cpp
uint8_t PT7C4339::checkAlarm1Status()
```

**คำอธิบาย**: ตรวจสอบสถานะ Alarm 1  
**คืนค่า**: 1 = Alarm ทำงาน, 0 = ไม่ทำงาน

---

## ฟังก์ชันอื่นๆ

### `enableOscillator()`
```cpp
void PT7C4339::enableOscillator()
```
**คำอธิบาย**: เปิดใช้งานออสซิลเลเตอร์

---

### `checkOsfStatus()`
```cpp
uint8_t PT7C4339::checkOsfStatus()
```
**คำอธิบาย**: ตรวจสอบสถานะออสซิลเลเตอร์  
**คืนค่า**: 1 = ทำงานปกติ, 0 = หยุดทำงาน

---

## หมายเหตุ
1. ต้องต่อวงจร I2C พร้อม Pull-up resistors
2. แนะนำให้ใช้แบตเตอรี่ Backup
3. วันที่ต้องอยู่ในช่วงที่ถูกต้องของแต่ละเดือน
## การติดตั้ง (Installation)
1. Download ZIP
2. Arduino IDE: Sketch > Include Library > Add .ZIP Library...
3. Select the downloaded file

## ตัวอย่างโค้ด (Example)
```cpp
#include <Wire.h>
#include "PT7C4339.h"

PT7C4339  Best_rtc;

void setup() {
  Serial.begin(9600);
  Best_rtc.begin();
  Best_rtc.clearAllAlarm();
  Best_rtc.clearAlarmFlags();
  Best_rtc.enableOscillator();
  //วันศุกร์ ที่ 21 มีนาคม 2025 เวลา 14:10:10 ระบบเวลา 24 ชั่วโมง 
  Best_rtc.set24hrMode(Friday,21,March,2025,14,10,10);
  Best_rtc.defaultTrickleCharger(0x00);
}

void loop() {
  Serial.println(Best_rtc.readDateTime());
  delay(1000);
}
