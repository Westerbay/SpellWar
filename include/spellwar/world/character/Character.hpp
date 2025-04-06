/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <wgame/wgame.hpp>


using namespace wgame;

class Character : public AnimatedModelGLTF {
public:
    Character(const String & modelPath, bool isCullable = true);
    bool isCullable() const;
private:
    bool _isCullable;
};

#endif
