#pragma once

#include <Types.hpp>

namespace Spore
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64 p_uuid);
		UUID(const UUID&) = default;

		operator uint64() const
		{
			return m_UUID;
		}

	protected:

	private:
		uint64 m_UUID;
	};
}

namespace std
{
	template<typename T> struct hash;

	template<>
	struct hash<Spore::UUID>
	{
		std::size_t operator()(const Spore::UUID& uuid) const
		{
			return (Spore::uint64) uuid;
		}
	};
}