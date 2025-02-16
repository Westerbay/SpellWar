/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/AbstractFrame.hpp>

#include <stdexcept>


namespace wgame {

AbstractFrame::AbstractFrame(const char * title, const Size & size) : _running(false) {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW ! ");
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_USED);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_USED);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	_frame = glfwCreateWindow(size.width, size.height, title, NULL, NULL);
	if (_frame == NULL) {
		throw std::runtime_error("Failed to create GLFW window ! ");
	}
	
	glfwMakeContextCurrent(_frame);
	gladLoadGL();
	
	glViewport(0, 0, size.width, size.height);

	_size = size;
	_world = nullptr;
	_camera = nullptr;
	Inputs::initContext(_frame);
}

AbstractFrame::~AbstractFrame() {
	glfwDestroyWindow(_frame);
	glfwTerminate();
}

void AbstractFrame::setCursorActive(bool cursorActive) {
	_cursorActive = cursorActive;
	if (_cursorActive) {
		glfwSetInputMode(_frame, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else {		
		glfwSetInputMode(_frame, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void AbstractFrame::setBackgroundColor(GLclampf red, GLclampf green, GLclampf blue) {
	glClearColor(red, green, blue, 1.0f);
}

void AbstractFrame::initWorld(GameObjectGroup & world) {
	if (_world != nullptr) {
		throw std::runtime_error("World already initialized ! ");
	}
	_world = &world;
}
void AbstractFrame::initCamera(GameCamera & camera) {
	if (_camera != nullptr) {
		throw std::runtime_error("Camera already initialized ! ");
	}
	_camera = &camera;
	_camera -> setSize(_size);
}

void AbstractFrame::start() {
	using namespace std::chrono;	
	initOpenGLState();
	_running = true;
	while (!glfwWindowShouldClose(_frame) && _running) {
		glfwPollEvents();
		render();
		glfwSwapBuffers(_frame);
    }
}

void AbstractFrame::stop() {
	_running = false;
}

void AbstractFrame::initOpenGLState() {
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);       
	glCullFace(GL_BACK);         
	glFrontFace(GL_CCW);
}

void AbstractFrame::render() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_camera -> render();
	_world -> render();	
	glDisable(GL_DEPTH_TEST);
	renderHUD();
}

};

