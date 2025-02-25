/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/core/MainFrame.hpp>

MainFrame::MainFrame(const char * title, const Size & size) :
    AbstractFrame(title, size) {
    setBackgroundColor(255, 255, 255);    
    setCursorActive(false);
}
