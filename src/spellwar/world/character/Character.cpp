/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/character/Character.hpp>


Character::Character(const String & modelPath, bool isCullable) : AnimatedModelGLTF(modelPath) {
    _isCullable = isCullable;
}

bool Character::isCullable() const {
    return _isCullable;
}
