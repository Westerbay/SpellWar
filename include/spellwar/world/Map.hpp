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
    ModelDrawer _modelStalagmiteDrawer;
    ModelDrawer _modelPinkTreeDrawer;
    ColorDrawer _hitboxDrawer;
    Stalagmite _stalagmite;
    PinkTree _pinkTree;
    std::vector<Platform> _platforms;
    std::vector<TextureDrawer> _platformDrawers;
    Texture2D _diffuse;
};

#endif
