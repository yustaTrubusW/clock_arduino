#include "Arduino.h"
#include <rtc.h>
#include <lcd.h>
#include <button.h>

// button PIN
#define MENU_BUTTON 5
#define UP_BUTTON 3
#define DOWN_BUTTON 4

// ouput PIN
const int ledPin1 = 6;
const int ledPin2 = 7;
const int ledPin3 = 8;

// initialize all function
void settingDay();
void settingMonth();
void settingYear();
void settingDow();
void settingHour();
void settingMin();
void settingSec();
void home();
void handdlePreSellectOnMenu(int8_t index);
void handdleMenuOnSellect(int8_t index);
void showClock(int8_t hour, int8_t minute, int8_t second, int8_t nothing);
void showDate(int8_t day, int8_t month, int8_t year, int8_t dow);

// variabale untutk menyimpan data tanggal/bulan/tahun, dalam menu setting
int dd = 1;
int mm = 1;
int yy = 1;
int dow = 1;
int _hour = 0;
int _minute = 0;
int _second = 0;

// char dayOfWeeks[7][5] = {"MING", "SEN", "SEL", "RAB", "KAM", "JUM", "SAB"};
char dayOfWeeks[7][7] = {"MINGGU", "SENIN ", "SELASA", "RABU  ", "KAMIS ", "JUMAT ", "SABTU "};

// index menu
int menuAddress;

// custom charakter derajat
byte degreeChar[8] = {
    B00110,
    B01001,
    B01001,
    B00110,
    B00000,
    B00000,
    B00000,
    B00000};

CustomLiquidCrystal lcd(0x27, 16, 2);
CustomuRTCLib rtc(0x68);
Button menuButton(MENU_BUTTON);
Button upButton(UP_BUTTON);
Button downButton(DOWN_BUTTON);

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, degreeChar);
    URTCLIB_WIRE.begin();

    // initialize input PIN active LOW
    menuButton.init();
    upButton.init();
    menuButton.init();

    // initialize output PIN active LOW
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    digitalWrite(ledPin1, 1);
    digitalWrite(ledPin2, 1);
    digitalWrite(ledPin3, 1);

    //  rtc.set(0, 30, 21, 2, 28, 5, 24);
    //  RTCLib::set(byte second(), byte minute(), byte hour, byte dayOfWeek, byte dayOfMonth, byte month(), byt()e year())
}

void loop()
{
    while (1)
    {
        menuButton.OnPresed([]()
                            {
            menuAddress++;
            handdlePreSellectOnMenu(menuAddress); });

        handdleMenuOnSellect(menuAddress);
    }
}

void handdleMenuOnSellect(int8_t index)
{
    switch (index)
    {
    case 0:
        home();
        break;

    case 1:
        settingDay();
        break;

    case 2:
        settingMonth();
        break;

    case 3:
        settingYear();
        break;

    case 4:
        settingDow();
        break;
    case 5:
        settingHour();
        break;
    case 6:
        settingMin();
        break;
    case 7:
        settingSec();
        break;

    default:
        menuAddress = 0;
        lcd.clear();
        //  RTCLib::set(byte second(), byte minute(), byte hour, byte dayOfWeek, byte dayOfMonth, byte month(), byt()e year())
        rtc.set(_second, _minute, _hour, dow, dd, mm, yy);
        lcd.print("SETTING SAVED");
        delay(1000);
        lcd.clear();
        showDate(rtc.day(), rtc.month(), rtc.year(), rtc.dayOfWeek());
        break;
    }
}

void home()
{
    rtc.refresh();
    lcd.setCursor(0, 0);
    lcd.lcdRefresh(rtc.dateDataChanged(), showDate, rtc.day(), rtc.month(), rtc.year(), rtc.dayOfWeek());
    lcd.setCursor(0, 1);
    lcd.lcdRefresh(rtc.clockDataChanged(), showClock, rtc.hour(), rtc.minute(), rtc.second(), true);
}

void handdlePreSellectOnMenu(int8_t index)
{
    switch (index)
    {
    case 1:
        lcd.clear();
        rtc.refresh();
        dd = rtc.day();
        mm = rtc.month();
        yy = rtc.year();
        dow = rtc.dayOfWeek();
        settingDay();
        showDate(dd, mm, yy, dow);
        break;
    case 5:
        lcd.clear();
        rtc.refresh();
        _hour = rtc.hour();
        _minute = rtc.minute();
        _second = rtc.second();
        settingHour();
        showClock(_hour, _minute, _second, false);
        break;

    default:
        break;
    }
}

