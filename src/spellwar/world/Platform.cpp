/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Platform.hpp>


Platform::Platform(const Cuboid & platform) : _platform(platform) {
    Image image(TEXTURE_PLATFORM);
    _texture.setData(image);
    _texture.setRepeatMode(MIRRORED_REPEAT);
    _texture.setInterpolationMode(INTERPOLATION_LINEAR);
    //_colorDrawer.setFillCuboidData(_platform, {1.0f, 0.0f, 0.0f});
    //_hitboxDrawer.setDrawCuboidData(_platform);
    _textureDrawer.setCuboidData(_platform);
    //_textureDrawer.setTexCoordFlex({2.0f, 2.0f});
    _textureDrawer.setTexCoordFixed(_platform, {3.0f, 3.0f});
}

void Platform::update() {
}

void Platform::render() {
    //_textureDrawer.drawCuboid(_platform, _texture);
    //_colorDrawer.fillCuboid(_platform, {1.0f, 0.0f, 0.0f});
    //_colorDrawer.drawCuboid(_platform);
    //_colorDrawer.fill();
    //_hitboxDrawer.draw();
    _textureDrawer.draw(_texture);
    //_textureDrawer.drawCuboid(_platform, _texture);
}

