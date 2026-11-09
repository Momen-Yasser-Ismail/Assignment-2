#include "../Headers/Screen.h"

Screen::Screen() : content_("") {}

void Screen::clear() {
    content_.clear();
}

void Screen::write(char c) {
    content_.push_back(c);
}

std::string Screen::getContent() const {
    return content_;
}