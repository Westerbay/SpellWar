/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/opengl/ShaderStorageBufferObject.hpp>


namespace wgame {
  
ShaderStorageBufferObject::ShaderStorageBufferObject() 
: SharedBufferObject(GL_SHADER_STORAGE_BUFFER) {}
  
}
 