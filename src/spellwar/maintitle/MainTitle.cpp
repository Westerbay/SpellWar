/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/maintitle/Maintitle.hpp>


Maintitle::Maintitle() : GameObjectGroup() {
    Font font(FONT_PATH, 50.0f);    
    font.setReferencedCharacter(' ');
    font.setColumnCharacterNumber(8);

    LabelBuilder labelBuilder;
    labelBuilder.setText("Spellwar");
    labelBuilder.setPosition(Point2D(0.0f, 0.0f));
    add(labelBuilder.build(font));
}
 