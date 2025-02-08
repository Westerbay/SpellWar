/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __ENTITY_H__
#define __ENTITY_H__


namespace wgame {

class Entity {
public:
    virtual void update() = 0;
    virtual ~Entity() = default;
};

};


#endif