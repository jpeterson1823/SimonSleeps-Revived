#include <cstdio>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "AlarmModule.hpp"

#define PAUSE_MS 250

void pause() {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(PAUSE_MS);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(PAUSE_MS);
}


int main()
{
    // initialize gpio
    stdio_init_all();
    cyw43_arch_init();

    pause();

    // lcd test code
    ShiftReg lcdDataReg(0, 1, 2);
    LCD display(&lcdDataReg, 8, 7, 6);

    //display.command(0b0011'1100);
    display.functionSet(true,true,true);

    //display.command(0b0000'1110);
    display.displaySet(true, true, false);

    //display.command(0b0000'0110);
    display.entryModeSet(true, false);

    //display.command(0b0000'0001);
    //sleep_ms(2);
    display.clearDisplay();

    //LCDMessage msg("This is line #1.", "This is line #2.");
    //display.writeMessage(msg);

    display.setCursorPos(0, 3);
    display.writeChar('1');
    display.setCursorPos(1, 7);
    display.writeChar('2');

    pause();
}
