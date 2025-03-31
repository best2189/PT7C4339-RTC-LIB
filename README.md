# สุพงศ์ เฉลิมชัยนุวงศ์ 

Arduino library of PT7C4339 Real-Time Clock/calendar

   พัฒนาโดย นาย สุพงศ์ เฉลิมชัยนุวงศ์ 
   วันที่ 20 มีนาคม 2568
   โดเนทเพื่อขวัญกำลังใจได้ที่ ธนาคารกสิกร 0718251311 
   
## Examples

ฟังก์ชั่นการทำงาน (Function Documentation)
ฟังก์ชั่นพื้นฐาน (Basic Functions)
Function	Description	คำอธิบาย
begin()	Initialize I2C communication	เริ่มต้นการสื่อสาร I2C
decToBcd(val)	Convert decimal to BCD format	แปลงเลขฐานสิบเป็นรูปแบบ BCD
bcdToDec(val)	Convert BCD to decimal format	แปลงจาก BCD กลับเป็นเลขฐานสิบ
ฟังก์ชั่นการตั้งเวลา (Time Setting Functions)
Function	Description	คำอธิบาย
set24hrMode(dayOfWeek, date, month, year, hour, minute, second)	Set time in 24-hour format	ตั้งเวลาในรูปแบบ 24 ชั่วโมง
set12hrMode(dayOfWeek, date, month, year, hour, minute, second, period)	Set time in 12-hour format (0=AM, 1=PM)	ตั้งเวลาในรูปแบบ 12 ชั่วโมง
readDateTime()	Read complete date/time as string	อ่านวันเวลาแบบเต็มรูปแบบเป็นข้อความ
ฟังก์ชั่นอ่านค่า (Reading Functions)
Function	Description	คำอธิบาย
getSecond()	Get current seconds	อ่านค่าวินาทีปัจจุบัน
getMinute()	Get current minutes	อ่านค่านาทีปัจจุบัน
getHour()	Get current hour	อ่านค่าชั่วโมงปัจจุบัน
get12_24hr()	Check if 12/24 hour mode (1=12hr, 0=24hr)	ตรวจสอบโหมดเวลา
getAM_PM()	Check AM/PM in 12hr mode (1=PM, 0=AM)	ตรวจสอบ AM/PM
getDate()	Get current date	อ่านค่าวันที่ปัจจุบัน
getMonth()	Get current month	อ่านค่าเดือนปัจจุบัน
getYear()	Get current year (00-99)	อ่านค่าปีปัจจุบัน (00-99)
getDayOfWeek()	Get day of week (1=Sunday)	อ่านค่าวันในสัปดาห์
ฟังก์ชั่น Alarm (Alarm Functions)
Function	Description	คำอธิบาย
setAlarm1(sec, min, hour, day_date, mask)	Set Alarm 1 with mask	ตั้ง Alarm 1 พร้อม mask
setAlarm2(min, hour, day_date, mask)	Set Alarm 2 with mask	ตั้ง Alarm 2 พร้อม mask
setAlarm1_24_12()	Set Alarm 1 in 12/24hr mode	ตั้ง Alarm 1 แบบเลือกโหมดเวลา
setAlarm2_24_12()	Set Alarm 2 in 12/24hr mode	ตั้ง Alarm 2 แบบเลือกโหมดเวลา
checkAlarm1Status()	Check Alarm 1 trigger status	ตรวจสอบสถานะ Alarm 1
checkAlarm2Status()	Check Alarm 2 trigger status	ตรวจสอบสถานะ Alarm 2
clearAlarmFlags()	Clear alarm flags	ล้างสถานะ Alarm
ฟังก์ชั่นอื่นๆ (Other Functions)
Function	Description	คำอธิบาย
enableOscillator()	Enable clock oscillator	เปิดใช้งานออสซิลเลเตอร์
setClkout(freq)	Set CLKOUT frequency	ตั้งค่าความถี่สัญญาณนาฬิกา
defaultTrickleCharger(reg)	Configure trickle charger	ตั้งค่าเครื่องชาร์จแบตเตอรี่
checkOsfStatus()	Check oscillator stop flag	ตรวจสอบสถานะออสซิลเลเตอร์
