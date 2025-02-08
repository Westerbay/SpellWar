/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/gui/MainFrame.hpp>
#include <spellwar/spell/Spell.hpp>


MainFrame::MainFrame(const char * title, const Size & size) :
    AbstractFrame(title, size) {
    addSprite(new Spell());
}

void MainFrame::renderScene() {
    displaySprites();
}

void MainFrame::renderHUD() {
}

