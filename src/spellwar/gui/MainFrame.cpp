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
    addSprite(new PlatformSprite(new Platform(
        Point3D(0.0f, 0.0f, 0.0f), 0.5f, 0.5f, 0.5f
    )));
}

void MainFrame::renderScene() {
    displaySprites();
}

void MainFrame::renderHUD() {
}

