/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_SSBO_H__
#define __WG_SSBO_H__
  
#include "SharedBufferObject.hpp"
  
  
namespace wgame {
  
class ShaderStorageBufferObject : public SharedBufferObject {
public:
    ShaderStorageBufferObject();
};
  
}
  
#endif
  