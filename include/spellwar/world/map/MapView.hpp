/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __MAP_VIEW_H__
#define __MAP_VIEW_H__

#include <wgame/wgame.hpp>


#define TEX_SCALE 10.0f


using namespace wgame;

class Map;

class MapView {
public:
    void initViews(
        Map * map,
        std::vector<Matrix4D> & stalagmiteTransform,
        std::map<int, std::vector<Matrix4D>> & decorationTransforms
    );
    void setUpPlatformTextures(Map * map);
    void render(Map * map);
private:
    ModelDrawer _modelDrawer;
    ColorDrawer _hitboxDrawer; 
    std::vector<TextureDrawer> _platformDrawers;
};

#endif