#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>

class CustomLiquidCrystal : public LiquidCrystal_I2C {
public:
    // Konstruktor yang sama seperti di LiquidCrystal
    CustomLiquidCrystal(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);
    void lcdRefresh(bool condition, void (*lcdFunction)(int8_t, int8_t, int8_t, int8_t), int8_t a, int8_t b, int8_t c, int8_t d);

};

#endif