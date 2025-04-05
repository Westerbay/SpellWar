/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/core/MainFrame.hpp>

MainFrame::MainFrame() :
    AbstractFrame(TITLE, DEFAULT_SIZE) {
}

void MainFrame::processEvent(Event event) {
    switch (event) {
        case IN_GAME_EVENT:
            setCursorActive(false);
            pollEvents();
            _system.resetMousePosition();
            break;
        case IN_MAINTITLE_EVENT:
            setCursorActive(true);
            pollEvents();
            _system.resetMousePosition();
            break;
    }    
}
