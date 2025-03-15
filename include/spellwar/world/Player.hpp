/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <wgame/wgame.hpp>
#include "PlayerCamera.hpp"
#include "Map.hpp"

#include <limits>

#define FROST_MODEL "assets/model/player/frost.glb"

#define SPEED 0.08f
#define RUNNING_FACTOR 2.0f
#define ANIMATION_ACCELERATION 1.5f
#define MAX_JUMP_DISTANCE 100.0f

using namespace wgame;

class Player : public GameObject {
public:
    enum State {
        RUNNING,
        WALKING,
        BACK,
        IDLE,
        STRAFE
    };
    enum Direction {
        LEFT,
        RIGHT,
        NONE
    };
public:
    Player(Map * map);    
    GameObject * getCameraObject();
    void state();
    void move();
    void animate();
    void swapPlatform(Platform * platform, const Point3D & destination);
    bool onPlatform() const;
    Platform * findBestAlignedPlatform(Point3D & destination);
    void update() override;
    void render() override;    
public:
    class FrostModel : public AnimatedModelGLTF {
    public:
        FrostModel();
    };
private:
    Vector3D getMovement() const;
    bool intersectionPlatform(
        const Point3D & gazePosition, 
        const Vector3D & gazeVector,  
        const Hitbox & hitbox, 
        const Vector3D & normal,
        Point3D & intersection
    );
private: 

    Map * _map;
    Platform * _currentPlatform;

    float _speed;
    float _runningFactor;
    float _sensibility;
    System _system;
    PlayerCamera _camera;
    FrostModel _model;
    ModelDrawer _modelDrawer;
    ColorDrawer _hitboxDrawer;

    State _state;
    Direction _direction;
    bool _jumping;
};


#endif
