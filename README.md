

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

# เอกสารการตั้งค่า Alarm บน PT7C4339 RTC

## ตัวอย่างการตั้งค่า Alarm แบบ 12 ชั่วโมง

```cpp
// ตั้ง Alarm1 สำหรับวันที่ 21 เวลา 11:59:55 PM (โหมด 12 ชั่วโมง)
Best_rtc.setAlarm1_24_12(21, 11, 59, 55, 0, false, true);

// ตั้ง Alarm2 สำหรับวันที่ 22 เวลา 12:00:00 AM (โหมด 12 ชั่วโมง)
Best_rtc.setAlarm2_24_12(22, 12, 0, 0, false, false);

// เปิดใช้งานการแจ้งเตือนทั้ง Alarm1 และ Alarm2 ผ่านขา SQW
Best_rtc.enableAlarmInterruptSqw(1, 1);

// ล้างสถานะ Alarm ทั้งหมด
Best_rtc.clearAlarmFlags();

// ตั้งค่าเวลาเริ่มต้น (วันศุกร์ที่ 21 มีนาคม 2025 เวลา 11:59:50 PM โหมด 12 ชั่วโมง)
Best_rtc.set12hrMode(Friday, 21, March, 2025, 11, 59, 50, sysTimePM);
```

## รายละเอียดการตั้งค่า

### 1. การตั้งค่า Alarm1
- **วันที่**: 21
- **เวลา**: 11:59:55 PM
- **โหมดเวลา**: 12 ชั่วโมง
- **ช่วงเวลา**: PM (หลังเที่ยง)
- **Mask**: 0 (ตรวจสอบทุกฟิลด์)

### 2. การตั้งค่า Alarm2
- **วันที่**: 22
- **เวลา**: 12:00:00 AM (เที่ยงคืน)
- **โหมดเวลา**: 12 ชั่วโมง
- **ช่วงเวลา**: AM (ก่อนเที่ยง)
- **Mask**: 0 (ตรวจสอบทุกฟิลด์)

### 3. การตั้งค่าเวลาเริ่มต้น
- **วัน**: ศุกร์
- **วันที่**: 21
- **เดือน**: มีนาคม
- **ปี**: 2025
- **เวลา**: 11:59:50 PM
- **โหมดเวลา**: 12 ชั่วโมง
- **ช่วงเวลา**: PM

## หมายเหตุสำคัญ

1. **การทำงานของ Alarm**:
   - Alarm1 จะทำงานเมื่อเวลาถึง 11:59:55 PM ของวันที่ 21
   - Alarm2 จะทำงานเมื่อเวลาถึง 12:00:00 AM ของวันที่ 22

2. **การแจ้งเตือน**:
   - ขา SQW จะเปลี่ยนสถานะจาก High เป็น Low เมื่อ Alarm ทำงาน
   - ต้องเรียกใช้ `enableAlarmInterruptSqw(1, 1)` เพื่อเปิดใช้งานการแจ้งเตือน

3. **การล้างสถานะ Alarm**:
   - ควรเรียกใช้ `clearAlarmFlags()` หลังจาก Alarm ทำงานแล้ว

4. **ความแตกต่างของโหมดเวลา**:
   - โหมด 12 ชั่วโมง: ต้องระบุ AM/PM ให้ถูกต้อง
   - โหมด 24 ชั่วโมง: ไม่ต้องระบุ AM/PM

## ตัวอย่างการตรวจสอบ Alarm

```cpp
void loop() {
  // ตรวจสอบ Alarm1
  if(Best_rtc.checkAlarm1Status()) {
    Serial.println("Alarm1 ทำงานแล้ว!");
    // ทำสิ่งที่ต้องการเมื่อ Alarm1 ทำงาน
  }

  // ตรวจสอบ Alarm2
  if(Best_rtc.checkAlarm2Status()) {
    Serial.println("Alarm2 ทำงานแล้ว!");
    // ทำสิ่งที่ต้องการเมื่อ Alarm2 ทำงาน
  }
}
```

# การตั้งค่า Alarm แบบ 24 ชั่วโมง บนโมดูล RTC PT7C4339

## รายละเอียดการตั้งค่า

### 1. การตั้งค่า Alarm1
```cpp
Best_rtc.setAlarm1_24_12(21, 14, 10, 55, 0, true, false);
```
- **วันที่**: 21
- **เวลา**: 14:10:55 (2:10:55 PM)
- **โหมดเวลา**: 24 ชั่วโมง
- **Mask**: 0 (ตรวจสอบทุกฟิลด์)

### 2. การตั้งค่า Alarm2
```cpp
Best_rtc.setAlarm2_24_12(21, 14, 11, 0, true, false);
```
- **วันที่**: 21
- **เวลา**: 14:11:00 (2:11:00 PM)
- **โหมดเวลา**: 24 ชั่วโมง
- **Mask**: 0 (ตรวจสอบทุกฟิลด์)

