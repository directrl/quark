module;
#include <glad/gl.h>
#include <quill/LogMacros.h>

export module game.scenes:hello;
import quark.render;
import quark.log;

export namespace game::scenes {

	class HelloScene : public quark::render::Scene {
	public:
		void update(float delta) override {

		}

		void render(int windowId, GladGLContext* gl) override {
			LOG_DEBUG(quark::log::PROGRAM_LOGGER, "meow");
		}
	};
}
