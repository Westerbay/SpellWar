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
#define RED_TREE_MODEL "assets/model/decoration/redTree/scene.gltf"
#define FANTASY_PLANT_MODEL "assets/model/decoration/fantasyPlant/scene.gltf"
#define ROCK_MODEL "assets/model/decoration/rock/scene.gltf"
#define WATER_PLANT_MODEL "assets/model/decoration/waterPlant/scene.gltf"

#define MAX_ATTEMPTS_DECORATION 5


using namespace wgame;

struct DecorationInfo {
	int id;
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
	virtual Matrix4D getTransform() const;
	virtual float getRotaHitboxY() const;
	virtual Vector3D getCollideSize() const;
	virtual Vector3D getMoveHitbox() const;
};

class Stalagmite : public Decoration {
public:
    Stalagmite();
    DecorationInfo getDecorationInfo() const override;
	Vector3D getCollideSize() const override;
	Matrix4D getTransform() const override;
};

class RedTree : public Decoration {
public:
	RedTree();
    DecorationInfo getDecorationInfo() const override;
	Vector3D getCollideSize() const override;
};

class FantasyPlant : public Decoration {
public:
	FantasyPlant();
	DecorationInfo getDecorationInfo() const override;
	Matrix4D getTransform() const override;
};

class Rock : public Decoration {
public:
	Rock();
	DecorationInfo getDecorationInfo() const override;
	Vector3D getCollideSize() const override;
	float getRotaHitboxY() const override;
	Vector3D getMoveHitbox() const override;
};

class WaterPlant : public Decoration {
public:
WaterPlant();
	DecorationInfo getDecorationInfo() const override;
};

#endif


