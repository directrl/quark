module;
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <quill/LogMacros.h>

export module quark.render:gl;
import quark.log;

export namespace quark::render {

	const int OPENGL_VERSION_MINOR = 3;
	const int OPENGL_VERSION_MAJOR = 3;
	const int OPENGL_PROFILE = GLFW_OPENGL_CORE_PROFILE;

	GladGLContext* create_gl_context(GLFWwindow* window) {
		glfwMakeContextCurrent(window);

		auto* context = new GladGLContext;
		int glVersion = gladLoadGLContext(context, glfwGetProcAddress);

		if(!context) {
			LOG_ERROR(log::ENGINE_LOGGER, "Failed to create OpenGL context");
			return nullptr;
		}

		LOG_INFO(log::ENGINE_LOGGER, "Using OpenGL {}.{}",
			GLAD_VERSION_MAJOR(glVersion), GLAD_VERSION_MINOR(glVersion));

		return context;
	}
}
