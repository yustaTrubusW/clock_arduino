#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

class Button
{
private:
    int _pin;
    bool previousButtonState = HIGH;
public:
    Button(const int pin);
    void init();
    void OnPresed(void(*func)());
    bool read();
};


#endif