#pragma once

#include <string>

class Screen {
private:
    std::string content_;

public:
    Screen();
    void clear();
    void write(char c);
    std::string getContent() const;
};