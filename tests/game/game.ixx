module;
#include <algorithm>
#include <memory>

export module game;
import quark;
import quark.render;
import game.scenes;

export namespace game {

	class Game : public quark::Quark {
	public:
		Game() : Quark("game") { }

		void init() override {
			auto window = std::make_shared<quark::render::Window>();

			if(!window->create()) {
				throw std::runtime_error("Failed to create window");
			}

			window->set_position(-1, -1);
			window->set_size(1280, 720);
			window->show();

			scenes::HelloScene hello;
			window->scene = static_cast<quark::render::Scene>(hello);

			windows.push_back(window);
		}

		void update() override { }
	};
}
