#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "ShiftReg.hpp"
#include "LCD.hpp"

void pause() {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(1000);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(1000);
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

    display.command(0b0011'1100);

    display.command(0b0000'1110);

    display.command(0b0000'0110);

    display.command(0b0000'0001);
    sleep_ms(2);

    display.writeString("Hello, World!");
}
