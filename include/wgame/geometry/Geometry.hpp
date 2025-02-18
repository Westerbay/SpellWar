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
#include <glm/gtc/type_ptr.hpp>

#define AXIS_X Vector3D(1.0f, 0.0f, 0.0f)
#define AXIS_Y Vector3D(0.0f, 1.0f, 0.0f)
#define AXIS_Z Vector3D(0.0f, 0.0f, 1.0f)

#define AXIS_XY Vector3D(1.0f, 1.0f, 0.0f)
#define AXIS_XZ Vector3D(1.0f, 0.0f, 1.0f)
#define AXIS_YZ Vector3D(0.0f, 1.0f, 1.0f)

#define AXIS_XYZ Vector3D(1.0f, 1.0f, 1.0f)

#define EPSILON 1e-6f

#define PRINT_VEC3(v) std::cout << #v << ": (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;


namespace wgame {

typedef glm::vec2 Point2D;
typedef glm::vec3 Point3D;
typedef glm::vec4 Point4D;
typedef glm::vec2 Vector2D;
typedef glm::vec3 Vector3D;
typedef glm::vec4 Vector4D;
typedef glm::mat2 Matrix2D;
typedef glm::mat3 Matrix3D;
typedef glm::mat4 Matrix4D;
typedef glm::vec3 ColorRGB;
typedef glm::quat Quaternion;

typedef struct {
	unsigned width;
	unsigned height;
} Size;

}

#endif
