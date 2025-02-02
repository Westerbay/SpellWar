/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#include <WindowGL/MainFrame.hpp>
#include <LSystem/Spell.hpp>

MainFrame::MainFrame(const char * title, const Size & size) :
    AbstractMainFrame(title, size) {
    _spriteGroup.add(new Spell());
}

void MainFrame::renderLoop() {
    _spriteGroup.update();
}
