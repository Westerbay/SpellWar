/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/widget/Label.hpp>


namespace wgame {

Label::Label() : Widget() {}

Label * Label::createLabel() {
    return new Label();
}

String Label::getText() const {
    return _text;
}

void Label::setPosition(const Point2D & position) {
    _position = position;
}

void Label::setText(const String & text) {
    _text = text;
}

void Label::setFont(const Font & font) {
    _font = font;
}

void Label::rebuild() {
    Font font = _font;
    int fontSize = (int) font.getSize() * _scale;
    font.setSize((float) fontSize);
    Point3D position(
        (int)(_position.x * _scale), 
        (int)(_position.y * _scale), 
        0.0f
    );
    _fontDrawer.setTextData(font, _text, position, hitbox);
}

void Label::renderHUD(const Size & size) {
    resize(size);
    _fontDrawer.draw();
}

LabelBuilder::LabelBuilder() : Label() {}

Label * LabelBuilder::build() {
    Label * newLabel = createLabel();
    newLabel -> setHorizontalResponsive(_horizontalResponsive);
    newLabel -> setDesignedSize(_designedSize);
    newLabel -> setText(_text);
    newLabel -> setPosition(_position);
    newLabel -> setFont(_font);
    newLabel -> rebuild();
    return newLabel;
}

}

