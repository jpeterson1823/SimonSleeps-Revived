#pragma once
#include <cstdint>

#define SR_DELAY_US 1

class ShiftReg {
private:
    uint8_t ser;
    uint8_t oe;
    uint8_t rclk;
    uint8_t srclk;
    uint8_t srclr;

public:
    ShiftReg(uint8_t ser, uint8_t oe, uint8_t rclk, uint8_t srclk, uint8_t srclr);

    void shiftByte(uint8_t byte);
    void putByte(uint8_t byte);
    void shiftBit(bool bit);
    void putBit(bool bit);
    void latch();
    void clear();
    void pulseClock();
    void enableOutput();
    void disableOutput();
};