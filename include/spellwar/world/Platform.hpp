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
#define Y_GAP 20
#define MAX_ATTEMPTS 20


using namespace wgame;

class Platform : public GameObject {
public:
    Platform(const Hitbox & hitbox);
    Hitbox getPlayerSpawn() const;
    void generateStalagmite(
        std::vector<Matrix4D> & transforms,
        const Decoration & decoration
    );
    void generateDecoration(
        std::vector<Matrix4D> & transforms, 
        const Decoration & decoration
    );
	std::vector<Hitbox> & getDecorationHitboxes();    
private:
    std::vector<Hitbox> _decorationHitboxes;
    Hitbox _playerSpawn;
};

#endif
