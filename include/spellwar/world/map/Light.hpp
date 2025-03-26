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
#define LIGHT_DISTANCE_TO_WORLD 100000.0f

#define LIGHT_POSITION Point3D(0.0f, 500.0f, 0.0f)
#define DEFAULT_AMBIENT 0.25f
#define DEFAULT_SPECULAR_FACTOR 0.3f
#define DEFAULT_SPECULAR_EXPONENT 4

#define SUN_ROTATION 5.0f


using namespace wgame;

class Light : public GameObject {
public:
    Light(GameLight * gameLight, StaticModelGLTF * _sun, float scale);
    void update() override;
    void renderBackground() override;
private:
    StaticModelGLTF * _sun;
    ModelDrawer _drawer;
    ColorRGB _color;
    GameLight * _gameLight;
    float _angle;
    float _scale;
};

#endif
