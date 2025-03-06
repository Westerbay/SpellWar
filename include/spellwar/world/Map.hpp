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

#define MAX_ATTEMPTS 50
#define MAX_ANGLE_ROTATION 45.0f
#define PROBABILITY_ROTATE 0.5f
#define X_Z_GAP 8
#define Y_GAP 20

#define STALAGMITE_MODEL "assets/model/stalagmite/scene.gltf"
#define TREE_MODEL "assets/model/decoration/pinkTree/scene.gltf"

#define TEX_SCALE 10.0f

#define STALAGMITE_MIN_SCALE 0.8f
#define STALAGMITE_MAX_SCALE 1.5f

#define TREE_PROBABILITY 0.7f
#define TREE_MIN_SCALE 0.5f
#define TREE_MAX_SCALE 1.0f

#define STALAGMITE_ID 0
#define PINK_TREE_ID 1


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
    class PinkTree : public StaticModelGLTF {
    public:
        PinkTree();
        Vector3D getSize() const;
    };
private:
    void generateStalagmite();
    void generateTree();
private:
    ModelDrawer _modelStalagmiteDrawer;
    ModelDrawer _modelPinkTreeDrawer;
    ColorDrawer _hitboxDrawer;
    Stalagmite _stalagmite;
    PinkTree _pinkTree;
    std::vector<Cuboid> _platforms;
    std::vector<TextureDrawer> _drawers;
    Texture2D _diffuse;
    Texture2D _normal;
    Texture2D _height;
};

#endif
