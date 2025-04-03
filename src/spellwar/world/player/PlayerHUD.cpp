/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/player/Player.hpp>


PlayerHUD::PlayerHUD() {
    Circle circle(Point2D(0.0f), 5.0f);
    _visionIndicator.setFillCircleData(
        circle, ColorRGB(1.0f), 40
    );
}

void PlayerHUD::render(const Size & screenSize) {
    Matrix4D transform(1.0f);
    Point3D middleScreen(screenSize.width, screenSize.height, 0.0f);
    middleScreen *= 0.5f;
    transform = glm::translate(transform, middleScreen);
    _visionIndicator.fill(transform, Drawer::HUD);
}
