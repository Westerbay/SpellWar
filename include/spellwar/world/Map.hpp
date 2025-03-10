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
#include <spellwar/world/Platform.hpp>

#define TEX_SCALE 10.0f


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
private:
	Stalagmite _stalagmite;
	PinkTree _pinkTree;
    Fern _fern;
    Rock _rock;
    RadianceTree _radianceTree;
    std::vector<Decoration *> _decorations;
	std::vector<Platform> _platforms;    
private:
	Texture2D _diffuse;
    ModelDrawer _modelDrawer;
    ColorDrawer _hitboxDrawer; 
    std::vector<TextureDrawer> _platformDrawers;       
};

#endif
