/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __BACKGROUND__
#define __BACKGROUND__
 
#include <wgame/wgame.hpp>
 
 
using namespace wgame;
 
class Background : public GameObject {
public:
    Background(
        const char * cubeMapPX,
        const char * cubeMapNX,
        const char * cubeMapPY,
        const char * cubeMapNY,
        const char * cubeMapPZ,
        const char * cubeMapNZ
    );
    void renderBackground() override;
private:
    CubeMapDrawer _cubeMap;
};
 
#endif
 