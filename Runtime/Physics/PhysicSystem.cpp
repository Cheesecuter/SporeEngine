#include <PhysicSystem.hpp>

namespace Layers
{
	static constexpr JPH::ObjectLayer NON_MOVING = 0;
	static constexpr JPH::ObjectLayer MOVING = 1;
	static constexpr JPH::ObjectLayer NUM_LAYERS = 2;
}

namespace BroadPhaseLayers
{
	static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
	static constexpr JPH::BroadPhaseLayer MOVING(1);
	static constexpr Spore::uint32 NUM_LAYERS(2);
}

namespace Spore
{
	static void TraceImpl(const char* p_FMT, ...);
#ifdef JPH_ENABLE_ASSERTS

	static bool AssertFailedImpl(const char* p_expression, const char* p_message, const char* p_file, uint32 p_line);

#endif

	PhysicSystem::PhysicSystem()
	{

	}

	PhysicSystem::~PhysicSystem()
	{

	}

	void PhysicSystem::Init()
	{
		JPH::RegisterDefaultAllocator();

		JPH::Trace = TraceImpl;
		JPH_IF_ENABLE_ASSERTS(JPH::AssertFailed = AssertFailedImpl);

		JPH::Factory::sInstance = new JPH::Factory();

		JPH::RegisterTypes();


	}

	void PhysicSystem::Terminate()
	{

	}

	static void TraceImpl(const char* p_FMT, ...)
	{
		va_list list;
		va_start(list, p_FMT);
		char buffer [1024];
		vsnprintf(buffer, sizeof(buffer), p_FMT, list);
		va_end(list);

		std::cout << buffer << std::endl;
	}

#ifdef JPH_ENABLE_ASSERTS

	static bool AssertFailedImpl(const char* p_expression, const char* p_message, const char* p_file, uint32 p_line)
	{
		std::cout << p_file << ":" << p_line << ": (" << p_expression << ") " << (p_message != nullptr ? p_message : "") << std::endl;
		return true;
	}

#endif
}