/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/GameObject.hpp>


namespace wgame {

GameObject::GameObject(const Hitbox & hitbox): hitbox(hitbox) {}

Hitbox GameObject::getHitbox() const {
    return hitbox;
}

}
