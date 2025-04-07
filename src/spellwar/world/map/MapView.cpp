/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/map/Map.hpp>


void MapView::initViews(
    Map * map,
    std::map<int, std::vector<Matrix4D>> & decorationTransforms
) {
    for (const auto & pair : decorationTransforms) {
		_modelDrawer.configureInstances(pair.second, pair.first);
	}
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
    std::vector<Decoration *> & decorations = map -> _biome -> getDecorations();    

    for (TextureDrawer & drawer: _platformDrawers) {
        drawer.draw({
            map -> _biome -> getDiffusePlatform(),
            map -> _biome -> getDiffusePlatform(),
            map -> _biome -> getDiffusePlatform(),
            map -> _biome -> getDiffusePlatform(),
            map -> _biome -> getDiffusePlatform(),
            map -> _biome -> getDiffusePlatform()
        }, {
            map -> _biome -> getNormalPlatform(),
            map -> _biome -> getNormalPlatform(),
            map -> _biome -> getNormalPlatform(),
            map -> _biome -> getNormalPlatform(),
            map -> _biome -> getNormalPlatform(),
            map -> _biome -> getNormalPlatform()
        }, {
            map -> _biome -> getHeightPlatform(),
            map -> _biome -> getHeightPlatform(),
            map -> _biome -> getHeightPlatform(),
            map -> _biome -> getHeightPlatform(),
            map -> _biome -> getHeightPlatform(),
            map -> _biome -> getHeightPlatform()
        });
    }  
		
    cullClockwise();    
    for (size_t i = 0; i < decorations.size(); i ++) {
    	DecorationInfo info = decorations[i] -> getDecorationInfo();
    	_modelDrawer.drawInstanced(*decorations[i], info.id);
    }
    for (Platform & platform : map -> _platforms) {
        Decoration & decoration = map -> _biome -> getStalagmite();
        platform.renderStalagmite(
            decoration, decoration.getDecorationInfo().id
        );
    }
    cullCounterClockwise();     
    
    // for (Platform & plat: map -> _platforms) {
    //     _hitboxDrawer.setDrawCuboidData(plat.getExtendedHitbox(), ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f));
    //     _hitboxDrawer.draw();
    //     for (Hitbox & hitb: plat.getDecorationHitboxes()) {
    //         _hitboxDrawer.setDrawCuboidData(hitb, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f));
    //         _hitboxDrawer.draw();
    //     }
    // }
}
