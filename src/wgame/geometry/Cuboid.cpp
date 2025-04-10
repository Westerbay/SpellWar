/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/geometry/Cuboid.hpp>


namespace wgame {

Cuboid::Cuboid(
    const Point3D & position,
    const Vector3D & size,
    Matrix3D orientation
): position(position), size(size), orientation(orientation) {
    Cuboid::orientation[2] *= -1;
}

Matrix4D Cuboid::getTransform() const {
    Matrix4D scale = glm::scale(Matrix4D(1.0f), size);
    return getTransformWithoutScale() * scale;
}

Matrix4D Cuboid::getTransformWithoutScale() const {
    Matrix4D translate = glm::translate(Matrix4D(1.0f), position);
    Matrix4D rotate = Matrix4D(orientation);
    return translate * rotate;
}

std::vector<Point3D> Cuboid::getVertices() const {
    std::vector<Point3D> vertices;
    Vector3D halfSize = size * 0.5f;

    std::vector<Point3D> localVertices = {
        {-halfSize.x, -halfSize.y, halfSize.z}, // 0
        { halfSize.x, -halfSize.y, halfSize.z}, // 1
        { halfSize.x,  halfSize.y, halfSize.z}, // 2
        {-halfSize.x,  halfSize.y, halfSize.z}, // 3
        {-halfSize.x, -halfSize.y, -halfSize.z}, // 4
        { halfSize.x, -halfSize.y, -halfSize.z}, // 5
        { halfSize.x,  halfSize.y, -halfSize.z}, // 6
        {-halfSize.x,  halfSize.y, -halfSize.z}  // 7
    };

    std::vector<std::vector<int>> faceIndices = {
        {0, 1, 2, 3}, 
        {4, 5, 6, 7}, 
        {0, 1, 5, 4},          
        {3, 2, 6, 7}, 
        {1, 5, 6, 2},
        {0, 4, 7, 3}  
    };

    for (const std::vector<int> & face : faceIndices) {
        for (int index : face) {
            vertices.push_back(position + orientation * localVertices[index]);
        }
    }

    return vertices;
}

std::vector<std::vector<Point3D>> Cuboid::getVerticesPerFace() const {
    std::vector<std::vector<Point3D>> verticesPerFace;
    Vector3D halfSize = size * 0.5f;

    std::vector<Point3D> localVertices = {
        {-halfSize.x, -halfSize.y, halfSize.z}, // 0
        { halfSize.x, -halfSize.y, halfSize.z}, // 1
        { halfSize.x,  halfSize.y, halfSize.z}, // 2
        {-halfSize.x,  halfSize.y, halfSize.z}, // 3
        {-halfSize.x, -halfSize.y, -halfSize.z}, // 4
        { halfSize.x, -halfSize.y, -halfSize.z}, // 5
        { halfSize.x,  halfSize.y, -halfSize.z}, // 6
        {-halfSize.x,  halfSize.y, -halfSize.z}  // 7
    };

    std::vector<std::vector<int>> faceIndices = {
        {0, 1, 2, 3}, 
        {4, 5, 6, 7}, 
        {0, 1, 5, 4},        
        {3, 2, 6, 7},
        {1, 5, 6, 2},  
        {0, 4, 7, 3}  
    };

    for (const std::vector<int> & face : faceIndices) {
        std::vector<Point3D> vertices;
        for (int index : face) {
            vertices.push_back(position + orientation * localVertices[index]);
        }
        verticesPerFace.push_back(vertices);
    }

    return verticesPerFace;
}

std::vector<std::vector<Vector3D>> Cuboid::getNormalsPerFace() const {
    std::vector<std::vector<Vector3D>> normalsPerFace;

    Vector3D normalFront  = Vector3D(0, 0, 1);
    Vector3D normalBack   = Vector3D(0, 0, -1);    
    Vector3D normalBottom = Vector3D(0, -1, 0);
    Vector3D normalTop    = Vector3D(0, 1, 0);    
    Vector3D normalRight  = Vector3D(1, 0, 0);
    Vector3D normalLeft   = Vector3D(-1, 0, 0);

    std::vector<Vector3D> localNormals = {
        normalFront, normalBack, normalBottom,
        normalTop, normalRight, normalLeft
    };

    for (const Vector3D & localNormal : localNormals) {
        std::vector<Vector3D> normals;
        for (int i = 0; i < 4; i ++) {
            normals.push_back(orientation * localNormal);
        }    
        normalsPerFace.push_back(normals);    
    }
    
    return normalsPerFace;
}

std::vector<std::vector<Vector3D>> Cuboid::getTangentsPerFace() const {
    std::vector<std::vector<Vector3D>> tangentsPerFace;
    Vector3D halfSize = size * 0.5f;

    std::vector<Vector3D> localVertices = {
        {-halfSize.x, -halfSize.y, halfSize.z}, // 0
        { halfSize.x, -halfSize.y, halfSize.z}, // 1
        { halfSize.x,  halfSize.y, halfSize.z}, // 2
        {-halfSize.x,  halfSize.y, halfSize.z}, // 3
        {-halfSize.x, -halfSize.y, -halfSize.z}, // 4
        { halfSize.x, -halfSize.y, -halfSize.z}, // 5
        { halfSize.x,  halfSize.y, -halfSize.z}, // 6
        {-halfSize.x,  halfSize.y, -halfSize.z}  // 7
    };

    std::vector<std::vector<int>> faceIndices = {
        {0, 1, 2, 3}, 
        {4, 5, 6, 7}, 
        {0, 1, 5, 4},         
        {3, 2, 6, 7}, 
        {1, 5, 6, 2},
        {0, 4, 7, 3}  
    };

    for (const auto& indices : faceIndices) {
        std::vector<Vector3D> tangents;
        
        Vector3D tangent = glm::normalize(localVertices[indices[1]] - localVertices[indices[0]]);
        
        for (int i = 0; i < 4; i++) {
            tangents.push_back(glm::normalize(orientation * tangent));
        }
        
        tangentsPerFace.push_back(tangents);
    }

    return tangentsPerFace;
}

std::vector<std::vector<unsigned>> Cuboid::getElementsPerFace() const {
    return {
        {0, 2, 1, 0, 3, 2},
        {0, 1, 2, 0, 2, 3},
        {0, 1, 2, 0, 2, 3},
        {0, 2, 1, 0, 3, 2},
        {0, 2, 1, 0, 3, 2},
        {0, 1, 2, 0, 2, 3}
    };
}

bool Cuboid::contains(const Point3D & point) const {
    Point3D localPoint = glm::transpose(orientation) * (point - position);
    Point3D halfSize = size * 0.5f;

    return (fabs(localPoint.x) <= halfSize.x &&
            fabs(localPoint.y) <= halfSize.y &&
            fabs(localPoint.z) <= halfSize.z);
}

bool Cuboid::contains(const Point2D & point) const {
    return contains(Point3D(point, 0.0f));
}

bool Cuboid::collidesWith(const Cuboid & other) const {
    std::vector<Point3D> axes = {
        orientation[0], orientation[1], orientation[2],
        other.orientation[0], other.orientation[1], other.orientation[2]
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Point3D crossProduct = glm::cross(axes[i], axes[3 + j]);
            if (glm::length(crossProduct) > EPSILON) {
                axes.push_back(glm::normalize(crossProduct));
            }
        }
    }

