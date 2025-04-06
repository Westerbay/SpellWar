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

Size AbstractFrame::_frameSize = {0, 0};

void AbstractFrame::frameResize(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);
	_frameSize = {(unsigned) width, (unsigned) height};
}

void AbstractFrame::processEvents() {
	std::queue<Event> & events = _system.getEvents();
	while (!events.empty()) {
		processEvent(events.front());
		events.pop();
	}
}

AbstractFrame::AbstractFrame(const String & title, Size size) : _running(false) {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW ! ");
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_USED);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_USED);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	if (size.width && size.height) {
		_frame = glfwCreateWindow(size.width, size.height, title.c_str(), NULL, NULL);
	}
	else {
		GLFWmonitor * monitor = glfwGetPrimaryMonitor();
    	const GLFWvidmode * mode = glfwGetVideoMode(monitor);
		_frame = glfwCreateWindow(
			mode -> width,
			mode -> height,
			title.c_str(),
			monitor,
			nullptr
		);
		size.width = mode -> width;
		size.height = mode -> height;
	}
	
	if (_frame == NULL) {
		throw std::runtime_error("Failed to create GLFW window ! ");
	}
	
	glfwMakeContextCurrent(_frame);
	glfwSetFramebufferSizeCallback(_frame, frameResize);
	gladLoadGL();
	
	glViewport(0, 0, size.width, size.height);

	_frameSize = size;
	_world = nullptr;
	_camera = nullptr;
	_light = nullptr;
	System::initContext(_frame);
	glfwSwapInterval(0);
	initOpenGLState();
}

AbstractFrame::~AbstractFrame() {
	glfwDestroyWindow(_frame);
	glfwTerminate();
}

GLFWwindow * AbstractFrame::getFrameWindow() {
	return _frame;
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

void AbstractFrame::setBackgroundColor(ColorRGB color) {
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void AbstractFrame::initWorld(GameObjectGroup * world) {
	if (_world != nullptr) {
		throw std::runtime_error("World already initialized ! ");
	}
	_world = world;
}

void AbstractFrame::initCamera(GameCamera * camera) {
	if (_camera != nullptr) {
		throw std::runtime_error("Camera already initialized ! ");
	}
	_camera = camera;
	_camera -> setSize(_frameSize);
}

bool AbstractFrame::shouldExit() const {
	return glfwWindowShouldClose(_frame);
}

void AbstractFrame::pollEvents() const {
	glfwPollEvents();   
}

void AbstractFrame::swapBuffers() const {
	glfwSwapBuffers(_frame);
}

void AbstractFrame::initLight(GameLight * light) {
	if (_light != nullptr) {
		throw std::runtime_error("Light already initialized ! ");
	}
	_light = light;
}

void AbstractFrame::initOpenGLState() {
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);		
}

void AbstractFrame::render() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	_camera -> setSize(_frameSize);
	_light -> apply(_camera -> getHitbox().position);
	_camera -> apply();

	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);	
	_world -> renderBackground();	
	
	glClear(GL_DEPTH_BUFFER_BIT);	
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);	
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	_world -> render();	

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	_world -> renderHUD(_frameSize);	
}

};

