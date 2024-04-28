#include <PhysicSystem.hpp>
#include <PTSimpleTest.hpp>
#include <ConsoleLogger.hpp>

namespace Spore
{
	static void TraceImpl(const char* p_FMT, ...);

#ifdef JPH_ENABLE_ASSERTS

	static bool AssertFailedImpl(const char* p_expression, const char* p_message, const char* p_file, uint32 p_line);

#endif

	static constexpr uint32 c_num_bodies = 10240;
	static constexpr uint32 c_num_body_mutexes = 0;
	static constexpr uint32 c_max_body_pairs = 65536;
	static constexpr uint32 c_max_contact_constraints = 20480;

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

		SetRenderFrequency(m_update_frequency);

	#ifdef JPH_DISABLE_TEMP_ALLOCATOR
		m_temp_allocator = new JPH::TempAllocatorMalloc();
	#else
		m_temp_allocator = new JPH::TempAllocatorImpl(32 * 1024 * 1024);
	#endif

		m_job_system = new JPH::JobSystemThreadPool(c_max_physics_jobs, c_max_physics_barriers, m_max_concurrent_jobs - 1);

		m_job_system_validating = new JPH::JobSystemSingleThreaded(c_max_physics_jobs);

		//Start(JPH_RTTI(PTSimpleTest));
		//PTSimpleTest* ptsimpleTest = new PTSimpleTest();
		//Start(ptsimpleTest);
	}

	void PhysicSystem::Terminate()
	{

	}

	void PhysicSystem::AddScene(Scene* p_scene)
	{
		vec3f old_gravity = m_physics_system != nullptr ? Vec3f(m_physics_system->GetGravity()) : vec3f(0.0f, -9.81f, 0.0f);
		old_gravity = vec3f(0.0f, -2.0f, 0.0f);
		m_physics_system = new JPH::PhysicsSystem();
		m_physics_system->Init(c_num_bodies, c_num_body_mutexes, c_max_body_pairs, c_max_contact_constraints,
							   m_broad_phase_layer_interface, m_object_vs_broad_phase_layer_filter, m_object_vs_object_layer_filter);
		m_physics_system->SetPhysicsSettings(m_physics_settings);
		m_physics_system->SetGravity(JPHVec3(old_gravity));

		p_scene->SetPhysicsSystem(m_physics_system);
		p_scene->SetJobSystem(m_job_system);
		p_scene->SetTempAllocator(m_temp_allocator);
		if (m_install_contact_listener)
		{
			m_contact_listener = new ContactListenerImpl;
			m_contact_listener->SetNextListener(p_scene->GetContactListener());
			m_physics_system->SetContactListener(m_contact_listener);
		}
		else
		{
			m_contact_listener = nullptr;
			m_physics_system->SetContactListener(p_scene->GetContactListener());
		}
		p_scene->InitPhysics();
		//p_scene->CreateFloor();
		m_physics_system->OptimizeBroadPhase();
	}

	void PhysicSystem::Start(PhysicsTest* p_test)
	{
		vec3f old_gravity = m_physics_system != nullptr ? Vec3f(m_physics_system->GetGravity()) : vec3f(0.0f, -9.81f, 0.0f);

		m_physics_system = new JPH::PhysicsSystem();
		m_physics_system->Init(c_num_bodies, c_num_body_mutexes, c_max_body_pairs, c_max_contact_constraints,
							   m_broad_phase_layer_interface, m_object_vs_broad_phase_layer_filter, m_object_vs_object_layer_filter);
		m_physics_system->SetPhysicsSettings(m_physics_settings);
		m_physics_system->SetGravity(JPHVec3(old_gravity));

		//m_test_class = p_RTTI;
		//m_test = static_cast<PhysicsTest*>(p_RTTI->CreateObject());
		m_test = dynamic_cast<PTSimpleTest*>(p_test);
		m_test->SetPhysicsSystem(m_physics_system);
		m_test->SetJobSystem(m_job_system);
		m_test->SetTempAllocator(m_temp_allocator);
		if (m_install_contact_listener)
		{
			m_contact_listener = new ContactListenerImpl;
			m_contact_listener->SetNextListener(m_test->GetContactListener());
			m_physics_system->SetContactListener(m_contact_listener);
		}
		else
		{
			m_contact_listener = nullptr;
			m_physics_system->SetContactListener(m_test->GetContactListener());
		}
		m_test->Init();
		m_physics_system->OptimizeBroadPhase();

	}

	bool PhysicSystem::Update(float32 p_delta_time)
	{
		if (m_max_concurrent_jobs != m_job_system->GetMaxConcurrency())
		{
			static_cast<JPH::JobSystemThreadPool*>(m_job_system)->SetNumThreads(m_max_concurrent_jobs - 1);
		}

		DrawPhysics();
		StepPhysics(m_job_system);

		return true;
	}

	void PhysicSystem::Tick(uint32 step)
	{
		while (m_test->IsActive())
		{
			++step;
			m_test->Tick(step);
			const int cCollisionSteps = 1;
			m_physics_system->Update(1.0f / 60.0f, cCollisionSteps, m_temp_allocator, m_job_system);
		}
	}

	void PhysicSystem::DrawPhysics()
	{

	}

	void PhysicSystem::StepPhysics(JPH::JobSystem* p_job_stream)
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
		ConsoleLogger::GetInstance().Logger()->info("{}:{}: ({}) {}", p_file, p_line, p_expression, (p_message != nullptr ? p_message : ""));
		//std::cout << p_file << ":" << p_line << ": (" << p_expression << ") " << (p_message != nullptr ? p_message : "") << std::endl;
		return true;
	}

#endif
}