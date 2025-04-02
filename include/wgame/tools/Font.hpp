/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_FONT_H__
#define __WG_FONT_H__

#include "Util.hpp"
#include "Image.hpp"
#include "../geometry/Geometry.hpp"


namespace wgame {

class Font : public Image {
public:
    Font(const char * fontPath, float fontSize);
    unsigned char getRowCharacterNumber() const;
    unsigned char getColumnCharacterNumber() const;
    unsigned char getReferencedCharacter() const;
    float getSize() const;    
    ColorRGB getColor() const;
    ColorRGBA getFillColor() const;
    void setRowCharacterNumber(unsigned char nbChar);
    void setColumnCharacterNumber(unsigned char nbChar);
    void setReferencedCharacter(unsigned char character);
    void setColor(const ColorRGB & color);
    void setFillColor(const ColorRGBA & fillcolor);    
private:
    unsigned char _nbCharRow;
    unsigned char _nbCharColumn;
    unsigned char _refChar;
    float _fontSize;
    ColorRGB _color;
    ColorRGBA _fillColor;
};

}

#endif
