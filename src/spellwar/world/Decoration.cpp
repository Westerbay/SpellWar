/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Decoration.hpp>


Decoration::Decoration(const std::string & filepath) : StaticModelGLTF(filepath) {}

/* Stalagmite */
Stalagmite::Stalagmite() : Decoration(STALAGMITE_MODEL) {}

DecorationInfo Stalagmite::getDecorationInfo() const {
	DecorationInfo info;
	info.id = 0;
	info.size = Vector3D(2.0f, 5.0f, 2.0f);
	info.minScale = 0.8f;
	info.maxScale = 1.5f;
	info.minInstances = 1;   // Not Used
	info.maxInstances = 1;   // Not Used
	info.probability = 1.0f; // Not Used
	return info;
}


/* Pink Tree */
PinkTree::PinkTree() : Decoration(TREE_MODEL) {}

DecorationInfo PinkTree::getDecorationInfo() const {
	DecorationInfo info;
	info.id = 1;
	info.size = Vector3D(1.0f, 19.0f, 1.0f);
	info.minScale = 0.5f;
	info.maxScale = 1.0f;
	info.minInstances = 1;
	info.maxInstances = 2;
	info.probability = 0.7f;
	return info;
}

/* Fern */
Fern::Fern() : Decoration(FERN_MODEL) {}

DecorationInfo Fern::getDecorationInfo() const {
	DecorationInfo info;
	info.id = 2;
	info.size = Vector3D(1.0f, 0.5f, 1.0f);
	info.minScale = 1.0;
	info.maxScale = 3.0f;
	info.minInstances = 1;
	info.maxInstances = 2;
	info.probability = 0.8f;
	return info;
}

/* Fern */
Rock::Rock() : Decoration(ROCK_MODEL) {}

DecorationInfo Rock::getDecorationInfo() const {
	DecorationInfo info;
	info.id = 3;
	info.size = Vector3D(20.0f, 10.0f, 20.0f);
	info.minScale = 0.05f;
	info.maxScale = 0.1f;
	info.minInstances = 1;
	info.maxInstances = 2;
	info.probability = 0.8f;
	return info;
}

/* RadianceTree */
RadianceTree::RadianceTree() : Decoration(RADIANCE_TREE_MODEL) {}

DecorationInfo RadianceTree::getDecorationInfo() const {
	DecorationInfo info;
	info.id = 4;
	info.size = Vector3D(1.0f, 5.0f, 1.0f);
	info.minScale = 1.5f;
	info.maxScale = 5.0f;
	info.minInstances = 1;
	info.maxInstances = 2;
	info.probability = 0.5f;
	return info;
}

