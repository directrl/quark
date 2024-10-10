module;
#include <filesystem>
#include <quill/Backend.h>
#include <string>
#include <quill/Logger.h>
#include <quill/LogMacros.h>
#include <argparse/argparse.hpp>

#ifdef QUARK_GRAPHICS
namespace quark::graphics {
	class Window;
}
#endif

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

	#ifdef QUARK_GRAPHICS
		std::vector<std::unique_ptr<graphics::Window>> windows;
	#endif

		Quark(const std::string& id);
		virtual ~Quark();

		virtual void init() { }
		virtual void update() { }

		int start(int argc, char* argv[]);
	};

	Quark* Quark::GLOBAL = nullptr;
}
