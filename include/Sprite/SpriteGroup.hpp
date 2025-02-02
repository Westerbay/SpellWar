/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#ifndef __SPRITE_GROUP_H__
#define __SPRITE_GROUP_H__

#include <Sprite/Sprite.hpp>

#include <unordered_set>

class SpriteGroup {
public:
    ~SpriteGroup();    
    void add(Sprite * sprite);
    void remove(Sprite * sprite);
    void update();
private:
    std::unordered_set<Sprite *> _sprites;
};

#endif
