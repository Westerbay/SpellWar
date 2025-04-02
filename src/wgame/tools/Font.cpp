/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/tools/Font.hpp>


namespace wgame {

Font::Font(const char * fontPath, float fontSize) : Image(fontPath, false) {
    _fontSize = fontSize;
    _refChar = 0;
    _color = ColorRGB(1.0f);
    _fillColor = ColorRGBA(0.0f);
    _nbCharRow = 16;
    _nbCharColumn = 16;
}

unsigned char Font::getRowCharacterNumber() const {
    return _nbCharRow;
}

unsigned char Font::getColumnCharacterNumber() const {
    return _nbCharColumn;
}

unsigned char Font::getReferencedCharacter() const {
    return _refChar;
}

float Font::getSize() const {
    return _fontSize;
}

ColorRGB Font::getColor() const {
    return _color;
}

ColorRGBA Font::getFillColor() const {
    return _fillColor;
}

void Font::setRowCharacterNumber(unsigned char nbChar) {
    _nbCharRow = nbChar;
}

void Font::setColumnCharacterNumber(unsigned char nbChar) {
    _nbCharColumn = nbChar;
}

void Font::setReferencedCharacter(unsigned char character) {
    _refChar = character;
}

void Font::setColor(const ColorRGB & color) {
    _color = color;
}

void Font::setFillColor(const ColorRGBA & fillcolor) {
    _fillColor = fillcolor;
}

}
