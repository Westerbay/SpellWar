/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/gui/MainFrame.hpp>
#include <spellwar/sprites/PlatformSprite.hpp>

MainFrame::MainFrame(const char * title, const Size & size) :
    AbstractFrame(title, size) {
    setBackgroundColor(255, 255, 255);

    Cuboid cuboid(Point3D(0.0f, 0.0f, 0.0f), Point3D(0.5f, 0.5f, 0.5f));
    cuboid.rotate(glm::radians(45.0f), AXIS_XY);
    addSprite(new PlatformSprite(new Platform(cuboid)));
}

void MainFrame::renderWorld() {
    displaySprites();
}

void MainFrame::renderHUD() {
}

