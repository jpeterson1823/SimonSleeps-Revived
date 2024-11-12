#include "logic/LCDMessage.hpp"
#include <cstdlib>
#include <cstdint>
#include <cstring>

// Default constructor
LCDMessage::LCDMessage() { }

// Copies first 16 chars of line1 and line2 into their respective variable
LCDMessage::LCDMessage(const char* line1, const char* line2) : LCDMessage() {
    // loop for 16 chars
    for (uint8_t i = 0; i < 16; i++) {
        // if char is not null, save to member var
        if (line1[i] != 0)
            this->line1 += line1[i];

        // if char is not null, save to member var
        if (line2[i] != 0)
            this->line2 += line2[i];
    }
}

LCDMessage::LCDMessage(std::string line1, std::string line2) : LCDMessage() {
    // copy first 16 chars of line1 into member variable
    line1.copy(this->line1.data(), 16);
    // copy first 16 chars of line2 into member variable
    line2.copy(this->line2.data(), 16);
}

std::string LCDMessage::getLine1() { return line1; }
std::string LCDMessage::getLine2() { return line2; }

// Copies first 16 chars of line1 into its respective variable
void LCDMessage::setLine1(const char* line1) {
    // copy first 16 chars into line1, filling in nullchar if 16 chars not reached
    strncpy(this->line1.data(), line1, 16);
}

// Copies first 16 chars of line 2 into its respective variable
void LCDMessage::setLine2(const char* line2) {
    strncpy(this->line2.data(), line2, 16);
}
