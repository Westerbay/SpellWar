/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/map/Map.hpp>


Map::Map(const Hitbox & hitbox, AbstractBiome * biome) : GameObject(hitbox) {    
    _biome = biome;
    Hitbox collisionHitbox = hitbox;
    collisionHitbox.size *= RESIZE_FACTOR;
    _collision = std::make_shared<CollisionTree>(collisionHitbox);
}

Hitbox * Map::collide(const Hitbox & hitbox) {
    return _collision -> collidesWith(hitbox);
}

void Map::generatePlatform(
    GameObject * camera,
    size_t maxNumberOfPlatforms,
    const Vector3D & minSize,
    const Vector3D & maxSize,
    unsigned maxAttempts
) {    
    std::vector<Hitbox> _platformHitboxes;
    std::map<int, std::vector<Matrix4D>> decorationTransforms;
    std::vector<Decoration *> & decorations = _biome -> getDecorations();    

    for (size_t i = 0; i < decorations.size(); i ++) {
        DecorationInfo info = decorations[i] -> getDecorationInfo();
        decorationTransforms[info.id] = std::vector<Matrix4D>();
    }    
    
    unsigned tries = 0;    
    while (tries < maxAttempts && _platforms.size() < maxNumberOfPlatforms) {    
        Cuboid platform; 
        Hitbox hitboxPlatform;  
        tries ++;                     
        
        constructPlatform(platform, hitboxPlatform, minSize, maxSize);
        if (!hitboxPlatform.collidesList(_platformHitboxes)) {
            _platforms.push_back(Platform(platform, camera));
            _platformHitboxes.push_back(platform); 
            _platforms.back().generateStalagmite(*_collision, _biome -> getStalagmite());
            for (size_t i = 0; i < decorations.size(); i ++) {
            	DecorationInfo info = decorations[i] -> getDecorationInfo();
            	_platforms.back().generateDecoration(*_collision, decorationTransforms[info.id], *decorations[i]);
            }
            tries = 0;
        }         
    }  
    _mapView.initViews(this, decorationTransforms);             
}

void Map::constructPlatform(
    Cuboid & platform, Hitbox & hitboxPlatform,
    const Vector3D & minSize, const Vector3D & maxSize
) {
    Point3D position = hitbox.position;
    Vector3D size = hitbox.size;
    for (int i = 0; i < 3; i ++) {
        platform.position[i] = randomFloat(
            position[i] - size[i] / 2,
            position[i] + size[i] / 2
        );
        platform.size[i] = (float) randomInt(
            (int)minSize[i], (int)maxSize[i]
        );
    } 
    if (P(PROBABILITY_ROTATE) || platform.position.y > hitbox.position.y + HEIGHT_ROTATE_RATIO * hitbox.size.y) {
        Vector3D platformToCenter = glm::normalize(hitbox.position - platform.position);
        float cosTheta = glm::dot(glm::normalize(platform.orientation[1]), platformToCenter);
        float theta = glm::acos(glm::clamp(cosTheta, -1.0f, 1.0f));
        Vector3D rotationAxis = glm::cross(platform.orientation[1], platformToCenter);
        if (glm::length(rotationAxis) > 0.0001f) {
            rotationAxis = glm::normalize(rotationAxis);
            Matrix4D rotation = glm::rotate(Matrix4D(1.0f), theta, rotationAxis);
            platform.orientation = Matrix3D(rotation) * platform.orientation;
        }
    }                 
    hitboxPlatform = platform;            
    hitboxPlatform.size.x += X_Z_GAP;
    hitboxPlatform.size.y += Y_GAP;
    hitboxPlatform.size.z += X_Z_GAP;
}

void Map::render() {
    _mapView.render(this);
}

std::vector<Platform> & Map::getPlatforms() {
    return _platforms;
}
