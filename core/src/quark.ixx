module;
#include <filesystem>
#include <quill/Backend.h>
#include <string>
#include <quill/Logger.h>
#include <quill/LogMacros.h>
#include <argparse/argparse.hpp>

namespace quark::render {
	class Window;
}

export module quark;
import quark.config;
import quark.log;
import quark.utility;

export namespace quark {

	class Quark {
	public:
		static Quark* GLOBAL;

		std::string id {};
		bool running = false;

		utility::DeltaClock delta_clock;
		std::vector<std::unique_ptr<render::Window>> windows;

		Quark(const std::string& id);
		virtual ~Quark();

		virtual void init() { }
		virtual void update() { }

		int start(int argc, char* argv[]);
	};

	Quark* Quark::GLOBAL = nullptr;
}
