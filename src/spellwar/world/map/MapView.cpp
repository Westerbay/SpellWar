/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/map/Map.hpp>


MapView::MapView() {
    Image image(PLATFORM_DIFFUSE);
    _diffuse.setType(TEXTURE_2D);
    _diffuse.setInterpolationMode(GL_LINEAR);
    _diffuse.setRepeatMode(GL_REPEAT);
    _diffuse.setData(image);    

    Image imageNormal(PLATFORM_NORMAL);
    _normal.setType(TEXTURE_2D);
    _normal.setInterpolationMode(GL_LINEAR);
    _normal.setRepeatMode(GL_REPEAT);
    _normal.setData(imageNormal);

    Image imageHeight(PLATFORM_HEIGHT);
    _height.setType(TEXTURE_2D);
    _height.setInterpolationMode(GL_LINEAR);
    _height.setRepeatMode(GL_REPEAT);
    _height.setData(imageHeight);
}

void MapView::initViews(
    Map * map,
    std::vector<Matrix4D> & stalagmiteTransform,
    std::map<int, std::vector<Matrix4D>> & decorationTransforms
) {
    for (const auto & pair : decorationTransforms) {
		_modelDrawer.configureInstances(pair.second, pair.first);
	}
    _modelDrawer.configureInstances(
        stalagmiteTransform, 
        map -> _stalagmite.getDecorationInfo().id
    );
    setUpPlatformTextures(map);
}

void MapView::setUpPlatformTextures(Map * map) {
    _platformDrawers.resize(map -> _platforms.size());
    for (size_t i = 0; i < map -> _platforms.size(); i ++) {
        const Cuboid & platform = map -> _platforms[i].getHitbox();
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

void MapView::render(Map * map) {
    for (TextureDrawer & drawer: _platformDrawers) {
        drawer.draw({
            &_diffuse,
            &_diffuse,
            &_diffuse,
            &_diffuse,
            &_diffuse,
            &_diffuse
        }, {
            &_normal,
            &_normal,
            &_normal,
            &_normal,
            &_normal,
            &_normal
        }, {
            &_height,
            &_height,
            &_height,
            &_height,
            &_height,
            &_height
        });
    }  
		
    cullClockwise();    
    for (size_t i = 0; i < map -> _decorations.size(); i ++) {
    	DecorationInfo info = map -> _decorations[i] -> getDecorationInfo();
    	_modelDrawer.drawInstanced(*map -> _decorations[i], info.id);
    }
    _modelDrawer.drawInstanced(map -> _stalagmite, map -> _stalagmite.getDecorationInfo().id);
    cullCounterClockwise();     
    
    // for (Platform & plat: map -> _platforms) {
    //     _hitboxDrawer.setDrawCuboidData(plat.getExtendedHitbox(), ColorRGB(1.0f, 0.0f , 0.0f));
    //     _hitboxDrawer.draw();
    //     for (Hitbox & hitb: plat.getDecorationHitboxes()) {
    //         _hitboxDrawer.setDrawCuboidData(hitb, ColorRGB(1.0f, 0.0f , 0.0f));
    //         _hitboxDrawer.draw();
    //     }
    // }
}