### 3. การเปิดใช้งานขา SQW
```cpp
Best_rtc.enableAlarmInterruptSqw(1, 1);
```
- เปิดใช้งานการแจ้งเตือนทั้ง Alarm1 และ Alarm2
- ขา SQW จะเปลี่ยนสถานะจาก High เป็น Low เมื่อถึงเวลาที่ตั้ง Alarm

### 4. การล้างสถานะ Alarm
```cpp
Best_rtc.clearAlarmFlags();
```
- ล้างสถานะ Alarm ทั้งหมดเพื่อเตรียมรับการแจ้งเตือนใหม่

### 5. การตั้งค่าเวลาเริ่มต้น
```cpp
Best_rtc.set24hrMode(Friday, 21, March, 2025, 14, 10, 50);
```
- **วัน**: ศุกร์
- **วันที่**: 21
- **เดือน**: มีนาคม
- **ปี**: 2025
- **เวลา**: 14:10:50 (2:10:50 PM)
- **โหมดเวลา**: 24 ชั่วโมง

## ลำดับการทำงานของระบบ

1. ตั้งค่าเวลาเริ่มต้นเป็นวันศุกร์ที่ 21 มีนาคม 2025 เวลา 14:10:50
2. ตั้ง Alarm1 ให้ทำงานที่เวลา 14:10:55 (หลังจากตั้งค่า 5 วินาที)
3. ตั้ง Alarm2 ให้ทำงานที่เวลา 14:11:00 (หลังจาก Alarm1 ทำงาน 5 วินาที)
4. เมื่อถึงเวลาที่กำหนด:
   - ขา SQW จะเปลี่ยนสถานะเป็น Low
   - สามารถตรวจสอบสถานะ Alarm ได้ด้วยฟังก์ชัน `checkAlarm1Status()` และ `checkAlarm2Status()`

## ตัวอย่างโค้ดการตรวจสอบ Alarm

```cpp
void loop() {
  if(Best_rtc.checkAlarm1Status()) {
    Serial.println("Alarm1 ทำงานที่เวลา 14:10:55");
    // โค้ดที่ต้องการให้ทำงานเมื่อ Alarm1 ทำงาน
  }

  if(Best_rtc.checkAlarm2Status()) {
    Serial.println("Alarm2 ทำงานที่เวลา 14:11:00");
    // โค้ดที่ต้องการให้ทำงานเมื่อ Alarm2 ทำงาน
  }
}
```

## ข้อควรระวัง

1. ต้องเรียกใช้ `clearAlarmFlags()` หลังจาก Alarm ทำงานแล้ว
2. ตรวจสอบให้แน่ใจว่าได้ตั้งค่าเวลาเริ่มต้นถูกต้องก่อนตั้ง Alarm
3. โหมด 24 ชั่วโมงใช้ค่าชั่วโมงตั้งแต่ 0-23 (0 = เที่ยงคืน, 12 = เที่ยงวัน, 23 = 23:00 น.)

###  checkAlarm1Status()

```cpp
uint8_t PT7C4339::checkAlarm1Status()
```

**คำอธิบาย**: ตรวจสอบสถานะ Alarm1  
**คืนค่า**: 1 = Alarm ทำงาน, 0 = ไม่ทำงาน

---

###  checkAlarm2Status()

```cpp
uint8_t PT7C4339::checkAlarm2Status()
```

**คำอธิบาย**: ตรวจสอบสถานะ Alarm2  
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


# เอกสารประกอบฟังก์ชันการอ่านค่า PT7C4339 RTC

## ฟังก์ชันการอ่านค่าวันเวลา

### `getSecond()`
```cpp
uint8_t getSecond();
```
**หน้าที่**: อ่านค่าวินาทีปัจจุบัน  
**ค่าที่คืน**: 
- ค่าวินาที (0-59) ในรูปแบบฐานสิบ  
**รายละเอียด**:
- อ่านค่าจากรีจิสเตอร์ที่อยู่ 0x00
- กรองเฉพาะ 7 บิตล่าง (0x7F) เพื่อตัดบิตที่ไม่เกี่ยวข้อง
- แปลงจากรูปแบบ BCD เป็นฐานสิบ

---

### `getMinute()`
```cpp
uint8_t getMinute();
```
**หน้าที่**: อ่านค่านาทีปัจจุบัน  
**ค่าที่คืน**: 
- ค่านาที (0-59) ในรูปแบบฐานสิบ  
**รายละเอียด**:
- อ่านค่าจากรีจิสเตอร์ที่อยู่ 0x01
- แปลงจากรูปแบบ BCD เป็นฐานสิบ

---

