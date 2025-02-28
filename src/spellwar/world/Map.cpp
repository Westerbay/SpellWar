/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Map.hpp>


Map::Map(const Hitbox & hitbox) : GameObject() {
    _hitbox = hitbox;
    _model = new StaticModelGLTF("assets/model/stalagmite/scene.gltf");
}

Map::~Map() {
    delete _model;
}

void Map::generatePlatform(
    size_t maxNumberOfPlatforms,
    const Vector3D & minSize,
    const Vector3D & maxSize,
    unsigned maxAttempts
) {
    Point3D position = _hitbox.position;
    Vector3D size = _hitbox.size;

    unsigned tries = 0;
    _drawers.resize(maxNumberOfPlatforms);
    for (size_t i = 0; i < maxNumberOfPlatforms; i ++) {
        if (tries >= maxAttempts) {
            break;
        }
        while (tries < maxAttempts) {            
            Cuboid platform; 
            Hitbox hitbox; 

            tries ++;          
            for (int i = 0; i < 3; i ++) {
                platform.position[i] = randomFloat(
                    position[i] - size[i] / 2,
                    position[i] + size[i] / 2
                );
                platform.size[i] = randomFloat(
                    minSize[i], maxSize[i]
                );
            }  

            if (P(PROBABILITY_ROTATE)) {
                platform.rotateX(randomFloat(0.0f, MAX_ANGLE_ROTATION));
                platform.rotateY(randomFloat(0.0f, MAX_ANGLE_ROTATION));
                platform.rotateZ(randomFloat(0.0f, MAX_ANGLE_ROTATION));
            }            
            hitbox = platform;            
            hitbox.size.x += X_Z_GAP;
            hitbox.size.y += Y_GAP;
            hitbox.size.z += X_Z_GAP;
            if (!hitbox.collidesList(_platforms)) {
                _platforms.push_back(platform);                            
                _drawers[i].setFillCuboidData(platform, ColorRGB(0.0f, 0.0f, 1.0f));
                tries = 0;
                break;
            }         
        }
    }
    generateStalagmite();
}

void Map::render() {
    for (ColorDrawer & drawer: _drawers) {
        drawer.fill();
    }   
    glFrontFace(GL_CW); 
    _modelDrawer.draw(*_model);
    glFrontFace(GL_CCW); 
}

void Map::generateStalagmite() {
    const Cuboid & platform = _platforms.front();
    Matrix4D transform = platform.getTransformWithoutScale();
    
    transform = glm::translate(transform, platform.orientation[1] * platform.size.y * -0.5f);
    transform = glm::rotate(transform, glm::radians(180.0f), AXIS_X);
    transform = glm::scale(transform, Vector3D(3.0f, 3.0f, 3.0f));

    _model -> setTransform(transform);
}
