/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __MAIN_FRAME__
#define __MAIN_FRAME__

#include <wgame/wgame.hpp>


using namespace wgame;

class MainFrame : public AbstractFrame {
public: 
    MainFrame(const char * title, const Size & size);
    void render() override;
};

#endif

