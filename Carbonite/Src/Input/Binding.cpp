#include "Binding.h"

namespace Input
{
	bool operator==(Binding lhs, Binding rhs)
	{
		return lhs.m_Location == rhs.m_Location && lhs.m_ID == rhs.m_ID && lhs.m_Index == rhs.m_Index;
	}
} // namespace Input