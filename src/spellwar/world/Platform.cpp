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
    const Decoration & decoration
) {
	
	DecorationInfo info = decoration.getDecorationInfo();
	
    std::vector<Cuboid> stalagmiteHitbox;
    unsigned limit = (unsigned)(hitbox.size.x * hitbox.size.z);
    unsigned tries = 0;
    unsigned nb = 0;
    while (nb < limit && tries < MAX_ATTEMPTS) {
        tries ++;
        Matrix4D transform = hitbox.getTransformWithoutScale();
        float scale = randomFloat(info.minScale, info.maxScale);
        Vector3D translate = {
            (hitbox.size.x * 0.5f - scale * info.size.x) * randomFloat(-1.0f, 1.0f),
            -hitbox.size.y * 0.5f,
            (hitbox.size.z * 0.5f - scale * info.size.z) * randomFloat(-1.0f, 1.0f),
        };
        transform = glm::translate(transform, translate);
        transform = glm::rotate(transform, glm::radians(180.0f), AXIS_X);
        transform = glm::scale(transform, Vector3D(scale, scale, scale));            

        Hitbox hitbox(Point3D(0.0f), info.size);
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
    const Decoration & decoration
) {
	DecorationInfo info = decoration.getDecorationInfo();
    if (!P(info.probability)) {
        return;
    }
    
    Matrix4D transform;
	Hitbox hitboxDecoration;
	unsigned numberOfTries;
    int numberOfInstances = randomInt(info.minInstances, info.maxInstances);
    for (int i = 0; i < numberOfInstances; i ++) {
		numberOfTries = 0;
		do {
			numberOfTries ++;
			transform = hitbox.getTransformWithoutScale();
			float scale = randomFloat(info.minScale, info.maxScale);
			float rotation = randomFloat(0.0f, 360.0f);
			Vector3D translate = {
				(hitbox.size.x * 0.5f - scale * info.size.x) * randomFloat(-1.0f, 1.0f),
				hitbox.size.y * 0.5f,
				(hitbox.size.z * 0.5f - scale * info.size.z) * randomFloat(-1.0f, 1.0f),
			};
			transform = glm::translate(transform, translate);
			transform = glm::rotate(transform, glm::radians(rotation), AXIS_Y);
			transform = glm::scale(transform, Vector3D(scale, scale, scale)); 
			
			hitboxDecoration.size = info.size * scale;
			hitboxDecoration.orientation = hitbox.orientation;	
			hitboxDecoration.position = hitbox.position;
			hitboxDecoration.position += hitbox.orientation[1] * hitboxDecoration.size.y * 0.5f;
		    hitboxDecoration.move(translate);					
			
		} while (numberOfTries < MAX_ATTEMPTS_DECORATION && hitboxDecoration.collidesList(_decorationHitboxes));
		if (numberOfTries < MAX_ATTEMPTS_DECORATION) {
			transforms.push_back(transform);
			_decorationHitboxes.push_back(hitboxDecoration);
		}
	} 
}

std::vector<Hitbox> & Platform::getDecorationHitboxes() {
	return _decorationHitboxes;
}


