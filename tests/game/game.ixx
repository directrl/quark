module;
#include <algorithm>
#include <memory>

export module game;
import quark;
import quark.graphics;
import game.scenes;

export namespace game {

	class Game : public quark::Quark {
	public:
		Game() : Quark("game") { }

		void init() override {
			auto window = std::make_unique<quark::graphics::Window>();

			if(!window->create()) {
				throw std::runtime_error("Failed to create window");
			}

			window->set_position(-1, -1);
			window->set_size(1280, 720);
			window->show();

			auto hello = std::unique_ptr<quark::graphics::Scene>(new scenes::HelloScene);
			window->scene = std::move(hello);

			windows.push_back(std::move(window));
		}

		void update() override { }
	};
}
