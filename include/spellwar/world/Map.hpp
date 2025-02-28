/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __MAP_H__
#define __MAP_H__

#include <wgame/wgame.hpp>

#define MAX_ATTEMPTS 100
#define MAX_ANGLE_ROTATION 45.0f
#define PROBABILITY_ROTATE 0.5f
#define X_Z_GAP 5
#define Y_GAP 20


using namespace wgame;

class Map : public GameObject {
public:
    Map(const Hitbox & hitbox);
    ~Map();
    void generatePlatform(
        size_t maxNumberOfPlatforms,
        const Vector3D & minSize,
        const Vector3D & maxSize,
        unsigned maxAttempts = MAX_ATTEMPTS
    );    
    void render() override;
private:
    void generateStalagmite();
private:
    Hitbox _hitbox;
    StaticModelGLTF * _model;
    ModelDrawer _modelDrawer;
    std::vector<Cuboid> _platforms;
    std::vector<ColorDrawer> _drawers;
};

#endif
