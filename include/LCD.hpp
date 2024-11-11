#pragma once

#include <cstdint>
#include "ShiftReg.hpp"

#define LCD_CMD_DELAY_US 10

class LCD {
private:
    uint8_t e;
    uint8_t rw;
    uint8_t rs;
    ShiftReg* dataReg;

private:
    void gpioSetup();
    void awaken();
    void pulseEnable();

public:
    LCD(ShiftReg* dataReg, uint8_t e, uint8_t rw, uint8_t rs);

    // data methods
    void command(uint8_t byte);
    void writeChar(char c);
    void writeString(char* c);
    void functionSet(uint8_t byte);
    void entryModeSet(uint8_t byte);

    // control methods
    void clearDisplay();
    void returnHome();
    void enableDisplay();
    void disableDisplay();
};