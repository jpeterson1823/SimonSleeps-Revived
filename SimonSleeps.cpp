#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "ShiftReg.hpp"

struct lcd {
    ShiftReg* dataReg;
    uint8_t e;
    uint8_t rw;
    uint8_t rs;
};

void lcd_send_cmd(struct lcd& display, uint8_t byte) {
    gpio_put(display.e, 1);
    sleep_ms(5);
    display.dataReg->putByte(byte);
    gpio_put(display.e, 0);
};

int main()
{
    // initialize gpio
    stdio_init_all();
    cyw43_arch_init();

    // lcd testing
    uint8_t e = 7;
    uint8_t rw = 6;
    uint8_t rs = 5;

    lcd display;
    display.e = e;
    display.rw = rw;
    display.rs = rs;

    gpio_init(e);
    gpio_init(rw);
    gpio_init(rs);
    gpio_set_dir(e, GPIO_OUT);
    gpio_set_dir(rw, GPIO_OUT);
    gpio_set_dir(rs, GPIO_OUT);
    gpio_pull_down(e);
    gpio_pull_down(rw);
    gpio_pull_down(rs);

    gpio_put(e,0);
    gpio_put(rw,0);
    gpio_put(rs,0);

    sleep_ms(1000);

    ShiftReg lcdDataReg(0,1,2,3,4);
    lcdDataReg.enableOutput();
    display.dataReg = &lcdDataReg;

    lcd_send_cmd(display, 0b00111000);
    lcd_send_cmd(display, 0b00001111);
    lcd_send_cmd(display, 0b00000110);
    lcd_send_cmd(display, 0b00000001);
    sleep_ms(5);

    gpio_put(display.rs, 1);
    lcd_send_cmd(display, 'H');
    gpio_put(display.rs, 0);
}
