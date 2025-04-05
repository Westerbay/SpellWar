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

void Label::rebuild(const Font & font) {
    _fontDrawer.setTextData(font, _text, Point3D(_position, 0.0f), hitbox);
}

void Label::renderHUD(const Size & size) {
    Matrix4D transform(1.0f);
    transform = glm::scale(transform, Vector3D(getScale(size)));
    _fontDrawer.draw(transform);
}

LabelBuilder::LabelBuilder() : Label() {}

Label * LabelBuilder::build(const Font & font) {
    Label * newLabel = createLabel();
    newLabel -> setHorizontalResponsive(_horizontalResponsive);
    newLabel -> setDesignedSize(_designedSize);
    newLabel -> setText(_text);
    newLabel -> setPosition(_position);
    newLabel -> rebuild(font);
    return newLabel;
}

}

