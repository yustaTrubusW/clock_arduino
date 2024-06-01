#include <lcd.h>

CustomLiquidCrystal::CustomLiquidCrystal(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows)
    : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)
{
    // Anda bisa menambahkan kode inisialisasi khusus di sini jika diperlukan
}

void CustomLiquidCrystal::lcdRefresh(bool condition, void (*lcdFunction)(int8_t, int8_t, int8_t, int8_t), int8_t a, int8_t b, int8_t c, int8_t d)
{
    if (condition)
    {
        lcdFunction(a, b, c, d);
    }
    else
    {
        // do nothing
    }
}
