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

#include "../tools/System.hpp"
#include "../geometry/Geometry.hpp"
#include "../opengl/Shader.hpp"
#include "../opengl/UniformBufferObject.hpp"
#include "GameObjectGroup.hpp"
#include "GameCamera.hpp"
#include "GameLight.hpp"

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
	GLFWwindow * getFrameWindow();
	bool shouldExit() const;
	void pollEvents() const;
	void swapBuffers() const;
	void setCursorActive(bool cursorActive);
	void setBackgroundColor(ColorRGB color);
	void initWorld(GameObjectGroup * world);
	void initCamera(GameCamera * camera);
	void initLight(GameLight * light);
	void initOpenGLState();
	void render();	
	void processEvents();
	virtual void processEvent(Event event) = 0;
private:
	static void frameResize(GLFWwindow * window, int width, int height);
	static Size _frameSize;
private:
	GLFWwindow * _frame;
	GameCamera * _camera;	
	GameObjectGroup * _world;
	GameLight * _light;
	bool _running;
	bool _cursorActive;
	System _system;
};

}

#endif

