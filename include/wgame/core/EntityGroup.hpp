/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __ENTITY_GROUP_H__
#define __ENTITY_GROUP_H__

#include <wgame/core/Entity.hpp>

#include <unordered_set>


namespace wgame {

class EntityGroup : public Entity {
public:
    ~EntityGroup();
    void add(Entity * entity);
    void remove(Entity * entity);
    void update() override;
private:
    std::unordered_set<Entity *> _entities;
};

};


#endif