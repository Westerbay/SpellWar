/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/map/Platform.hpp>

Platform::Platform(const Hitbox & hitbox, GameObject * camera) : GameObject(hitbox) {
    _camera = camera;
    _playerSpawn = hitbox;
    _playerSpawn.move(hitbox.size.y * 0.5f, AXIS_Y);
    _playerSpawn.size = SPAWN_SIZE;
    _decorationHitboxes.push_back(_playerSpawn);
    _maxHeightStalagmite = 0; 
}

Hitbox Platform::getPlayerSpawn() const {
    return _playerSpawn;
}

void Platform::generateStalagmite(
    CollisionTree & collision,
    Decoration & decoration
) {	
	DecorationInfo info = decoration.getDecorationInfo();	
    std::vector<Hitbox> stalagmiteHitbox;
    std::vector<Matrix4D> transforms;
    Hitbox hitboxDecoration;
    
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
        float rotation = randomFloat(0.0f, 360.0f);
        transform = glm::rotate(transform, glm::radians(180.0f), AXIS_X);
        transform = glm::rotate(transform, glm::radians(rotation), AXIS_Y);
        transform = glm::scale(transform, Vector3D(scale, scale, scale));                    
        transform *= decoration.getTransform();

		hitboxDecoration.size = info.size * scale;
		hitboxDecoration.orientation = hitbox.orientation;	
		hitboxDecoration.position = hitbox.position;
		hitboxDecoration.position += hitbox.orientation[1] * hitboxDecoration.size.y * -0.5f;
		hitboxDecoration.move(translate);	

        _maxHeightStalagmite = glm::max(_maxHeightStalagmite, hitboxDecoration.size.y);
        if (!hitboxDecoration.collidesList(stalagmiteHitbox)) {
            nb ++;
            tries = 0;
            stalagmiteHitbox.push_back(hitboxDecoration);
            collision.insert(hitboxDecoration);
            _decorationHitboxes.push_back(hitboxDecoration);
            transforms.push_back(transform); 
        }                
    }
    _modelDrawer.configureInstances(transforms, info.id);
}

void Platform::generateDecoration(
    CollisionTree & collision,
    std::vector<Matrix4D> & transforms, 
    Decoration & decoration
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
			Vector3D translate = {
				(hitbox.size.x * 0.5f - scale * info.size.x) * randomFloat(-1.0f, 1.0f),
				hitbox.size.y * 0.5f,
				(hitbox.size.z * 0.5f - scale * info.size.z) * randomFloat(-1.0f, 1.0f),
			};            
			transform = glm::translate(transform, translate);
			transform = glm::scale(transform, Vector3D(scale, scale, scale)); 
            transform *= decoration.getTransform();
			
			hitboxDecoration.size = info.size * scale;
			hitboxDecoration.orientation = hitbox.orientation;	
			hitboxDecoration.position = hitbox.position;
			hitboxDecoration.position += hitbox.orientation[1] * hitboxDecoration.size.y * 0.5f;
		    hitboxDecoration.move(translate);
            hitboxDecoration.rotateY(decoration.getRotaHitboxY());
            hitboxDecoration.move(decoration.getMoveHitbox() * scale);
			
		} while (numberOfTries < MAX_ATTEMPTS_DECORATION && hitboxDecoration.collidesList(_decorationHitboxes));
		if (numberOfTries < MAX_ATTEMPTS_DECORATION) {
			transforms.push_back(transform);
			_decorationHitboxes.push_back(hitboxDecoration);
            if (decoration.getCollideSize() != Vector3D(0.0f)) {
                hitboxDecoration.size /= info.size;
                hitboxDecoration.size *= decoration.getCollideSize();
                collision.insert(hitboxDecoration);
            }
		}
	} 
}

std::vector<Hitbox> & Platform::getDecorationHitboxes() {
	return _decorationHitboxes;
}

Hitbox Platform::getExtendedHitbox() const {
    Hitbox extendedHitbox = hitbox;
    extendedHitbox.size.y += _maxHeightStalagmite;
    extendedHitbox.move(-_maxHeightStalagmite * 0.5f, AXIS_Y);
    return extendedHitbox;
}

bool Platform::onPlatform(const Hitbox & object) const {
    Hitbox entityHitbox = object;
    float delta = (entityHitbox.size.y + hitbox.size.y) * 0.5f;
    entityHitbox.move(-delta, AXIS_Y);
    return hitbox.contains(entityHitbox.position);
}

void Platform::renderStalagmite(ModelGLTF & model, int id) {
    if (shouldRenderStalagmite()) {
        _modelDrawer.drawInstanced(model, id);
    }    
}

bool Platform::shouldRenderStalagmite() {
    Hitbox camera = _camera -> getHitbox();
    Vector3D & gaze = camera.orientation[2];
    Point3D & cameraPos = camera.position;
    Vector3D toPlatform = glm::normalize(hitbox.position - cameraPos);
    return  glm::dot(gaze, toPlatform) > 0.0f;
}
