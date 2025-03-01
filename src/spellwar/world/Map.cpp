/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Map.hpp>


Map::Map(const Hitbox & hitbox) : GameObject(hitbox) {
    Image image("assets/textures/4/4_diffuseOriginal.bmp");
    _texture.setType(TEXTURE_2D);
    _texture.setInterpolationMode(GL_LINEAR);
    _texture.setRepeatMode(GL_REPEAT);
    _texture.setData(image);
    _texture.enableAnisotropicFiltering();

    Image imageHeight("assets/textures/4/4_height.bmp");
    _textureHeight.setType(TEXTURE_2D);
    _textureHeight.setInterpolationMode(GL_LINEAR);
    _textureHeight.setRepeatMode(GL_REPEAT);
    _textureHeight.setData(imageHeight);
    _textureHeight.enableAnisotropicFiltering();
}

void Map::generatePlatform(
    size_t maxNumberOfPlatforms,
    const Vector3D & minSize,
    const Vector3D & maxSize,
    unsigned maxAttempts
) {
    Point3D position = hitbox.position;
    Vector3D size = hitbox.size;

    unsigned tries = 0;
    _drawers.resize(maxNumberOfPlatforms);
    for (size_t i = 0; i < maxNumberOfPlatforms; i ++) {
        if (tries >= maxAttempts) {
            break;
        }
        while (tries < maxAttempts) {            
            Cuboid platform; 
            Hitbox hitbox; 

            tries ++;          
            for (int i = 0; i < 3; i ++) {
                platform.position[i] = randomFloat(
                    position[i] - size[i] / 2,
                    position[i] + size[i] / 2
                );
                platform.size[i] = randomFloat(
                    minSize[i], maxSize[i]
                );
            }  

            if (P(PROBABILITY_ROTATE)) {
                platform.rotateX(randomFloat(0.0f, MAX_ANGLE_ROTATION));
                platform.rotateY(randomFloat(0.0f, MAX_ANGLE_ROTATION));
                platform.rotateZ(randomFloat(0.0f, MAX_ANGLE_ROTATION));
            }            
            hitbox = platform;            
            hitbox.size.x += X_Z_GAP;
            hitbox.size.y += Y_GAP;
            hitbox.size.z += X_Z_GAP;
            if (!hitbox.collidesList(_platforms)) {
                _platforms.push_back(platform);   

                _drawers[i].setCuboidData(platform, {
                    {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}},
                    {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}},
                    {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}},
                    {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}},
                    {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}},
                    {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}}
                });

                tries = 0;
                break;
            }         
        }
    }
    generateStalagmite();
}

void Map::render() {
    for (TextureDrawer & drawer: _drawers) {
        drawer.draw({
            &_texture,
            &_texture,
            &_texture,
            &_texture,
            &_texture,
            &_texture
        });
    }   
    cullClockwise();
    _modelDrawer.drawInstanced(_stalagmite);
    cullCounterClockwise();
}

void Map::generateStalagmite() {

    std::vector<Matrix4D> stalagmiteTransform;
    Vector3D stalagmiteSize = _stalagmite.getSize();

    for (const Cuboid & platform: _platforms) {        
        std::vector<Cuboid> stalagmiteHitbox;
        unsigned limit = (unsigned)(platform.size.x * platform.size.z) / 100;
        unsigned tries = 0;
        unsigned nb = 0;
        while (nb < limit && tries < MAX_ATTEMPTS) {
            tries ++;
            Matrix4D transform = platform.getTransformWithoutScale();
            float scale = randomFloat(2.0f, 4.5f);
            Vector3D translate = {
                (platform.size.x * 0.5f - scale * stalagmiteSize.x) * randomFloat(-1.0f, 1.0f),
                -platform.size.y * 0.5f,
                (platform.size.z * 0.5f - scale * stalagmiteSize.z) * randomFloat(-1.0f, 1.0f),
            };
            transform = glm::translate(transform, translate);
            transform = glm::rotate(transform, glm::radians(180.0f), AXIS_X);
            transform = glm::scale(transform, Vector3D(scale, scale, scale));            

            Hitbox hitbox(Point3D(0.0f), stalagmiteSize);
            Vector3D offset(0.5f, 0.0f, 0.5f);
            offset *= scale;
            hitbox.orientation = platform.orientation;            
            hitbox.position += platform.position;
            hitbox.position += translate.x * platform.orientation[0];
            hitbox.position += translate.y * platform.orientation[1];
            hitbox.position += translate.z * platform.orientation[2]; 

            hitbox.position += offset.x * platform.orientation[0];
            hitbox.position += offset.y * platform.orientation[1];
            hitbox.position += offset.z * platform.orientation[2]; 
            hitbox.size *= scale;   

            if (!hitbox.collidesList(stalagmiteHitbox)) {
                nb ++;
                tries = 0;
                stalagmiteHitbox.push_back(hitbox);
                stalagmiteTransform.push_back(transform); 
            }
                    
        }        
    }    

    _modelDrawer.configureInstances(stalagmiteTransform);
}

Map::Stalagmite::Stalagmite() : StaticModelGLTF(STALAGMITE_MODEL) {}

Vector3D Map::Stalagmite::getSize() const {
    return Vector3D(1.8f, 5.0f, 1.8f);
}
