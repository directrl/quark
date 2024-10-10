module;
#include <glad/gl.h>

export module quark.render:scene;

export namespace quark::render {

	class Scene {
	public:
		virtual ~Scene() = default;

		virtual void update(float delta) { }
		virtual void render(int windowId, GladGLContext* gl) { }
	};
}
