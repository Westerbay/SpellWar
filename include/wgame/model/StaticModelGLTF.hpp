/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_STATIC_MODEL_H__
#define __WG_STATIC_MODEL_H__

#include "ModelGLTF.hpp"


namespace wgame {

class StaticModelGLTF : public ModelGLTF {
public:
    StaticModelGLTF(const std::string & filename);
    void draw(const Shader & shader) override;
    void drawInstanced(const Shader & shader, size_t numberOfInstance) override;
};

}

#endif
