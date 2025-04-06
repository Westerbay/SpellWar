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

#include "../scene/Scene.hpp"

#define TITLE "Spellwar"


using namespace wgame;

class MainFrame : public AbstractFrame {
public: 
    MainFrame(const Size & size = {0, 0});
    void processEvent(Event event) override;
private:
    System _system;
};

#endif

