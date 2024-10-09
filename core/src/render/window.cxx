module;
#include <GLFW/glfw3.h>
#include <memory>

module quark.render;
import quark.config;

namespace quark::render {

	Window::Window() : id(++WINDOW_LAST_ID) { }

	Window::~Window() {
		if(handle != nullptr) destroy();
		if(gl != nullptr) free(gl);
	}

	bool Window::create()  {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		handle = glfwCreateWindow(
			640,
			480,
			config::BASENAME.c_str(),
			monitor,
			SHARED_CONTEXT
		);

		if(handle == nullptr) return false;
		if(SHARED_CONTEXT == nullptr) SHARED_CONTEXT = handle;
		if(!(gl = create_gl_context(handle))) return false;
		return true;
	}

	void Window::destroy() {
		if(handle != nullptr) glfwDestroyWindow(handle);
		handle = nullptr;
	}
}
