/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

 
#ifndef __ABSTRACT_FRAME_H__
#define __ABSTRACT_FRAME_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <wgame/geometry/Geometry.hpp>
#include <wgame/opengl/Shader.hpp>
#include "GameObjectGroup.hpp"
#include "GameCamera.hpp"
#include "../tools/Inputs.hpp"

#include <string>
#include <thread>
#include <chrono>


#define GL_VERSION_USED 4
#define DEFAULT_FPS 60


namespace wgame {

class AbstractFrame {
public:
	AbstractFrame(const char * title, const Size & size, unsigned fps = DEFAULT_FPS);
	virtual ~AbstractFrame();
	void setFPS(unsigned fps);
	void setCursorActive(bool cursorActive);
	void setBackgroundColor(GLclampf red, GLclampf green, GLclampf blue);
	void initWorld(GameObjectGroup & world);
	void initCamera(GameCamera & camera);
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
	unsigned _frameDelay;
	bool _running;
	bool _cursorActive;
};

}

#endif

