#include "Node.h"

#include <utility>

namespace Renderer::RHI
{
	Node::Node(const std::string& name)
	    : m_Name(name) {}

	Node::Node(std::string&& name)
	    : m_Name(std::move(name)) {}

	Node::~Node()
	{
		detachChildren();
		for (auto parent : m_Parents)
		{
			std::erase(parent->m_Children, this);
			parent->onChildDetached(this);
		}
		m_Parents.clear();
	}

	bool Node::isDirectChild(Node* node)
	{
		return std::find(m_Children.begin(), m_Children.end(), node) != m_Children.end();
	}

	bool Node::isIndirectChild(Node* node)
	{
		if (isDirectChild(node))
			return true;

		for (auto child : m_Children)
			if (child->isIndirectChild(node))
				return true;

		return false;
	}

	bool Node::isIndirectParent(Node* node)
	{
		if (isDirectParent(node))
			return true;

		for (auto parent : m_Parents)
			if (parent->isIndirectParent(node))
				return true;

		return false;
	}

	bool Node::attachChild(Node* node)
	{
		if (node->isIndirectChild(this))
			return false;

		m_Children.emplace_back(node);
		node->m_Parents.emplace_back(this);
		node->onAttached(this);
		onChildAttached(node);
		return true;
	}

	void Node::detachChild(Node* node)
	{
		if (std::erase(m_Children, node))
		{
			std::erase(node->m_Parents, this);
			node->onDetached(this);
			onChildDetached(node);
		}
	}

	void Node::detachChildren()
	{
		for (auto child : m_Children)
		{
			std::erase(child->m_Parents, this);
			child->onDetached(this);
		}
		m_Children.clear();
	}

	void Node::setName(const std::string& name)
	{
		m_Name = name;
	}

	void Node::setName(std::string&& name)
	{
		m_Name = std::move(name);
	}
} // namespace Renderer::RHI