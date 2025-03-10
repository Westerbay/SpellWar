/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __DECORATION__
#define __DECORATION__

#include <wgame/wgame.hpp>

#define STALAGMITE_MODEL "assets/model/decoration/stalagmite/scene.gltf"
#define TREE_MODEL "assets/model/decoration/pinkTree/scene.gltf"
#define FERN_MODEL "assets/model/decoration/fern/scene.gltf"

#define MAX_ATTEMPTS_DECORATION 5


using namespace wgame;

struct DecorationInfo {
	Vector3D size;
	float minScale;
	float maxScale;
	int minInstances;
	int maxInstances;
	float probability;
};

class Decoration : public StaticModelGLTF {
public:
	Decoration(const std::string & filepath);
	virtual DecorationInfo getDecorationInfo() const = 0;
};

class Stalagmite : public Decoration {
public:
    Stalagmite();
    DecorationInfo getDecorationInfo() const override;
};

class PinkTree : public Decoration {
public:
    PinkTree();
    DecorationInfo getDecorationInfo() const override;
};

class Fern : public Decoration {
public:
	Fern();
	DecorationInfo getDecorationInfo() const override;
};

#endif


