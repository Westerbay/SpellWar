/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

 
#ifndef __WG_ABSTRACT_FRAME_H__
#define __WG_ABSTRACT_FRAME_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../tools/Inputs.hpp"
#include "../geometry/Geometry.hpp"
#include "../opengl/Shader.hpp"
#include "../opengl/UniformBufferObject.hpp"
#include "GameObjectGroup.hpp"
#include "GameCamera.hpp"

#include <string>
#include <thread>
#include <chrono>


#define GL_VERSION_USED 4

#define MATRIX_CAMERA_POINT 0 


namespace wgame {

class AbstractFrame {
public:
	AbstractFrame(const char * title, const Size & size);
	virtual ~AbstractFrame();
	void setCursorActive(bool cursorActive);
	void setBackgroundColor(GLclampf red, GLclampf green, GLclampf blue);
	void initWorld(GameObjectGroup * world);
	void initCamera(GameCamera * camera);
	void start();
	void stop();
	virtual void renderHUD() = 0;
private:
	void initOpenGLState();
	void render();
	GLFWwindow * _frame;
	GameObjectGroup * _world;
	GameCamera * _camera;
	Size _size;
	bool _running;
	bool _cursorActive;
};

}

#endif

