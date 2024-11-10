#include "LCD.hpp"
#include "pico/stdlib.h"

LCD::LCD(ShiftReg* dataReg, uint8_t e, uint8_t rw, uint8_t rs)
: dataReg(dataReg), e(e), rw(rw), rs(rs)
{
    gpioSetup();

    // set up LCD
}

// general setup of GPIO pins
void LCD::gpioSetup() {
    gpio_init(e);
    gpio_init(rw);
    gpio_init(rs);

    gpio_set_dir(e, GPIO_OUT);
    gpio_set_dir(rw, GPIO_OUT);
    gpio_set_dir(rs, GPIO_OUT);

    gpio_pull_down(e);
    gpio_pull_down(rw);
    gpio_pull_down(rs);

    gpio_put(e, 0);
    gpio_put(rw, 0);
    gpio_put(rs, 0);
}

void LCD::sendByte(uint8_t byte) {
    dataReg->putByte(byte);
}

void LCD::setRS() { gpio_put(rs, 1); }
void LCD::setRW() { gpio_put(rw, 1); }
void LCD::setE()  { gpio_put(e,  1); }
void LCD::unsetRS() { gpio_put(rs, 0); }
void LCD::unsetRW() { gpio_put(rw, 0); }
void LCD::unsetE()  { gpio_put(e,  0); }

void LCD::functionSet(uint8_t byte) {
    // unset RS and RW and set enable
    unsetRS();
    unsetRW();
    setE();

    // write masked byte to data bus
    dataReg->putByte(0x20 & byte);
    sleep_us(1);

    // unset enable
    unsetE();
}

void LCD::entryModeSet(uint8_t byte) {
    // unset RS and RW and set enable
    unsetRS();
    unsetRW();
    setE();

    // write masked byte to data bus
    dataReg->putByte(0x04 & byte);

    // unset enable
    unsetE();
}