void showClock(int8_t hour, int8_t minute, int8_t second, int8_t showTemp)
{
    lcd.print(hour / 10);
    lcd.print(hour % 10);
    lcd.print(':');
    lcd.print(minute / 10);
    lcd.print(minute % 10);
    lcd.print(':');
    lcd.print(second / 10);
    lcd.print(second % 10);

    if (showTemp)
    {
        lcd.print("    ");
        lcd.print(rtc.temp() / 100);
        lcd.write(byte(0));
    }
}

void showDate(int8_t day, int8_t month, int8_t year, int8_t dow)
{
    lcd.print(day / 10);
    lcd.print(day % 10);
    lcd.print('/');
    lcd.print(month / 10);
    lcd.print(month % 10);
    lcd.print('/');
    lcd.print(year / 10);
    lcd.print(year % 10);
    lcd.print(" ");
    lcd.print(dayOfWeeks[dow - 1]);
}

void settingDate(int8_t index)
{
    lcd.setCursor(0, 0);
    lcd.print("SETTING DATE");
    lcd.setCursor(0, 1);
    switch (index)
    {
    case 0:
        lcd.print("DD ");
        break;

    case 1:
        lcd.print("MM ");
        break;

    case 2:
        lcd.print("YY ");
        break;

    case 3:
        lcd.print("DW ");
        break;

    default:
        break;
    }
}

void settingClock(int8_t index)
{
    lcd.setCursor(0, 0);
    lcd.print("SETTING CLOCK");
    lcd.setCursor(0, 1);
    switch (index)
    {
    case 0:
        lcd.print("Hour    ");
        break;
    case 1:
        lcd.print("Min     ");
        break;
    case 2:
        lcd.print("Sec     ");
        break;

    default:
        break;
    }
}

void settingDay()
{
    settingDate(0);
    lcd.lcdRefresh(!upButton.read() || !downButton.read(), showDate, dd, mm, yy, dow);
    upButton.OnPresed([]()
                      {
        dd++;
        if (dd >= 32)
        {
            dd = 1;
        } });

    downButton.OnPresed([]()
                        {
        dd--;
        if (dd <= 0)
        {
            dd = 31;
        } });
}

void settingMonth()
{
    settingDate(1);
    lcd.lcdRefresh(!upButton.read() || !downButton.read(), showDate, dd, mm, yy, dow);
    upButton.OnPresed([]()
                      {
        mm++;
        if (mm >= 13)
        {
            mm = 1;
        } });

    downButton.OnPresed([]
                        {
        mm--;
        if (mm <= 0)
        {
            mm = 12;
        } });
}

void settingYear()
{
    settingDate(2);
    lcd.lcdRefresh(!upButton.read() || !downButton.read(), showDate, dd, mm, yy, dow);

    upButton.OnPresed([]()
                      {
        yy++;
        if (yy >=100){
            yy=1;
        } });

    downButton.OnPresed([]
                        {
        yy--;
        if (yy <= 0)
        {
            yy = 99;
        } });
}

void settingDow()
{
    settingDate(3);
    lcd.lcdRefresh(!upButton.read() || !downButton.read(), showDate, dd, mm, yy, dow);

    upButton.OnPresed([]()
                      {
        dow++;
        if (dow >= 8)
        {
            dow = 1;
        } });

    downButton.OnPresed([]
                        {
        dow--;
        if (dow <= 0)
        {
            dow = 7;
        } });
}

void settingHour()
{
    settingClock(0);
    lcd.lcdRefresh(!upButton.read() || !downButton.read(), showClock, _hour, _minute, _second, false);

    upButton.OnPresed([]()
                      {
        _hour++;
        if (_hour >= 24)
        {
            _hour = 0;
        } });

    downButton.OnPresed([]
                        {
        _hour--;
        if (_hour <= -1)
        {
            _hour = 23;
        } });
}

void settingMin()
{
    settingClock(1);
    lcd.lcdRefresh(!upButton.read() || !downButton.read(), showClock, _hour, _minute, _second, false);

    upButton.OnPresed([]()
                      {
        _minute++;
        if (_minute >= 60)
        {
            _minute = 0;
        } });

    downButton.OnPresed([]
                        {
        _minute--;
        if (_minute <= -1)
        {
            _minute = 59;
        } });
}

void settingSec()
{
    settingClock(2);
    lcd.lcdRefresh(!upButton.read() || !downButton.read(), showClock, _hour, _minute, _second, false);

    upButton.OnPresed([]()
                      {
        _second++;
        if (_second >= 60)
        {
            _second = 0;
        } });

    downButton.OnPresed([]
                        {
        _second--;
        if (_second <= -1)
        {
            _second = 59;
        } });
}