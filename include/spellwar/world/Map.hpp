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

#define TEX_SCALE 10.0f

#define PLATFORM_DIFFUSE "assets/materials/platform/diffuse.bmp"
#define PLATFORM_NORMAL "assets/materials/platform/normal.bmp"
#define PLATFORM_HEIGHT "assets/materials/platform/height.bmp"


using namespace wgame;

class Map : public GameObject {
public:
    Map(const Hitbox & hitbox);
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
    void setUpPlatformTextures();
private:
	Stalagmite _stalagmite;
    std::vector<std::unique_ptr<Decoration>> _decorations;
	std::vector<Platform> _platforms;    
    std::shared_ptr<StaticCollision> _collision;
private:
	Texture2D _diffuse;    
    Texture2D _normal;
    Texture2D _height;
    ModelDrawer _modelDrawer;
    ColorDrawer _hitboxDrawer; 
    std::vector<TextureDrawer> _platformDrawers;       
};

#endif
