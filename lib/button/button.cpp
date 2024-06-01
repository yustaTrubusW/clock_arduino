#include <button.h>

Button::Button(const int pin)
{
    _pin = pin;
}

void Button::init(){
    pinMode(_pin, INPUT);
}

void Button::OnPresed(void(*funct)()){
    int buttonState = digitalRead(_pin);

    if (buttonState != previousButtonState)
    {
        if (buttonState == LOW)
        {
            funct();
        }
        previousButtonState = buttonState;
    }
}

bool Button::read(){
    return digitalRead(_pin);
}

