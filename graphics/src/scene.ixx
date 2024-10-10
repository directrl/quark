module;
#include <glad/gl.h>

export module quark.graphics:scene;

export namespace quark::graphics {

	class Scene {
	public:
		virtual ~Scene() = default;

		virtual void update(float delta) { }
		virtual void render(int windowId, GladGLContext* gl) { }
	};
}
