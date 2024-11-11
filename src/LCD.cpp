#include "LCD.hpp"
#include "pico/stdlib.h"

LCD::LCD(ShiftReg* dataReg, uint8_t e, uint8_t rw, uint8_t rs)
: dataReg(dataReg), e(e), rw(rw), rs(rs)
{
    gpioSetup();
    awaken();
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

// go through wake-up procedure shown in datasheet example.
void LCD::awaken() {
    command(0x30);  // wake up #1
    sleep_ms(10);        // busy flag not available, must wait 5ms
    command(0x30);  // wake up #2
    sleep_ms(10);      // busy flag not available, must wait 160us
    command(0x30);  // wake up #3
    sleep_us(250);      // busy flag not available, must wait 160us
}

// pulse enable pin for ~1000ns
void LCD::pulseEnable() {
    gpio_put(e, 1);
    sleep_us(5);
    gpio_put(e, 0);
    sleep_us(5);
}

// send command to lcd
void LCD::command(uint8_t byte) {
    // put data out on data bus
    dataReg->putByte(byte);

    // send command to lcd
    gpio_put(rs, 0);    // send instruction
    gpio_put(rw, 0);    // write
    pulseEnable();      // pulse enable pin
}

// send character to lcd
void LCD::writeChar(char c) {
    // put data out on data bus
    dataReg->putByte(c);
    
    // write character to lcd
    gpio_put(rs, 1);    // send data
    gpio_put(rw, 0);    // write
    pulseEnable();      // pulse enable pin
    sleep_us(50);
    gpio_put(rs, 0);
}

void LCD::writeString(char* c) {
    while (*c != '\0')
        writeChar(*c++);
}