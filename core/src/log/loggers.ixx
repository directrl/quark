module;
#include <quill/Frontend.h>
#include <quill/Logger.h>
#include <quill/sinks/ConsoleSink.h>
#include <quill/sinks/RotatingFileSink.h>
#include <filesystem>
#include <format>

using qf = quill::Frontend;

export module quark.log:loggers;

export namespace quark::log {

	quill::Logger* ENGINE_LOGGER;
	quill::Logger* PROGRAM_LOGGER;

	quill::Logger* create_logger(
		const std::string& id,
		const quill::LogLevel& logLevel,
		const std::filesystem::path& dataPath
	) {
		auto consoleSink = qf::create_or_get_sink<quill::ConsoleSink>(
			std::format("{}_csink", id));
		auto fileSink = qf::create_or_get_sink<quill::RotatingFileSink>(
			dataPath / "logs" / "latest.log",
			[]() {
				quill::RotatingFileSinkConfig config;
				config.set_open_mode('a');
				config.set_max_backup_files(10);
				config.set_rotation_frequency_and_interval('H', 24);

				return config;
			}()
		);

		auto* logger = qf::create_or_get_logger(id, {
			std::move(consoleSink),
			std::move(fileSink)
		});
		logger->set_log_level(logLevel);

		return logger;
	}
}
