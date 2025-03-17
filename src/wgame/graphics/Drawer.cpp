/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/graphics/Drawer.hpp>


namespace wgame {

void Drawer::setActiveLight(bool activeLight) {
    this->activeLight = activeLight;
}

void Drawer::configureInstances(const std::vector<Matrix4D> & transforms, int id) {
    if (instances.find(id) == instances.end()) {
        instances[id] = std::make_unique<ShaderStorageBufferObject>();
    }
    instances[id] -> configure(transforms.size() * sizeof(Matrix4D));
    instances[id] -> setData(transforms.data(), transforms.size() * sizeof(Matrix4D));
    numberOfInstances[id] = transforms.size();
}

}
