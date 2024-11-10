#pragma once

#include <cstdint>
#include "ShiftReg.hpp"

class LCD {
private:
    uint8_t e;
    uint8_t rw;
    uint8_t rs;
    ShiftReg* dataReg;

private:
    void gpioSetup();
    void setRS();
    void setRW();
    void setE();
    void unsetRS();
    void unsetRW();
    void unsetE();

public:
    LCD(ShiftReg* dataReg, uint8_t e, uint8_t rw, uint8_t rs);

    // data methods
    void sendByte(uint8_t byte);
    void putByte(uint8_t byte);
    void functionSet(uint8_t byte);
    void entryModeSet(uint8_t byte);

    // control methods
    void clearDisplay();
    void returnHome();
    void enableDisplay();
    void disableDisplay();
};