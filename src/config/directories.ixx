module;
#include <filesystem>
#include <cstdlib>
#include <format>
#include <stdexcept>

export module quark.config:directories;

export namespace quark::config {

	const std::string BASENAME = "quark";
	
	inline const std::filesystem::path ENGINE_DATA_ROOT =
#ifdef WINDOWS
		[] -> std::filesystem::path {
			const auto appdata = std::getenv("APPDATA");
			
			if(appdata && !std::string(appdata).empty()) {
				return { std::format("{}/{}", appdata, BASENAME) };
			} else {
				throw std::runtime_error("could not determine the data root path");
			}
		}();
#elif MAC
		[] -> std::filesystem::path {
			const auto userHome = std::getenv("HOME");
			
			if(userHome && !std::string(userHome).empty()) {
				return { std::format("{}/Library/Application Support/{}", userHome, BASENAME) };
			} else {
				throw std::runtime_error("could not determine the data root path");
			}
		}();
#elif LINUX
		[] -> std::filesystem::path {
			const auto dataHome = std::getenv("XDG_DATA_HOME");
			const auto userHome = std::getenv("HOME");
			
			if(dataHome && !std::string(dataHome).empty()) {
				return { std::format("{}/{}", dataHome, BASENAME) };
			} else if(userHome && !std::string(userHome).empty()) {
				return { std::format("{}/.local/share/{}", userHome, BASENAME) };
			} else {
				throw std::runtime_error("could not determine the data root path");
			}
		}();
#endif
	
	const std::filesystem::path ENGINE_CONFIG_ROOT(ENGINE_DATA_ROOT / "config");
	
	std::filesystem::path PROGRAM_DATA_ROOT;
	std::filesystem::path PROGRAM_CONFIG_ROOT;
}
