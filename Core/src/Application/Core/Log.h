#pragma once

namespace Project {

	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

/// Logger Macros
#define PROJECT_CORE_TRACE(...)	::Project::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PROJECT_CORE_INFO(...)	::Project::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PROJECT_CORE_WARN(...)	::Project::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PROJECT_CORE_ERROR(...)	::Project::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PROJECT_CORE_FATAL(...)	::Project::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define PROJECT_TRACE(...)	::Project::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PROJECT_INFO(...)	::Project::Log::GetClientLogger()->info(__VA_ARGS__)
#define PROJECT_WARN(...)	::Project::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PROJECT_ERROR(...)	::Project::Log::GetClientLogger()->error(__VA_ARGS__)
#define PROJECT_FATAL(...)	::Project::Log::GetClientLogger()->fatal(__VA_ARGS__)

#ifdef ENABLE_ASSERTS
#define PROJECT_CORE_ASSERT(x, ...) do { \
        if (!(x)) { \
            PROJECT_CORE_ERROR("Assertion Failed: " __VA_ARGS__); \
            __debugbreak(); \
        } \
    } while (0)

#define PROJECT_ASSERT(x, ...) do { \
            if (!(x)) { \
                PROJECT_ERROR("Assertion Failed: " __VA_ARGS__); \
                __debugbreak(); \
            } \
        } while (0)

#else
#define ASSERT(x, ...)
#endif