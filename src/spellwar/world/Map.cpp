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
    
    _decorations.push_back(&_pinkTree);
    _decorations.push_back(&_fern);
    _decorations.push_back(&_rock);
    _decorations.push_back(&_radianceTree);
}

void Map::generatePlatform(
    size_t maxNumberOfPlatforms,
    const Vector3D & minSize,
    const Vector3D & maxSize,
    unsigned maxAttempts
) {
    Point3D position = hitbox.position;
    Vector3D size = hitbox.size;
    std::vector<Hitbox> _platformHitboxes;
    std::vector<Matrix4D> stalagmiteTransform;
    std::map<int, std::vector<Matrix4D>> decorationTransforms;
    
    unsigned tries = 0;    
    while (tries < maxAttempts && _platforms.size() < maxNumberOfPlatforms) {   
        tries ++;         
        Cuboid platform; 
        Hitbox hitbox;                      
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
        hitbox = platform;            
        hitbox.size.x += X_Z_GAP;
        hitbox.size.y += Y_GAP;
        hitbox.size.z += X_Z_GAP;

        if (!hitbox.collidesList(_platformHitboxes)) {
            _platforms.push_back(platform);
            _platformHitboxes.push_back(platform); 
            _platforms.back().generateStalagmite(&stalagmiteTransform, _stalagmite);
            
            for (Decoration * decoration : _decorations) {
            	DecorationInfo info = decoration -> getDecorationInfo();
            	decorationTransforms[info.id] = std::vector<Matrix4D>();
            	_platforms.back().generateDecoration(&decorationTransforms[info.id], *decoration);
            }
            tries = 0;
        }         
    }

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
	
	for (const auto & pair : decorationTransforms) {
		_modelDrawer.configureInstances(pair.second, pair.first);
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
    
    for (Platform & platform : _platforms) {
    	for (Hitbox & hitboxDecoration : platform.getDecorationHitboxes()) {
    		_hitboxDrawer.setDrawCuboidData(hitboxDecoration, ColorRGB(1.0f, 0.0f, 0.0f));
    		_hitboxDrawer.draw();
		}
    } 
		
    cullClockwise();
    
    for (Decoration * decoration : _decorations) {
    	DecorationInfo info = decoration -> getDecorationInfo();
    	_modelDrawer.drawInstanced(*decoration, info.id);
    }
    _modelDrawer.drawInstanced(_stalagmite, _stalagmite.getDecorationInfo().id);
    cullCounterClockwise();        
}

