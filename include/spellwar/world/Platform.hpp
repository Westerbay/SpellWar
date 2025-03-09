/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __PLATFORM__
#define __PLATFORM__

#include <wgame/wgame.hpp>

#define MAX_ANGLE_ROTATION 45.0f
#define PROBABILITY_ROTATE 0.5f
#define X_Z_GAP 8
#define Y_GAP 20
#define MAX_ATTEMPTS 20

#define STALAGMITE_MIN_SCALE 0.8f
#define STALAGMITE_MAX_SCALE 1.5f

#define TREE_PROBABILITY 0.7f
#define TREE_MIN_SCALE 0.5f
#define TREE_MAX_SCALE 1.0f

#define STALAGMITE_MODEL "assets/model/decoration/stalagmite/scene.gltf"
#define TREE_MODEL "assets/model/decoration/pinkTree/scene.gltf"


using namespace wgame;

class Platform : public GameObject {
public:
    Platform(const Hitbox & hitbox);
    void generateStalagmite(
        std::vector<Matrix4D> & transforms,
        const Vector3D & size
    );
    void generateDecoration(
        std::vector<Matrix4D> & transforms, 
        const Vector3D & size, float probability,
        float minScale, float maxScale
    );
    void endGenerate();
private:
    std::vector<Hitbox> _decorationHitboxes;
};

#endif
