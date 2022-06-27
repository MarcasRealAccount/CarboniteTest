#pragma once

#include <string>
#include <vector>

namespace Renderer::RHI
{
	struct Node
	{
	public:
		Node(const std::string& name);
		Node(std::string&& name);
		virtual ~Node();

		bool isDirectChild(Node* node);
		bool isDirectParent(Node* node) { return node->isDirectChild(node); }
		bool isIndirectChild(Node* node);
		bool isIndirectParent(Node* node);

		bool attachChild(Node* node);
		void detachChild(Node* node);

		auto& getName() const { return m_Name; }
		auto& getChildren() const { return m_Children; }
		auto& getParents() const { return m_Parents; }

	protected:
		void detachChildren();

		void setName(const std::string& name);
		void setName(std::string&& name);

	private:
		virtual void onDetached([[maybe_unused]] Node* parent) {}
		virtual void onAttached([[maybe_unused]] Node* parent) {}
		virtual void onChildDetached([[maybe_unused]] Node* child) {}
		virtual void onChildAttached([[maybe_unused]] Node* child) {}

	private:
		std::string        m_Name;
		std::vector<Node*> m_Children;
		std::vector<Node*> m_Parents;
	};
} // namespace Renderer::RHI