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
	return info;
}



