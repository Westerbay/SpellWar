/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WORLD__
#define __WORLD__

#include "player/Player.hpp"
#include "map/Background.hpp"
#include "map/Map.hpp"
#include "map/Light.hpp"

#include <wgame/wgame.hpp>

#define MAP_SIZE Vector3D(100.0f, 75.0f, 100.0f)
#define MIN_PLATFORM_SIZE Vector3D(10.0f, 1.0f, 10.0f)
#define MAX_PLATFORM_SIZE Vector3D(30.0f, 1.0f, 30.0f)
#define MAX_NUMBER_OF_PLATFORMS 30
#define FAR_PLANE 600.0f


using namespace wgame;

class World : public GameObjectGroup {
public:
    World(GameCamera * camera, GameLight * light);
};

#endif
