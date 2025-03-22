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
#define X_Z_GAP 8
#define Y_GAP 25
#define MAX_ATTEMPTS 20


using namespace wgame;

class Platform : public GameObject {
public:
    Platform(const Hitbox & hitbox);
    Hitbox getPlayerSpawn() const;
    std::vector<Hitbox> & getDecorationHitboxes();  
    void generateStalagmite(
        StaticCollision & collision,
        std::vector<Matrix4D> & transforms,
        Decoration & decoration
    );
    void generateDecoration(
        StaticCollision & collision,
        std::vector<Matrix4D> & transforms, 
        Decoration & decoration
    );
    Hitbox getExtendedHitbox() const;
private:
    std::vector<Hitbox> _decorationHitboxes;
    std::vector<Hitbox> _collideHitboxex;
    float _maxHeightStalagmite;
    Hitbox _playerSpawn;
};

#endif
