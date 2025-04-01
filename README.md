

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

![PT7C4339 RTC Module](https://example.com/rtc_module.jpg)

## ข้อมูลทั่วไป
- **ผู้พัฒนา**: สุพงศ์ เฉลิมชัยนุวงศ์
- **เวอร์ชัน**: 1.0
- **วันที่ปรับปรุงล่าสุด**: 20 มีนาคม 2568

## 1. ฟังก์ชันพื้นฐาน

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

---

### `decToBcd()`
```cpp
uint8_t PT7C4339::decToBcd(uint8_t val)
```
**คำอธิบาย**: แปลงค่าจากฐานสิบเป็น BCD  
**พารามิเตอร์**:
- `val`: ค่าในรูปแบบฐานสิบ (0-99)  
**คืนค่า**: ค่าในรูปแบบ BCD  
**ตัวอย่าง**:
```cpp
uint8_t bcd = rtc.decToBcd(45); // ได้ค่า 0x45
```

---

### `bcdToDec()`
```cpp
uint8_t PT7C4339::bcdToDec(uint8_t val)
```
**คำอธิบาย**: แปลงค่าจาก BCD เป็นฐานสิบ  
**พารามิเตอร์**:
- `val`: ค่าในรูปแบบ BCD  
**คืนค่า**: ค่าในรูปแบบฐานสิบ  
**ตัวอย่าง**:
```cpp
uint8_t dec = rtc.bcdToDec(0x59); // ได้ค่า 59
```

---

## 2. ฟังก์ชันการอ่าน/เขียนรีจิสเตอร์

### `write_register()`
```cpp
void PT7C4339::write_register(uint8_t reg, uint8_t value)
```
**คำอธิบาย**: เขียนข้อมูลลงรีจิสเตอร์  
**พารามิเตอร์**:
- `reg`: ที่อยู่รีจิสเตอร์
- `value`: ค่าที่ต้องการเขียน  
**คืนค่า**: ไม่มี

---

### `readRegister()`
```cpp
uint8_t PT7C4339::readRegister(uint8_t reg)
```
**คำอธิบาย**: อ่านค่าจากรีจิสเตอร์  
**พารามิเตอร์**:
- `reg`: ที่อยู่รีจิสเตอร์  
**คืนค่า**: ค่าที่อ่านได้จากรีจิสเตอร์

---

## 3. ฟังก์ชันการตั้งค่าเวลา

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

## 4. ฟังก์ชันการอ่านเวลา

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

---

## 5. ฟังก์ชัน Alarm

### `setAlarm1()`
```cpp
void PT7C4339::setAlarm1(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t day_date, uint8_t mask)
```
**คำอธิบาย**: ตั้งค่า Alarm 1  
**พารามิเตอร์**:
- `mask`: บิต mask สำหรับกำหนดเงื่อนไขการเตือน

---

### `checkAlarm1Status()`
```cpp
uint8_t PT7C4339::checkAlarm1Status()
```
**คำอธิบาย**: ตรวจสอบสถานะ Alarm 1  
**คืนค่า**: 1 = Alarm ทำงาน, 0 = ไม่ทำงาน

---

## 6. ฟังก์ชันอื่นๆ

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
