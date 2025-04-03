/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_LABEL_H__
#define __WG_LABEL_H__

#include "Widget.hpp"
#include "../graphics/FontDrawer.hpp"


namespace wgame {

class Label : public Widget {
public:    
    void setPosition(const Point2D & position);
    void setText(const String & text);
    void rebuild(const Font & font); 
    void renderHUD(const Size & size) override;
protected:
    Label();
    Label * createLabel();      
    Point2D _position;
    String _text;  
private:
    FontDrawer _fontDrawer;
};

class LabelBuilder : public Label {
public:
    LabelBuilder();    
    Label * build(const Font & font);    
};

}

#endif