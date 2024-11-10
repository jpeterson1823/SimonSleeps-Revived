#include "ShiftReg.hpp"
#include "pico/stdlib.h"

ShiftReg::ShiftReg(uint8_t ser, uint8_t oe, uint8_t rclk, uint8_t srclk, uint8_t srclr)
    : ser(ser), oe(oe), rclk(rclk), srclk(srclk), srclr(srclr)
{
    // initialize gpio pins
    gpio_init(ser);
    gpio_init(oe);
    gpio_init(rclk);
    gpio_init(srclk);
    gpio_init(srclr);

    // set pins to output
    gpio_set_dir(ser,   GPIO_OUT);
    gpio_set_dir(oe,    GPIO_OUT);
    gpio_set_dir(rclk,  GPIO_OUT);
    gpio_set_dir(srclk, GPIO_OUT);
    gpio_set_dir(srclr, GPIO_OUT);

    // set pull-up on active-low pins
    gpio_pull_up(oe);
    gpio_pull_up(srclr);

    // set pull-down on active-high pins
    gpio_pull_down(ser);
    gpio_pull_down(rclk);
    gpio_pull_down(srclk);

    // set default pin states
    gpio_put(ser,   0);
    gpio_put(oe,    1);
    gpio_put(rclk,  0);
    gpio_put(srclk, 0);
    gpio_put(srclr, 1);
}

void ShiftReg::enableOutput()  { gpio_put(oe, 0); }
void ShiftReg::disableOutput() { gpio_put(oe, 1); }

// Pulses clock by SR_DELAY_US microseconds
void ShiftReg::pulseClock() {
    gpio_put(srclk, 1);
    sleep_us(SR_DELAY_US);
    gpio_put(srclk, 0);
    sleep_us(SR_DELAY_US);
}

// Latches current shift register's state to the output register
void ShiftReg::latch() {
    gpio_put(rclk, 1);
    sleep_us(SR_DELAY_US);
    gpio_put(rclk, 0);
    sleep_us(SR_DELAY_US);
}

// Clears shift register
void ShiftReg::clear() {
    gpio_put(srclr, 0);
    sleep_us(SR_DELAY_US);
    gpio_put(srclr, 1);
    sleep_us(SR_DELAY_US);
}

// Loads byte into shift register without latching to output. LSB first
void ShiftReg::shiftByte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        gpio_put(ser, byte&(0x01<<i));
        pulseClock();
    }
}

// Loads a single bit into the shift register.
void ShiftReg::shiftBit(bool bit) {
    gpio_put(ser, bit);
    pulseClock();
}

// Loads AND latches byte into shift register. LSB fisrt.
void ShiftReg::putByte(uint8_t byte) {
    shiftByte(byte);
    latch();
}

// Loads AND latches a single bit into shift register.
void ShiftReg::putBit(bool bit) {
    shiftBit(bit);
    latch();
}