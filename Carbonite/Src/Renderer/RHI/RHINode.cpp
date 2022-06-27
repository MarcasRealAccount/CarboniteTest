#include "RHINode.h"

namespace Renderer::RHI
{
	RHINode::RHINode(const std::string& name)
	    : Node(name), m_Recreate(false), m_Created(false) {}

	RHINode::RHINode(std::string&& name)
	    : Node(std::move(name)), m_Recreate(false), m_Created(false) {}

	bool RHINode::create()
	{
		if (isDestructible())
		{
			bool pCreated = m_Created;
			if (pCreated)
			{
				m_Recreate = true;
				destroy();
			}

			createImpl();
			m_Created = isValid();
			if (pCreated && m_Created)
			{
				for (auto& child : m_DestroyedChildren)
					child->create();
				m_DestroyedChildren.clear();
			}
			m_Recreate = false;
			return m_Created;
		}
		else
		{
			m_Recreate = true;
			destroy();

			createImpl();
			m_Created = true;
			for (auto& child : m_DestroyedChildren)
				child->create();
			m_DestroyedChildren.clear();

			m_Recreate = false;
			return true;
		}
	}

	void RHINode::destroy()
	{
		bool recreate = m_Recreate || !isDestructible();

		if (recreate)
			m_DestroyedChildren.clear();

		auto& children = getChildren();
		for (auto itr = children.rbegin(); itr != children.rend(); ++itr)
		{
			auto rhiChild = reinterpret_cast<RHINode*>(*itr);
			if (rhiChild->isValid())
			{
				rhiChild->destroy();
				if (recreate && rhiChild->isDestructible())
					m_DestroyedChildren.emplace_back(rhiChild);
			}
		}

		if (isDestructible())
		{
			if (m_Created)
				destroyImpl();
		}
		else
		{
			destroyImpl();
		}
		m_Created = false;
	}

	void RHINode::onDetached([[maybe_unused]] Node* parent)
	{
		detachChildren();
		destroy();
	}
} // namespace Renderer::RHI