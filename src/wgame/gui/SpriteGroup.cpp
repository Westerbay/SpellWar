/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/gui/SpriteGroup.hpp>


namespace wgame {

SpriteGroup::~SpriteGroup() {
    for (Sprite * sprite : _sprites) {
        delete sprite;
    }
}

void SpriteGroup::add(Sprite * sprite) {
    _sprites.insert(sprite);
}

void SpriteGroup::remove(Sprite * sprite) {
    _sprites.erase(sprite);
}

void SpriteGroup::render() {
    for (Sprite * sprite : _sprites) {
        sprite -> render();
    }
}

}
