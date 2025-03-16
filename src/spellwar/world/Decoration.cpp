/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Decoration.hpp>


Decoration::Decoration(const std::string & filepath) : StaticModelGLTF(filepath) {}

Matrix4D Decoration::getTransform() const {
	return Matrix4D(1.0f);
}

Vector3D Decoration::getCollideSize() const {
	return Vector3D(0.0f);
}

/* Stalagmite */
Stalagmite::Stalagmite() : Decoration(STALAGMITE_MODEL) {}

DecorationInfo Stalagmite::getDecorationInfo() const {
	DecorationInfo info;
	info.id = 0;
	info.size = Vector3D(2.0f, 4.2f, 2.0f);
	info.minScale = 0.8f;
	info.maxScale = 1.5f;
	info.minInstances = 1;   // Not Used
	info.maxInstances = 1;   // Not Used
	info.probability = 1.0f; // Not Used
	return info;
}

Vector3D Stalagmite::getCollideSize() const {
	return getDecorationInfo().size;
}


/* Pink Tree */
PinkTree::PinkTree() : Decoration(TREE_MODEL) {}

DecorationInfo PinkTree::getDecorationInfo() const {
	DecorationInfo info;
	info.id = 1;
	info.size = Vector3D(4.0f, 19.0f, 4.0f);
	info.minScale = 0.5f;
	info.maxScale = 1.0f;
	info.minInstances = 1;
	info.maxInstances = 2;
	info.probability = 0.7f;
	return info;
}

Vector3D PinkTree::getCollideSize() const {
	return Vector3D(1.0f, 19.0f, 1.0f);
}


/* FantasyPlant */
FantasyPlant::FantasyPlant() : Decoration(FANTASY_PLANT_MODEL) {}

DecorationInfo FantasyPlant::getDecorationInfo() const {
	DecorationInfo info;
	info.id = 2;
	info.size = Vector3D(1.0f, 1.0f, 1.0f);
	info.minScale = 1.5f;
	info.maxScale = 4.0f;
	info.minInstances = 1;
	info.maxInstances = 2;
	info.probability = 0.8f;
	return info;
}

Matrix4D FantasyPlant::getTransform() const {
	return glm::translate(Matrix4D(1.0f), Vector3D(0.0f, 0.48f, 0.0f));
}

/* Fern */
Rock::Rock() : Decoration(ROCK_MODEL) {}

DecorationInfo Rock::getDecorationInfo() const {
	DecorationInfo info;
	info.id = 3;
	info.size = Vector3D(9.0f, 7.0f, 8.0f);
	info.minScale = 0.5f;
	info.maxScale = 1.2f;
	info.minInstances = 1;
	info.maxInstances = 2;
	info.probability = 0.8f;
	return info;
}

Vector3D Rock::getCollideSize() const {
	return getDecorationInfo().size;
}

/* WaterPlant */
WaterPlant::WaterPlant() : Decoration(WATER_PLANT_MODEL) {}

DecorationInfo WaterPlant::getDecorationInfo() const {
	DecorationInfo info;
	info.id = 4;
	info.size = Vector3D(0.5f, 0.3f, 0.5f);
	info.minScale = 4.0f;
	info.maxScale = 8.0f;
	info.minInstances = 1;
	info.maxInstances = 2;
	info.probability = 0.5f;
	return info;
}

