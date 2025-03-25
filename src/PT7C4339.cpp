#include "PT7C4339.h"

PT7C4339::PT7C4339() 
{
    // Constructor
}

void PT7C4339::begin() 
{
    Wire.begin();
}

uint8_t PT7C4339::decToBcd(uint8_t val) 
{
    return ((val / 10 * 16) + (val % 10));
}

uint8_t PT7C4339::bcdToDec(uint8_t val) 
{
    return ((val / 16 * 10) + (val % 16));
}

void PT7C4339::write_register(uint8_t reg, uint8_t value) 
{
    Wire.beginTransmission(PT7C4339_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

uint8_t PT7C4339::readRegister(uint8_t reg) 
{
    Wire.beginTransmission(PT7C4339_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(PT7C4339_ADDR, 1);
    if (Wire.available()) 
    {
        return Wire.read();
    }
    return 0;
}

void PT7C4339::enableOscillator() 
{
    write_register(0x0E, 0x00);
}

void PT7C4339::defaultTrickleCharger(uint8_t reg) 
{
    write_register(0x10, reg);
}

void PT7C4339::setClkout(uint8_t freq1) 
{
    write_register(0x0E, freq1);
}

void PT7C4339::clearAllAlarm() 
{
    setAlarm1(0x00, 0x00, 0x00, 0x00, 0x00);
    setAlarm2(0x00, 0x00, 0x00, 0x00);
    enableAlarmInterruptSqw(0x00, 0x00);
    clearAlarmFlags();
    clearControlReg();
}

void PT7C4339::clearAlarmFlags() 
{
    uint8_t status = readRegister(0x0F);
    status &= ~0x03;
    write_register(0x0F, status);
}

uint8_t PT7C4339::checkAlarm1Status() 
{
    uint8_t status = readRegister(0x0F);
    uint8_t bufdata1 = 0;
    if (bcdToDec(status & 0x01)) 
    {
        clearAlarmFlags();
        bufdata1 = 1;
    }
    else
    {
        bufdata1 = 0;
    }
return bufdata1;
}

uint8_t PT7C4339::checkAlarm2Status() 
{
    uint8_t status = readRegister(0x0F);
    uint8_t bufdata2 = 0;
    if (status & 0x02) 
    {
        clearAlarmFlags();
          bufdata2 = 1;
    }
    else
    {
         bufdata2   = 0;
    }
return bufdata2;
}



void PT7C4339::enableAlarmInterruptSqw(uint8_t alarm1_enable, uint8_t alarm2_enable) 
{
    uint8_t control = readRegister(0x0E);
    control &= ~0x03;
    control |= (alarm1_enable ? 0x01 : 0x00) | (alarm2_enable ? 0x02 : 0x00);
    control |= 0x04;
    write_register(0x0E, control);
}

void PT7C4339::clearControlReg() 
{
    write_register(0x0E, 0x00);
}

void PT7C4339::setAlarm1(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t day_date, uint8_t mask) 
{
    write_register(0x07, decToBcd((mask & 0x80) | (seconds & 0x7F)));
    write_register(0x08, decToBcd((mask & 0x80) | (minutes & 0x7F)));
    write_register(0x09, decToBcd((mask & 0x80) | (hours & 0x7F)));
    write_register(0x0A, decToBcd((mask & 0x80) | (day_date & 0x7F)));
}

void PT7C4339::setAlarm2(uint8_t minutes, uint8_t hours, uint8_t day_date, uint8_t mask) 
{
    write_register(0x0B, decToBcd((mask & 0x80) | (minutes & 0x7F)));
    write_register(0x0C, decToBcd((mask & 0x80) | (hours & 0x7F)));
    write_register(0x0D, decToBcd((mask & 0x80) | (day_date & 0x7F)));
}

void PT7C4339::setAlarm1_24_12(uint8_t day_date, uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t mask, bool is_24hr, bool is_pm) {
    uint8_t bcd_seconds = decToBcd((mask & 0x80) | (seconds & 0x7F));
    uint8_t bcd_minutes = decToBcd((mask & 0x80) | (minutes & 0x7F));
    uint8_t bcd_hours;

    if (is_24hr) 
    {
        bcd_hours = decToBcd((mask & 0x80) | (hours & 0x3F));
    } 
    else 
    {
        bcd_hours = decToBcd((mask & 0x80) | (hours & 0x1F));
        if (is_pm) 
        {
            bcd_hours |= 0x20;
        }
        bcd_hours |= 0x40;
    }

    write_register(0x07, bcd_seconds);
    write_register(0x08, bcd_minutes);
    write_register(0x09, bcd_hours);
    write_register(0x0A, decToBcd((mask & 0x80) | (day_date & 0x7F)));
}

void PT7C4339::setAlarm2_24_12(uint8_t day_date, uint8_t hours, uint8_t minutes, uint8_t mask, bool is_24hr, bool is_pm) {
    uint8_t bcd_minutes = decToBcd((mask & 0x80) | (minutes & 0x7F));
    uint8_t bcd_hours;

    if (is_24hr) 
    {
        bcd_hours = decToBcd((mask & 0x80) | (hours & 0x3F));
    } else {
        bcd_hours = decToBcd((mask & 0x80) | (hours & 0x1F));
        if (is_pm) 
        {
            bcd_hours |= 0x20;
        }
        bcd_hours |= 0x40;
    }

    write_register(0x0B, bcd_minutes);
    write_register(0x0C, bcd_hours);
    write_register(0x0D, decToBcd((mask & 0x80) | (day_date & 0x7F)));
}

void PT7C4339::set24hrMode(uint8_t dayOfWeek, uint8_t date, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second) {
    if(year<2000)year=2000;
    year = year - 2000;
    if (second > 59 || minute > 59 || hour > 23 || dayOfWeek < 1 || dayOfWeek > 7 || date < 1 || date > 31 || month < 1 || month > 12 || year > 99) {
        return;
    }
    uint8_t hour_bcd = decToBcd(hour & 0x1F);
    write_register(0x00, decToBcd(second));
    write_register(0x01, decToBcd(minute));
    write_register(0x02, hour_bcd);
    write_register(0x03, decToBcd(dayOfWeek));
    write_register(0x04, decToBcd(date));
    write_register(0x05, decToBcd(month));
    write_register(0x06, decToBcd(year));
}

void PT7C4339::set12hrMode(uint8_t dayOfWeek, uint8_t date, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second, uint8_t period) {
    if(year<2000)year=2000;
    year = year - 2000;
    if (second > 59 || minute > 59 || hour < 1 || hour > 12 || dayOfWeek < 1 || dayOfWeek > 7 || date < 1 || date > 31 || month < 1 || month > 12 || year > 99) {
        return;
    }
    uint8_t hour_bcd = decToBcd(hour);
    hour_bcd |= 0x40;
    if (period == 1) {
        hour_bcd |= 0x20;
    } else {
        hour_bcd &= ~0x20;
    }
    write_register(0x00, decToBcd(second));
    write_register(0x01, decToBcd(minute));
    write_register(0x02, hour_bcd);
    write_register(0x03, decToBcd(dayOfWeek));
    write_register(0x04, decToBcd(date));
    write_register(0x05, decToBcd(month));
    write_register(0x06, decToBcd(year));
}

String PT7C4339::readDateTime() {
    const char* dayNames[8] = {
        "Undefined", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };
    char timeStr[20];
    char dateStr[20];
    char fullStr[50];
    Wire.beginTransmission(PT7C4339_ADDR);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(PT7C4339_ADDR, 7);
    if (Wire.available() >= 7) {
        uint8_t rawSec = Wire.read();
        uint8_t rawMin = Wire.read();
        uint8_t rawHour = Wire.read();
        uint8_t rawDay = Wire.read();
        uint8_t rawDate = Wire.read();
        uint8_t rawMonth = Wire.read();
        uint8_t rawYear = Wire.read();

        uint8_t sec = bcdToDec(rawSec & 0x7F);
        uint8_t minute = bcdToDec(rawMin);

        bool is12hrMode = (rawHour & 0x40) != 0;
        bool isPM = (rawHour & 0x20) != 0;
        if (is12hrMode) {
            rawHour = rawHour & 0x1F;
        }

        uint8_t hour = bcdToDec(rawHour);
        uint8_t dayOfWeek = bcdToDec(rawDay);
        uint8_t date = bcdToDec(rawDate);
        uint8_t month = bcdToDec(rawMonth);
        uint8_t year = bcdToDec(rawYear);

     

        if (is12hrMode) {
            if (hour == 0) hour = 12;
            else if (hour > 12) hour -= 12;
            sprintf(timeStr, "%02d:%02d:%02d %s", hour, minute, sec, isPM?"PM":"AM");
        } else {
            sprintf(timeStr, "%02d:%02d:%02d", hour, minute, sec);
        }

        sprintf(dateStr, "%02d/%02d/20%02d", date, month, year);
        const char* dayStr = (dayOfWeek >= 1 && dayOfWeek <= 7) ?dayNames[dayOfWeek]:"Invalid";
        sprintf(fullStr, "%s %s %s", dayStr, dateStr, timeStr);
    }
  return fullStr;
}

uint8_t PT7C4339::getSecond() {
    uint8_t bufdata = readRegister(0x00);
    return bcdToDec(bufdata & 0x7F);
}

uint8_t PT7C4339::getMinute() {
    uint8_t bufdata = readRegister(0x01);
    return bcdToDec(bufdata);
}

uint8_t PT7C4339::getHour() {
    uint8_t bufdata = readRegister(0x02);
    bool is12hrMode = (bufdata & 0x40) != 0;
    if (is12hrMode) {
        bufdata = bufdata & 0x1F;
    }
    return bcdToDec(bufdata);
}

uint8_t PT7C4339::get12_24hr() {
    uint8_t bufdata = readRegister(0x02);
    bool is12hrMode = (bufdata & 0x40) != 0;
    return is12hrMode ? 1 : 0;
}

uint8_t PT7C4339::getAM_PM() {
    uint8_t bufdata = readRegister(0x02);
    bool isPM = (bufdata & 0x20) != 0;
    return isPM ? 1 : 0;
}

uint8_t PT7C4339::getYear() {
    uint8_t bufdata = readRegister(0x06);
    return bcdToDec(bufdata);
}

uint8_t PT7C4339::getMonth() {
    uint8_t bufdata = readRegister(0x05);
    return bcdToDec(bufdata);
}

uint8_t PT7C4339::getDate() {
    uint8_t bufdata = readRegister(0x04);
    return bcdToDec(bufdata);
}

uint8_t PT7C4339::getDayOfWeek() {
    uint8_t bufdata = readRegister(0x03);
    return bcdToDec(bufdata);
}

uint8_t PT7C4339::checkOsfStatus()
{
    uint8_t osfstate = 0;
    uint8_t status = readRegister(0x0F);
    if ((bcdToDec(status) & 0x80) != 0)
    {
      osfstate = 0;
    } 
    else 
    {
      osfstate = 1;
    }
return osfstate;
}