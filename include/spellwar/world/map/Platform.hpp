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
#include "Decoration.hpp"

#define PROBABILITY_ROTATE 0.6f
#define HEIGHT_ROTATE_RATIO 0.3f
#define X_Z_GAP 5
#define Y_GAP 20
#define MAX_ATTEMPTS 40

#define SPAWN_SIZE Vector3D(3.0f, 2.0f, 3.0f)


using namespace wgame;

class Platform : public GameObject {
public:
    Platform(const Hitbox & hitbox, GameObject * camera);
    Hitbox getPlayerSpawn() const;
    std::vector<Hitbox> & getDecorationHitboxes();  
    void generateStalagmite(
        CollisionTree & collision,
        Decoration & decoration
    );
    void generateDecoration(
        CollisionTree & collision,
        std::vector<Matrix4D> & transforms, 
        Decoration & decoration
    );
    Hitbox getExtendedHitbox() const;
    bool onPlatform(const Hitbox & object) const;
    void renderStalagmite(ModelGLTF & model, int id);
    bool shouldRenderStalagmite();
private:
    GameObject * _camera;
    std::vector<Hitbox> _decorationHitboxes;
    float _maxHeightStalagmite;
    Hitbox _playerSpawn;
    ModelDrawer _modelDrawer;
};

#endif
