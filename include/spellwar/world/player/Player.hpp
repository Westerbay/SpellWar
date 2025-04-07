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
#include "PlayerModel.hpp"
#include "PlayerHUD.hpp"
#include "PlayerMotion.hpp"
#include "PlayerInputs.hpp"
#include "../map/Map.hpp"

#include <limits>


#define MAX_JUMP_DISTANCE 70.0f
#define SWAP_ANIMATION_KEYFRAME 0.014f
#define MIN_SWAP_ANIMATION_KEYFRAME 0.1f

#define HITBOX_SIZE Vector3D(0.6f, 1.65f, 0.6f)


using namespace wgame;

struct PlatformAnimation {
    Hitbox destinationHitbox;
    Hitbox startHitbox;
    float angle;
    float keyFrame;
    bool isSwapping;
};

class Player : public GameObject {
public:
    friend class PlayerModel;
    friend class PlayerHUD;
    friend class PlayerMotion;
    friend class PlayerInputs;
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
    Player(Map * map, Character * model);   
    void spawn(); 
    GameObject * getCameraObject();    
    void setCharacter(Character * model);
    void setActive(bool active);
    void updateCamera();  
    void update() override;
    void render() override; 
    void renderHUD(const Size & screenSize) override;        
private:
    Platform * findBestAlignedPlatform(Point3D & destination);
    bool intersectionPlatform(
        const Point3D & gazePosition, 
        const Vector3D & gazeVector,  
        const Hitbox & hitbox, 
        const Vector3D & normal,
        Point3D & intersection
    );
    bool canSwap();  
private: 
    PlayerModel _playerModel;
    PlayerHUD _playerHUD;
    PlayerMotion _playerMotion;
    PlayerInputs _playerInputs;
    PlayerCamera _camera;

    Map * _map;
    Platform * _currentPlatform;

    Hitbox _collideHitbox;
    State _state;
    Direction _direction;
    PlatformAnimation _swapAnimation;

    bool _jumping;
    bool _leap;
    bool _trySwap;
    bool _active;
};


#endif
