module;
#include <chrono>

using namespace std::chrono;

export module quark.utility:clock;

export namespace quark::utility {

	class DeltaClock {
	private:
		system_clock::time_point start_point;
		float delta_time = 1.0f;
	public:
		void start() {
			start_point = system_clock::now();
		}

		void end() {
			auto elapsed = system_clock::now() - start_point;
			delta_time = duration<float>(elapsed * 1000).count();
		}

		float get_delta_time() const { return delta_time; }
	};
}
