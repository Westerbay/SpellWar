/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_BUTTON_H__
#define __WG_BUTTON_H__

#include "Label.hpp"

namespace wgame {

class Button : public Label {
public:
    void setAction(const std::function<void()> & action);
    void update() override;
protected:
    Button();
    Button * createButton();  
    std::function<void()> _action;    
};

class ButtonBuilder : public Button {
public:
    ButtonBuilder();    
    Button * build(const Font & font);    
};

}

#endif