### `getHour()`
```cpp
uint8_t getHour();
```
**หน้าที่**: อ่านค่าชั่วโมงปัจจุบัน  
**ค่าที่คืน**: 
- ค่าชั่วโมง (0-23 หรือ 1-12) ตามโหมดที่ตั้ง  
**รายละเอียด**:
- อ่านค่าจากรีจิสเตอร์ที่อยู่ 0x02
- ตรวจสอบโหมด 12/24 ชั่วโมง (บิต 0x40)
- กรองบิตที่ไม่เกี่ยวข้อง (0x1F สำหรับโหมด 12 ชั่วโมง)
- แปลงจากรูปแบบ BCD เป็นฐานสิบ

---

### `get12_24hr()`
```cpp
uint8_t get12_24hr();
```
**หน้าที่**: ตรวจสอบโหมดเวลาปัจจุบัน  
**ค่าที่คืน**: 
- 1 = โหมด 12 ชั่วโมง
- 0 = โหมด 24 ชั่วโมง  
**รายละเอียด**:
- ตรวจสอบบิต 0x40 ในรีจิสเตอร์ชั่วโมง

---

### `getAM_PM()`
```cpp
uint8_t getAM_PM();
```
**หน้าที่**: ตรวจสอบช่วงเวลาสำหรับโหมด 12 ชั่วโมง  
**ค่าที่คืน**: 
- 1 = PM
- 0 = AM  
**รายละเอียด**:
- ตรวจสอบบิต 0x20 ในรีจิสเตอร์ชั่วโมง
- มีผลเฉพาะเมื่ออยู่ในโหมด 12 ชั่วโมงเท่านั้น

---

## ฟังก์ชันการอ่านค่าวันที่

### `getYear()`
```cpp
uint8_t getYear();
```
**หน้าที่**: อ่านค่าปีปัจจุบัน  
**ค่าที่คืน**: 
- ค่าปี (00-99) นับจากปี 2000  
**รายละเอียด**:
- อ่านค่าจากรีจิสเตอร์ที่อยู่ 0x06
- แปลงจากรูปแบบ BCD เป็นฐานสิบ

---

### `getMonth()`
```cpp
uint8_t getMonth();
```
**หน้าที่**: อ่านค่าเดือนปัจจุบัน  
**ค่าที่คืน**: 
- ค่าเดือน (1-12)  
**รายละเอียด**:
- อ่านค่าจากรีจิสเตอร์ที่อยู่ 0x05
- แปลงจากรูปแบบ BCD เป็นฐานสิบ

---

### `getDate()`
```cpp
uint8_t getDate();
```
**หน้าที่**: อ่านค่าวันที่ปัจจุบัน  
**ค่าที่คืน**: 
- ค่าวันที่ (1-31)  
**รายละเอียด**:
- อ่านค่าจากรีจิสเตอร์ที่อยู่ 0x04
- แปลงจากรูปแบบ BCD เป็นฐานสิบ

---

### `getDayOfWeek()`
```cpp
uint8_t getDayOfWeek();
```
**หน้าที่**: อ่านค่าวันในสัปดาห์  
**ค่าที่คืน**: 
- ค่าวันที่ (1-7) โดย 1 = อาทิตย์  
**รายละเอียด**:
- อ่านค่าจากรีจิสเตอร์ที่อยู่ 0x03
- แปลงจากรูปแบบ BCD เป็นฐานสิบ

---

## ฟังก์ชันตรวจสอบสถานะ

### `checkOsfStatus()`
```cpp
uint8_t checkOsfStatus();
```
**หน้าที่**: ตรวจสอบสถานะออสซิลเลเตอร์  
**ค่าที่คืน**: 
- 1 = ออสซิลเลเตอร์ทำงานปกติ
- 0 = ออสซิลเลเตอร์หยุดทำงาน  
**รายละเอียด**:
- อ่านค่าจากรีจิสเตอร์สถานะที่อยู่ 0x0F
- ตรวจสอบบิต 0x80 (Oscillator Stop Flag)

---

## ตัวอย่างการใช้งาน

```cpp
void displayTime() {
  Serial.print("เวลา: ");
  Serial.print(rtc.getHour());
  Serial.print(":");
  Serial.print(rtc.getMinute());
  Serial.print(":");
  Serial.println(rtc.getSecond());
  
  Serial.print("วันที่: ");
  Serial.print(rtc.getDate());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/20");
  Serial.println(rtc.getYear());
  
  if(rtc.checkOsfStatus() == 0) {
    Serial.println("คำเตือน: ออสซิลเลเตอร์หยุดทำงาน!");
  }
}
```

## หมายเหตุ
1. ค่าทั้งหมดที่คืนมาอยู่ในรูปแบบฐานสิบ
2. ฟังก์ชันเหล่านี้ไม่มีการแก้ไขข้อมูลใน RTC
3. ควรเรียกใช้ฟังก์ชันเหล่านี้เมื่อต้องการแสดงผลหรือประมวลผลเวลาเท่านั้น

## การต่อวงจร 
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
