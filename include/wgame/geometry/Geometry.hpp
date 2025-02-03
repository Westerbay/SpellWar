/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace wgame::geometry {

typedef glm::vec2 Point2D;
typedef glm::vec3 Point3D;
typedef glm::vec4 Point4D;
typedef glm::vec2 Vector2D;
typedef glm::vec3 Vector3D;
typedef glm::vec4 Vector4D;
typedef glm::mat2 Matrix2D;
typedef glm::mat3 Matrix3D;
typedef glm::mat4 Matrix4D;

typedef struct {
	unsigned width;
	unsigned height;
} Size;

}

#endif
