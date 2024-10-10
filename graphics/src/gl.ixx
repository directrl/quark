module;
#include <glad/gl.h>
#include <GLFW/glfw3.h>

export module quark.graphics:gl;

export namespace quark::graphics {

	const int OPENGL_VERSION_MINOR = 3;
	const int OPENGL_VERSION_MAJOR = 3;
	const int OPENGL_PROFILE = GLFW_OPENGL_CORE_PROFILE;

	GladGLContext* create_gl_context(GLFWwindow* window) {
		glfwMakeContextCurrent(window);

		auto* context = new GladGLContext;
		gladLoadGLContext(context, glfwGetProcAddress);

		return context;
	}
}
