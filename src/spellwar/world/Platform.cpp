/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Platform.hpp>

Platform::Platform(const Hitbox & hitbox) : GameObject(hitbox) {}

void Platform::generateStalagmite(
    std::vector<Matrix4D> & transforms,
    const Vector3D & size
) {
    std::vector<Cuboid> stalagmiteHitbox;
    unsigned limit = (unsigned)(hitbox.size.x * hitbox.size.z);
    unsigned tries = 0;
    unsigned nb = 0;
    while (nb < limit && tries < MAX_ATTEMPTS) {
        tries ++;
        Matrix4D transform = hitbox.getTransformWithoutScale();
        float scale = randomFloat(STALAGMITE_MIN_SCALE, STALAGMITE_MAX_SCALE);
        Vector3D translate = {
            (hitbox.size.x * 0.5f - scale * size.x) * randomFloat(-1.0f, 1.0f),
            -hitbox.size.y * 0.5f,
            (hitbox.size.z * 0.5f - scale * size.z) * randomFloat(-1.0f, 1.0f),
        };
        transform = glm::translate(transform, translate);
        transform = glm::rotate(transform, glm::radians(180.0f), AXIS_X);
        transform = glm::scale(transform, Vector3D(scale, scale, scale));            

        Hitbox hitbox(Point3D(0.0f), size);
        Vector3D offset(0.5f, 0.0f, 0.5f);
        offset *= scale;
        hitbox.orientation = hitbox.orientation;            
        hitbox.position += hitbox.position;
        hitbox.position += translate.x * hitbox.orientation[0];
        hitbox.position += translate.y * hitbox.orientation[1];
        hitbox.position += translate.z * hitbox.orientation[2]; 

        hitbox.position += offset.x * hitbox.orientation[0];
        hitbox.position += offset.y * hitbox.orientation[1];
        hitbox.position += offset.z * hitbox.orientation[2]; 
        hitbox.size *= scale;   

        if (!hitbox.collidesList(stalagmiteHitbox)) {
            nb ++;
            tries = 0;
            stalagmiteHitbox.push_back(hitbox);
            transforms.push_back(transform); 
        }
                
    }
}

void Platform::generateDecoration(
    std::vector<Matrix4D> & transforms, 
    const Vector3D & size, float probability,
    float minScale, float maxScale
) {
    if (!P(probability)) {
        return;
    }
    Matrix4D transform = hitbox.getTransformWithoutScale();
    float scale = randomFloat(minScale, maxScale);
    Vector3D translate = {
        (hitbox.size.x * 0.5f - scale * size.x) * randomFloat(-1.0f, 1.0f),
        hitbox.size.y * 0.5f,
        (hitbox.size.z * 0.5f - scale * size.z) * randomFloat(-1.0f, 1.0f),
    };
    transform = glm::translate(transform, translate);
    transform = glm::scale(transform, Vector3D(scale, scale, scale));   
    transforms.push_back(transform); 
}

void Platform::endGenerate() {
    _decorationHitboxes.clear();
}
