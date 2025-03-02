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

#define MAX_ATTEMPTS 100
#define MAX_ANGLE_ROTATION 45.0f
#define PROBABILITY_ROTATE 0.5f
#define X_Z_GAP 5
#define Y_GAP 40

#define TEX_SCALE 20.0f

#define STALAGMITE_MODEL "assets/model/stalagmite/scene.gltf"


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
protected:
    class Stalagmite : public StaticModelGLTF {
    public:
        Stalagmite();
        Vector3D getSize() const;
    };
private:
    void generateStalagmite();
private:
    ModelDrawer _modelDrawer;
    Stalagmite _stalagmite;
    std::vector<Cuboid> _platforms;
    std::vector<TextureDrawer> _drawers;
    Texture2D _texture;
};

#endif
