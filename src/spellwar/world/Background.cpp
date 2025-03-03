/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Background.hpp>


Background::Background() : GameObject() {
    _cubeMap.setFaces(
        Image("assets/background/px.png", false),
        Image("assets/background/nx.png", false),
        Image("assets/background/py.png", false),
        Image("assets/background/ny.png", false),
        Image("assets/background/pz.png", false),
        Image("assets/background/nz.png", false)
    );
}

void Background::renderBackground() {
    _cubeMap.draw();
}
