module;

export module quark.config:os;

export namespace quark::config {
	
	enum class OperatingSystem {
		
		Windows,
		Mac,
		Linux
	};

	const OperatingSystem CURRENT_SYSTEM =
#ifdef WINDOWS
	    OperatingSystem::Windows;
#elif APPLE
#define MAC
        OperatingSystem::Mac;
#elif LINUX
		OperatingSystem::Linux;
#else
#error "Unknown operating system"
#endif
}
