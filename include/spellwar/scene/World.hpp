/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WORLD__
#define __WORLD__

#include "../world/player/Player.hpp"
#include "../world/map/Background.hpp"
#include "../world/map/Map.hpp"
#include "../world/map/Light.hpp"
#include "../world/biome/Space.hpp"

#include <wgame/wgame.hpp>

#define MAP_SIZE Vector3D(80.0f, 80.0f, 80.0f)
#define MIN_PLATFORM_SIZE Vector3D(12.0f, 1.0f, 12.0f)
#define MAX_PLATFORM_SIZE Vector3D(36.0f, 1.0f, 36.0f)
#define MAX_NUMBER_OF_PLATFORMS 20
#define FAR_PLANE 600.0f


using namespace wgame;

class World : public GameObjectGroup {
public:
    World(GameCamera * camera, GameLight * light);
    void setActive(bool active);
private:
    Player * _player;
};

#endif
