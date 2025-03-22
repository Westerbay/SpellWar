/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/player/Player.hpp>


PlayerHUD::PlayerHUD() {
    Sphere sphere(Point3D(0.0f), 0.01f);
    _visionIndicator.setFillSphereData(
        sphere, ColorRGB(1.0f), 40, 40
    );
}

void PlayerHUD::render() {
    _visionIndicator.fill(Matrix4D(1.0f), Drawer::HUD);
}
