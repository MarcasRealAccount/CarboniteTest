#pragma once

#include "Node.h"

namespace Renderer::RHI
{
	struct RHINode : public Node
	{
	public:
		RHINode(const std::string& name);
		RHINode(std::string&& name);
		RHINode(const RHINode&) = delete;
		RHINode(RHINode&&)      = delete;

		bool create();
		void destroy();

	private:
		virtual void onDetached(Node* parent) override;

		virtual void createImpl() {}
		virtual void destroyImpl() {}
		virtual bool isDestructible() { return false; }
		virtual bool isValid() { return true; }

	protected:
		bool m_Recreate;

	private:
		bool                  m_Created;
		std::vector<RHINode*> m_DestroyedChildren;
	};
} // namespace Renderer::RHI