#ifndef PT7C4339_H
#define PT7C4339_H

/* พัฒนาโดย นาย สุพงศ์ เฉลิมชัยนุวงศ์ 
   วันที่ 20 มีนาคม 2568
   โดเนทเพื่อขวัญกำลังใจได้ที่ ธนาคารกสิกร 0718251311 
   rtc  PT7C4339
*/
#include <Arduino.h>
#include <Wire.h>

#define PT7C4339_ADDR   0x68  // ที่อยู่ I2C ของ PT7C4339

#define FREQ32768kHZ    0x18
#define FREQ8192kHZ     0x10
#define FREQ4096kHZ     0x08
#define FREQ1HZ         0x00

//------------------------------------------------
#define Sunday    1
#define Monday    2
#define Tuesday   3
#define Wednesday 4
#define Thursday  5
#define Friday    6
#define Saturday  7
//------------------------------------------------

//------------------------------------------------
#define January   1
#define February  2
#define March     3
#define April     4
#define May       5
#define June      6
#define July      7
#define August    8
#define September 9
#define October   10
#define November  11
#define December  12
//------------------------------------------------


#define HR24      0
#define HR12      1
#define sysTimeAM 0
#define sysTimePM 1

class PT7C4339 {
public:
    PT7C4339();
    void begin();
    uint8_t decToBcd(uint8_t val);
    uint8_t bcdToDec(uint8_t val);
    void write_register(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
    void enableOscillator();
    void defaultTrickleCharger(uint8_t reg);
    void setClkout(uint8_t freq1);
    void clearAllAlarm();
    void clearAlarmFlags();
    uint8_t checkAlarm1Status();
    uint8_t checkAlarm2Status();
    void enableAlarmInterruptSqw(uint8_t alarm1_enable, uint8_t alarm2_enable);
    void clearControlReg();
    void setAlarm1(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t day_date, uint8_t mask);
    void setAlarm2(uint8_t minutes, uint8_t hours, uint8_t day_date, uint8_t mask);
    void setAlarm1_24_12(uint8_t day_date, uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t mask, bool is_24hr, bool is_pm);
    void setAlarm2_24_12(uint8_t day_date, uint8_t hours, uint8_t minutes, uint8_t mask, bool is_24hr, bool is_pm);
    void set24hrMode(uint8_t dayOfWeek, uint8_t date, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second);
    void set12hrMode(uint8_t dayOfWeek, uint8_t date, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second, uint8_t period);
    String readDateTime();
    uint8_t getSecond();
    uint8_t getMinute();
    uint8_t getHour();
    uint8_t get12_24hr();
    uint8_t getAM_PM();
    uint8_t getYear();
    uint8_t getMonth();
    uint8_t getDate();
    uint8_t getDayOfWeek();
    uint8_t checkOsfStatus();
};

#endif