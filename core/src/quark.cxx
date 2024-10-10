module;
#include <string>
#include <quill/Backend.h>
#include <argparse/argparse.hpp>
#include <quill/Logger.h>
#include <quill/LogMacros.h>
#include <GLFW/glfw3.h>

module quark;
import quark.render;

namespace quark {

	Quark::Quark(const std::string& id) : id(id) {
		GLOBAL = this;

		config::PROGRAM_DATA_ROOT = config::ENGINE_DATA_ROOT / id;
		config::PROGRAM_CONFIG_ROOT = config::PROGRAM_DATA_ROOT / "config";
	}

	Quark::~Quark() {
		glfwTerminate();
		GLOBAL = nullptr;
	};

	int Quark::start(int argc, char* argv[]) {
		quill::Backend::start({ });

		argparse::ArgumentParser cmd(config::BASENAME);

		cmd.add_argument("--log-level")
		   .help("Set the default log level for both the engine and the program")
		   .default_value("info");

		try {
			cmd.parse_args(argc, argv);
		} catch(const std::exception& e) {
			std::cerr << e.what() << std::endl;
			std::cerr << cmd;
			std::exit(1);
		}

		quill::LogLevel logLevel = quill::LogLevel::Info;
		const std::unordered_map<std::string, quill::LogLevel> logLevelMap = {
			{ "info", quill::LogLevel::Info },
			{ "warn", quill::LogLevel::Warning },
			{ "error", quill::LogLevel::Error },
			{ "debug", quill::LogLevel::Debug },
			{ "trace", quill::LogLevel::TraceL3 },
		};

		auto iter = logLevelMap.find(cmd.get("--log-level"));
		if (iter != logLevelMap.end()) logLevel = iter->second;
		std::cout << "Setting log level: " << cmd.get("--log-level") << std::endl;

		log::ENGINE_LOGGER = log::create_logger(config::BASENAME, logLevel, config::ENGINE_DATA_ROOT);
		log::PROGRAM_LOGGER = log::create_logger(id, logLevel, config::PROGRAM_DATA_ROOT);

		LOG_INFO(log::ENGINE_LOGGER, "Hello!");
		running = true;

		if(!glfwInit()) {
			throw new std::runtime_error("Failed to initialize GLFW");
		}

		init();
		assert(windows.size() > 0);

		const auto& primaryWindow = windows[0];
		while(!glfwWindowShouldClose(primaryWindow->handle) && running) {
			delta_clock.start();

			for(const auto& window : windows) {
				window->begin();

				if(window->scene != nullptr) {
					window->scene->update(delta_clock.get_delta_time());
					window->scene->render(window->get_id(), window->gl);
				}

				window->end();
			}

			delta_clock.end();
		}

		return 0;
	}
}
