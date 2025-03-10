/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Map.hpp>


Map::Map(const Hitbox & hitbox) : GameObject(hitbox) {
    Image image("assets/moon.bmp");
    _diffuse.setType(TEXTURE_2D);
    _diffuse.setInterpolationMode(GL_LINEAR);
    _diffuse.setRepeatMode(GL_REPEAT);
    _diffuse.setData(image);
    
    _decorations.push_back(std::make_unique<PinkTree>());
    _decorations.push_back(std::make_unique<FantasyPlant>());
    _decorations.push_back(std::make_unique<Rock>());
    _decorations.push_back(std::make_unique<WaterPlant>());
}

void Map::generatePlatform(
    size_t maxNumberOfPlatforms,
    const Vector3D & minSize,
    const Vector3D & maxSize,
    unsigned maxAttempts
) {
    
    std::vector<Hitbox> _platformHitboxes;
    std::vector<Matrix4D> stalagmiteTransform;
    std::map<int, std::vector<Matrix4D>> decorationTransforms;

    for (size_t i = 0; i < _decorations.size(); i ++) {
        DecorationInfo info = _decorations[i] -> getDecorationInfo();
        decorationTransforms[info.id] = std::vector<Matrix4D>();
    }    
    
    unsigned tries = 0;    
    while (tries < maxAttempts && _platforms.size() < maxNumberOfPlatforms) {    
        Cuboid platform; 
        Hitbox hitboxPlatform;  
        tries ++;                     
        
        constructPlatform(platform, hitboxPlatform, minSize, maxSize);
        if (!hitboxPlatform.collidesList(_platformHitboxes)) {
            _platforms.push_back(platform);
            _platformHitboxes.push_back(platform); 
            _platforms.back().generateStalagmite(stalagmiteTransform, _stalagmite);
            
            for (size_t i = 0; i < _decorations.size(); i ++) {
            	DecorationInfo info = _decorations[i] -> getDecorationInfo();
            	_platforms.back().generateDecoration(decorationTransforms[info.id], *_decorations[i]);
            }
            tries = 0;
        }         
    }               
	
	for (const auto & pair : decorationTransforms) {
		_modelDrawer.configureInstances(pair.second, pair.first);
	}
    _modelDrawer.configureInstances(
        stalagmiteTransform, 
        _stalagmite.getDecorationInfo().id
    );
    setUpPlatformTextures();
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
    if (P(PROBABILITY_ROTATE)) {
        platform.rotateX(randomFloat(0.0f, MAX_ANGLE_ROTATION));
        platform.rotateY(randomFloat(0.0f, MAX_ANGLE_ROTATION));
        platform.rotateZ(randomFloat(0.0f, MAX_ANGLE_ROTATION));
    }                 
    hitboxPlatform = platform;            
    hitboxPlatform.size.x += X_Z_GAP;
    hitboxPlatform.size.y += Y_GAP;
    hitboxPlatform.size.z += X_Z_GAP;
}

void Map::setUpPlatformTextures() {
    _platformDrawers.resize(_platforms.size());
    for (size_t i = 0; i < _platforms.size(); i ++) {
        const Cuboid & platform = _platforms[i].getHitbox();
        _platformDrawers[i].setCuboidData(platform, {
            {{0.0f, 0.0f}, {platform.size.x / TEX_SCALE, 0.0f}, {platform.size.x / TEX_SCALE, platform.size.y / TEX_SCALE}, {0.0f, platform.size.y / TEX_SCALE}},
            {{0.0f, 0.0f}, {platform.size.x / TEX_SCALE, 0.0f}, {platform.size.x / TEX_SCALE, platform.size.y / TEX_SCALE}, {0.0f, platform.size.y / TEX_SCALE}},
            {{0.0f, 0.0f}, {platform.size.x / TEX_SCALE, 0.0f}, {platform.size.x / TEX_SCALE, platform.size.z / TEX_SCALE}, {0.0f, platform.size.z / TEX_SCALE}},
            {{0.0f, 0.0f}, {platform.size.x / TEX_SCALE, 0.0f}, {platform.size.x / TEX_SCALE, platform.size.z / TEX_SCALE}, {0.0f, platform.size.z / TEX_SCALE}},
            {{0.0f, 0.0f}, {platform.size.z / TEX_SCALE, 0.0f}, {platform.size.z / TEX_SCALE, platform.size.y / TEX_SCALE}, {0.0f, platform.size.y / TEX_SCALE}},
            {{0.0f, 0.0f}, {platform.size.z / TEX_SCALE, 0.0f}, {platform.size.z / TEX_SCALE, platform.size.y / TEX_SCALE}, {0.0f, platform.size.y / TEX_SCALE}}
        });
    } 
}

void Map::render() {
    for (TextureDrawer & drawer: _platformDrawers) {
        drawer.draw({
            &_diffuse,
            &_diffuse,
            &_diffuse,
            &_diffuse,
            &_diffuse,
            &_diffuse
        });
    }  
    
    // Draw hitboxes
    /*for (Platform & platform : _platforms) {
    	for (Hitbox & hitboxDecoration : platform.getDecorationHitboxes()) {
    		_hitboxDrawer.setDrawCuboidData(hitboxDecoration, ColorRGB(1.0f, 0.0f, 0.0f));
    		_hitboxDrawer.draw();
		}
    }*/
		
    cullClockwise();    
    for (size_t i = 0; i < _decorations.size(); i ++) {
    	DecorationInfo info = _decorations[i] -> getDecorationInfo();
    	_modelDrawer.drawInstanced(*_decorations[i], info.id);
    }
    _modelDrawer.drawInstanced(_stalagmite, _stalagmite.getDecorationInfo().id);
    cullCounterClockwise();        
}

