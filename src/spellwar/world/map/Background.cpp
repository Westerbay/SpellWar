/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/map/Background.hpp>


Background::Background(
    const char * cubeMapPX,
    const char * cubeMapNX,
    const char * cubeMapPY,
    const char * cubeMapNY,
    const char * cubeMapPZ,
    const char * cubeMapNZ
) : GameObject() {
    _cubeMap.setFaces(
        Image(cubeMapPX, false),
        Image(cubeMapNX, false),
        Image(cubeMapPY, false),
        Image(cubeMapNY, false),
        Image(cubeMapPZ, false),
        Image(cubeMapNZ, false)
    );
}

void Background::renderBackground() {
    _cubeMap.draw();
}
