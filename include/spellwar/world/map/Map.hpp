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
#include "Platform.hpp"
#include "MapView.hpp"
#include "AbstractBiome.hpp"


using namespace wgame;

class Map : public GameObject {
public:
    friend class MapView;
public:
    Map(const Hitbox & hitbox, AbstractBiome * biome);
    void generatePlatform(
        size_t maxNumberOfPlatforms,
        const Vector3D & minSize,
        const Vector3D & maxSize,
        unsigned maxAttempts = MAX_ATTEMPTS
    );    
    void render() override;	
    std::vector<Platform> & getPlatforms();
    bool collide(const Hitbox & hitbox);
private:
    void constructPlatform(
        Cuboid & platform, Hitbox & hitboxPlatform,
        const Vector3D & minSize, const Vector3D & maxSize
    );
private:
    MapView _mapView;
    AbstractBiome * _biome;
	std::vector<Platform> _platforms;    
    std::shared_ptr<CollisionTree> _collision;	       
};


#endif
