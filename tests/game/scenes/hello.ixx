module;
#include <glad/gl.h>

export module game.scenes:hello;
import quark.render;

export namespace game::scenes {

	class HelloScene : public quark::render::Scene {
	public:
		void update(float delta) override {

		}

		void render(int windowId, GladGLContext* gl) override {

		}
	};
}
