/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __SPACE_H__
#define __SPACE_H__

#define SPACE_PLATFORM_DIFFUSE "assets/materials/space/diffuse.bmp"
#define SPACE_PLATFORM_NORMAL "assets/materials/space/normal.bmp"
#define SPACE_PLATFORM_HEIGHT "assets/materials/space/height.bmp"

#define SPACE_SUN_ASSET "assets/model/sun/scene.gltf"
#define SPACE_SUN_SCALE 0.003f

#define SPACE_BACKGROUND_PX "assets/background/space/px.png"
#define SPACE_BACKGROUND_NX "assets/background/space/nx.png"
#define SPACE_BACKGROUND_PY "assets/background/space/py.png"
#define SPACE_BACKGROUND_NY "assets/background/space/ny.png"
#define SPACE_BACKGROUND_PZ "assets/background/space/pz.png"
#define SPACE_BACKGROUND_NZ "assets/background/space/nz.png"


#include <wgame/wgame.hpp>

#include "../map/AbstractBiome.hpp"
#include "../map/Decoration.hpp"
#include "../map/Light.hpp"
#include "../map/Background.hpp"


using namespace wgame;

class Space : public AbstractBiome {
public:
    Space(GameLight * gameLight);
    Decoration & getStalagmite() override;
    std::vector<Decoration *> & getDecorations() override;
    Texture2D * getDiffusePlatform() override;    
    Texture2D * getNormalPlatform() override;
    Texture2D * getHeightPlatform() override;
public:
    class Sun : public StaticModelGLTF {
    public:
        Sun();
    };
private:
    Stalagmite _stalagmite;
    RedTree _redTree;
    FantasyPlant _fantasyPlant;
    Rock _rock;
    WaterPlant _waterPlant;

    std::vector<Decoration *> _decorations;

    Texture2D _diffuse;
    Texture2D _normal;
    Texture2D _height;

    Sun _sun;
};

#endif