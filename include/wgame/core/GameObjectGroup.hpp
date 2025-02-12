/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __GAME_OBJECT_GROUP_H__
#define __GAME_OBJECT_GROUP_H__

#include <wgame/core/GameObject.hpp>

#include <unordered_set>


namespace wgame {

class GameObjectGroup : public GameObject {
public:
    ~GameObjectGroup();
    void add(GameObject * gameObject);
    void remove(GameObject * gameObject);
    void update() override;
    void render() override;
private:
    std::unordered_set<GameObject *> _objects;
};

}


#endif