    for (const Point3D & axis : axes) {
        if (isSeparated(other, axis)) {
            return false;
        }
    }
    return true;
}

bool Cuboid::collidesList(const std::vector<Cuboid> & cuboids) const {
    for (const Cuboid & cuboid: cuboids) {
        if (collidesWith(cuboid)) {
            return true;
        }
    }
    return false;
}

void Cuboid::translate(float delta, const Vector3D & axis) {
    position += delta * axis;
}

void Cuboid::move(const Vector3D & vector) {
	position += orientation * vector;
}

void Cuboid::move(float delta, const Vector3D & axis) {
    position += delta * orientation * axis;
}

void Cuboid::rotateX(float angle) {
    Matrix3D rotMatrix = Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(angle), orientation[0]));
    orientation = rotMatrix * orientation;
}

void Cuboid::rotateY(float angle) {
    Matrix3D rotMatrix = Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(angle), orientation[1]));
    orientation = rotMatrix * orientation;
}

void Cuboid::rotateZ(float angle) {
    Matrix3D rotMatrix = Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(angle), orientation[2]));
    orientation = rotMatrix * orientation;
}

bool Cuboid::isSeparated(const Cuboid & other, const Point3D & axis) const {
    float min1, max1, min2, max2;
    projectOntoAxis(axis, min1, max1);
    other.projectOntoAxis(axis, min2, max2);
    return max1 < min2 || max2 < min1;
}

void Cuboid::projectOntoAxis(const Point3D & axis, float & minProj, float & maxProj) const {
    std::vector<Point3D> vertices = getVertices();
    minProj = maxProj = glm::dot(vertices[0], axis);

    for (const Point3D & vertex : vertices) {
        float projection = glm::dot(vertex, axis);
        minProj = std::min(minProj, projection);
        maxProj = std::max(maxProj, projection);
    }
}

}

