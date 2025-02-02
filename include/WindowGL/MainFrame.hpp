/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#ifndef __MAIN_FRAME__
#define __MAIN_FRAME__

#include <WindowGL/AbstractMainFrame.hpp>
#include <Sprite/SpriteGroup.hpp>

class MainFrame : public AbstractMainFrame {
public: 
    MainFrame(const char * title, const Size & size);
    void renderLoop() override;
private:
    SpriteGroup _spriteGroup;
};

#endif
