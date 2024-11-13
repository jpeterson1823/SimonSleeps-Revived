#include <cstdio>
#include "pico/stdlib.h"

#include "AlarmModule.hpp"

#define PAUSE_MS 250

void pause() {
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    sleep_ms(PAUSE_MS);
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
    sleep_ms(PAUSE_MS);
}

void lcd_test() {
    // create message obj
    LCDMessage lcdText(
        "  Simon Sleeps  ",
        "--- REVIVED! ---"
    );

    // create shiftreg object
    ShiftReg lcdDataReg(0, 1, 2);

    // create lcd object and do setup
    LCD lcd(&lcdDataReg, 8, 7, 6);
    lcd.defaultSetup();
    lcd.clear();

    // write message to lcd
    lcd.writeMessage(lcdText);
}


int main()
{
    // initialize gpio
    stdio_init_all();
    pause();

    lcd_test();

    pause();
}
