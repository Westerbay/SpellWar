/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <wgame/wgame.hpp>

#define STEP_TIME 0.01f
#define LIGHT_SIZE 0.1f
#define LIGHT_DISTANCE_TO_WORLD 100000.0f


using namespace wgame;

class Light : public GameObject {
public:
    Light(GameLight * gameLight);
    void update() override;
    void renderBackground() override;
private:
    ColorDrawer _drawer;
    ColorRGB _color;
    GameLight * _gameLight;
    float _angle;
};

#endif
