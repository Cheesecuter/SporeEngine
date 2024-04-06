#pragma once

#include <Types.hpp>
#include <Math.hpp>
#include <SDKMath.hpp>

namespace Spore
{
	/// If objects are closer than this distance, they are considered to be colliding (used for GJK) (unit: meter)
	constexpr float32 c_default_collision_tolerance = 1.0e-4f;

	/// A factor that determines the accuracy of the penetration depth calculation. If the change of the squared distance is less than tolerance * current_penetration_depth^2 the algorithm will terminate. (unit: dimensionless)
	constexpr float32 c_default_penetration_tolerance = 1.0e-4f; ///< Stop when there's less than 1% change

	/// How much padding to add around objects
	constexpr float32 c_default_convex_radius = 0.05f;

	/// Used by (Tapered)CapsuleShape to determine when supporting face is an edge rather than a point (unit: meter)
	static constexpr float32 c_capsule_projection_slop = 0.02f;

	/// Maximum amount of jobs to allow
	constexpr int32 c_max_physics_jobs = 2048;

	/// Maximum amount of barriers to allow
	constexpr int32 c_max_physics_barriers = 8;

	struct PhysicsSettings
	{
		/// Size of body pairs array, corresponds to the maximum amount of potential body pairs that can be in flight at any time.
		/// Setting this to a low value will use less memory but slow down simulation as threads may run out of narrow phase work.
		int32 m_max_in_flight_body_pairs = 16384;

		/// How many PhysicsStepListeners to notify in 1 batch
		int32 m_step_listeners_batch_size = 8;

		/// How many step listener batches are needed before spawning another job (set to INT_MAX if no parallelism is desired)
		int32 m_step_listener_batches_per_job = 1;

		/// Baumgarte stabilization factor (how much of the position error to 'fix' in 1 update) (unit: dimensionless, 0 = nothing, 1 = 100%)
		float32 m_baumgarte = 0.2f;

		/// Radius around objects inside which speculative contact points will be detected. Note that if this is too big
		/// you will get ghost collisions as speculative contacts are based on the closest points during the collision detection
		/// step which may not be the actual closest points by the time the two objects hit (unit: meters)
		float32 m_speculative_contact_distance = 0.02f;

		/// How much bodies are allowed to sink into each other (unit: meters)
		float32 m_penetration_slop = 0.02f;

		/// Fraction of its inner radius a body must move per step to enable casting for the LinearCast motion quality
		float32 m_linear_cast_threshold = 0.75f;

		/// Fraction of its inner radius a body may penetrate another body for the LinearCast motion quality
		float32 m_linear_cast_max_penetration = 0.25f;

		/// Max squared distance to use to determine if two points are on the same plane for determining the contact manifold between two shape faces (unit: meter^2)
		float32 m_manifold_tolerance_sq = 1.0e-6f;

		/// Maximum distance to correct in a single iteration when solving position constraints (unit: meters)
		float32 m_max_penetration_distance = 0.2f;

		/// Maximum relative delta position for body pairs to be able to reuse collision results from last frame (units: meter^2)
		float32 m_body_pair_cache_max_delta_position_sq = Square(0.001f); ///< 1 mm

		/// Maximum relative delta orientation for body pairs to be able to reuse collision results from last frame, stored as cos(max angle / 2)
		float32 m_body_pair_cache_cos_max_delta_rotation_div2 = 0.99984769515639123915701155881391f; ///< cos(2 degrees / 2)

		/// Maximum angle between normals that allows manifolds between different sub shapes of the same body pair to be combined
		float32 m_contact_normal_cos_max_delta_rotation = 0.99619469809174553229501040247389f; ///< cos(5 degree)

		/// Maximum allowed distance between old and new contact point to preserve contact forces for warm start (units: meter^2)
		float32 m_contact_point_preserve_lambda_max_dist_sq = Square(0.01f); ///< 1 cm

		/// Number of solver velocity iterations to run
		/// Note that this needs to be >= 2 in order for friction to work (friction is applied using the non-penetration impulse from the previous iteration)
		uint32 m_num_velocity_steps = 10;

		/// Number of solver position iterations to run
		uint32 m_num_position_steps = 2;

		/// Minimal velocity needed before a collision can be elastic (unit: m)
		float32 m_min_velocity_for_restitution = 1.0f;

		/// Time before object is allowed to go to sleep (unit: seconds)
		float32 m_time_before_sleep = 0.5f;

		/// Velocity of points on bounding box of object below which an object can be considered sleeping (unit: m/s)
		float32 m_point_velocity_sleep_threshold = 0.03f;

		/// By default the simulation is deterministic, it is possible to turn this off by setting this setting to false. This will make the simulation run faster but it will no longer be deterministic.
		bool m_deterministic_simulation = true;

		///@name These variables are mainly for debugging purposes, they allow turning on/off certain subsystems. You probably want to leave them alone.
		///@{

		/// Whether or not to use warm starting for constraints (initially applying previous frames impulses)
		bool m_constraint_warm_start = true;

		/// Whether or not to use the body pair cache, which removes the need for narrow phase collision detection when orientation between two bodies didn't change
		bool m_use_body_pair_contact_cache = true;

		/// Whether or not to reduce manifolds with similar contact normals into one contact manifold (see description at Body::SetUseManifoldReduction)
		bool m_use_manifold_reduction = true;

		/// If we split up large islands into smaller parallel batches of work (to improve performance)
		bool m_use_large_is_land_splitter = true;

		/// If objects can go to sleep or not
		bool m_allow_sleeping = true;

		/// When false, we prevent collision against non-active (shared) edges. Mainly for debugging the algorithm.
		bool m_check_active_edges = true;

		///@}
	};
}
