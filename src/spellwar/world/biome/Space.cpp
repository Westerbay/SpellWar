/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/biome/Space.hpp>


Space::Space(GameLight * gameLight) : AbstractBiome() {
    Image image(SPACE_PLATFORM_DIFFUSE);
    _diffuse.setType(TEXTURE_2D);
    _diffuse.setInterpolationMode(GL_LINEAR);
    _diffuse.setRepeatMode(GL_REPEAT);
    _diffuse.setData(image);    

    Image imageNormal(SPACE_PLATFORM_NORMAL);
    _normal.setType(TEXTURE_2D);
    _normal.setInterpolationMode(GL_LINEAR);
    _normal.setRepeatMode(GL_REPEAT);
    _normal.setData(imageNormal);

    Image imageHeight(SPACE_PLATFORM_HEIGHT);
    _height.setType(TEXTURE_2D);
    _height.setInterpolationMode(GL_LINEAR);
    _height.setRepeatMode(GL_REPEAT);
    _height.setData(imageHeight);

    add(new Light(gameLight, &_sun, SPACE_SUN_SCALE));
    add(new Background(
        SPACE_BACKGROUND_PX, SPACE_BACKGROUND_NX,
        SPACE_BACKGROUND_PY, SPACE_BACKGROUND_NY,
        SPACE_BACKGROUND_PZ, SPACE_BACKGROUND_NZ
    ));

    _decorations.push_back(&_redTree);
    _decorations.push_back(&_fantasyPlant);
    _decorations.push_back(&_rock);
    _decorations.push_back(&_waterPlant);

}

Decoration & Space::getStalagmite() {
    return _stalagmite;
}

std::vector<Decoration *> & Space::getDecorations() {
    return _decorations;
}

Texture2D * Space::getDiffusePlatform() {
    return &_diffuse;
} 

Texture2D * Space::getNormalPlatform() {
    return &_normal;
}

Texture2D * Space::getHeightPlatform() {
    return &_height;
}

Space::Sun::Sun() : StaticModelGLTF(SPACE_SUN_ASSET) {}

