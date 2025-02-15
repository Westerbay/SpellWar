/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Platform.hpp>


Platform::Platform(const Cuboid & platform) : _platform(platform) {
    _color = {rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX};
}

void Platform::update() {
}

void Platform::render() {
    ColorDrawer colorDrawer;
    colorDrawer.fillCuboid(_platform, _color);
    colorDrawer.drawCuboid(_platform);
}

