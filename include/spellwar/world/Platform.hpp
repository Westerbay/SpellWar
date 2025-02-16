/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <wgame/wgame.hpp>

#define TEXTURE_PLATFORM "assets/textures/magical/1_diffuseOriginal.bmp"


using namespace wgame;

class Platform : public GameObject {
public:
    Platform(const Cuboid & platform);
    void update() override;
    void render() override;
private:
    Texture2D _texture;
    TextureDrawer _textureDrawer;
    ColorDrawer _colorDrawer;
    ColorDrawer _hitboxDrawer;
    Cuboid _platform;
};

#endif

