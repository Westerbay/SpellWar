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
#include <spellwar/world/Decoration.hpp>

#define MAX_ANGLE_ROTATION 45.0f
#define PROBABILITY_ROTATE 0.5f
#define X_Z_GAP 8
#define Y_GAP 20
#define MAX_ATTEMPTS 15


using namespace wgame;

class Platform : public GameObject {
public:
    Platform(const Hitbox & hitbox);
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
};

#endif
