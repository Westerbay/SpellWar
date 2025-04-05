/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_WIDGET_H__
#define __WG_WIDGET_H__


#include "../core/GameObject.hpp"
#include "../tools/System.hpp"


namespace wgame {

class Widget : public GameObject {
public:
    Widget();
    void setDesignedSize(const Size & designedSize);
    void setHorizontalResponsive(bool enable);
    void resize(const Size & size);
    bool hover();
    bool triggered();
    virtual void rebuild() = 0;
protected:
    System _system;
    Size _designedSize;
    bool _horizontalResponsive;
    float _scale;
};

}

#endif
