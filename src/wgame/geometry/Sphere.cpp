/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/geometry/Sphere.hpp>

namespace wgame {

Sphere::Sphere(Point3D position, float radius) {
    Sphere::position = position;
    Sphere::radius = radius;
}

void Sphere::generateSphere(
    std::vector<unsigned> & elements, 
    std::vector<Vector3D> & normals, 
    std::vector<Vector3D> & vertices, 
    unsigned int stacks, unsigned int slices
) const {

    for (unsigned int i = 0; i <= stacks; ++i) {
        float phi = PI * float(i) / float(stacks);
        float y = radius * cos(phi);
        float r = radius * sin(phi);

        for (unsigned int j = 0; j <= slices; ++j) {
            float theta = 2.0f * PI * float(j) / float(slices);
            float x = r * cos(theta);
            float z = r * sin(theta);
            
            Vector3D vertex = {x, y, z};
            vertex += position;
            Vector3D normal = {x / radius, y / radius, z / radius};
            
            vertices.push_back(vertex);
            normals.push_back(normal);
        }
    }

    for (unsigned int i = 0; i < stacks; ++i) {
        for (unsigned int j = 0; j < slices; ++j) {
            unsigned int first = i * (slices + 1) + j;
            unsigned int second = first + slices + 1;
            
            elements.push_back(first);
            elements.push_back(second);
            elements.push_back(first + 1);

            elements.push_back(second);
            elements.push_back(second + 1);
            elements.push_back(first + 1);
        }
    }
}

}
