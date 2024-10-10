module;
#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

export module quark.graphics:window;
import :gl;
import :scene;

namespace quark::graphics {

	GLFWwindow* SHARED_CONTEXT = nullptr;
	int WINDOW_LAST_ID = -1;

	export class Window {
	private:
		const int id;

		GLFWmonitor* monitor = nullptr;
		bool current = false;
	public:
		GLFWwindow* handle = nullptr;
		GladGLContext* gl = nullptr;

		std::unique_ptr<Scene> scene = nullptr;

		Window() : id(++WINDOW_LAST_ID) { }

		~Window() {
			if(handle != nullptr) destroy();
			if(gl != nullptr) free(gl);
		}

		bool create()  {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
			glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

			handle = glfwCreateWindow(
				640,
				480,
				"Window",
				monitor,
				SHARED_CONTEXT
			);

			if(handle == nullptr) return false;
			if(SHARED_CONTEXT == nullptr) SHARED_CONTEXT = handle;
			if(!(gl = create_gl_context(handle))) return false;
			return true;
		}

		void destroy() {
			if(handle != nullptr) glfwDestroyWindow(handle);
			handle = nullptr;
		}

		void show() {
			assert(handle != nullptr);
			glfwShowWindow(handle);
		}

		void hide() {
			assert(handle != nullptr);
			glfwHideWindow(handle);
		}

		void begin() {
			assert(handle != nullptr);
			assert(!current);

			glfwMakeContextCurrent(handle);
			current = true;

			int framebufferWidth, framebufferHeight;
			glfwGetFramebufferSize(handle, &framebufferWidth, &framebufferHeight);

			gl->Viewport(0, 0, framebufferWidth, framebufferHeight);
			gl->ClearColor(0, 0, 0, 0);
			gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void end() {
			assert(handle != nullptr);
			assert(current);

			glfwSwapBuffers(handle);
			glfwPollEvents();

			current = false;
		}

		int get_id() const { return id; }

		GLFWmonitor* get_monitor() const { return monitor; }
		void set_monitor(GLFWmonitor* monitor) { this->monitor = monitor; }

		void get_size(int& width, int& height) const {
			assert(handle != nullptr);
			glfwGetWindowSize(handle, &width, &height);
		}

		void set_size(int width, int height) {
			assert(handle != nullptr);
			glfwSetWindowSize(handle, width, height);
		}

		void get_position(int& x, int& y) const {
			assert(handle != nullptr);
			glfwGetWindowPos(handle, &x, &y);
		}

		void set_position(int x, int y) {
			assert(handle != nullptr);

			if(x <= 0 || y <= 0) {
				const GLFWvidmode* videoMode;

				if(monitor != nullptr) videoMode = glfwGetVideoMode(monitor);
				else videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

				int width, height;
				get_size(width, height);

				glfwSetWindowPos(
					handle,
					(videoMode->width / 2) - (width / 2),
					(videoMode->height / 2) - (height / 2)
				);
			} else {
				glfwSetWindowPos(handle, x, y);
			}
		}
	};
}
