#pragma once
#include <string>

class LCDMessage {
private:
    std::string line1;
    std::string line2;

public:
    LCDMessage();
    LCDMessage(const char* line1, const char* line2);
    LCDMessage(std::string line1, std::string line2);

    void setLine1(const char* line1);
    void setLine1(std::string line1);
    void setLine2(const char* line2);
    void setLine2(std::string line2);

    std::string getLine1();
    std::string getLine2();
};