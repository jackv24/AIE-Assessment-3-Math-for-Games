#include "SceneNode.h"

SceneNode::SceneNode()
{
	m_parent = nullptr;

	m_local_transform = Matrix3::CreateIdentity();
}
SceneNode::~SceneNode()
{
}

void SceneNode::SetParent(SceneNode* node)
{
	m_parent = node;
}
void SceneNode::AddChild(SceneNode* node)
{
	m_children.push_back(node);
	node->SetParent(this);
}
void SceneNode::RemoveChild(SceneNode* node)
{
	m_children.erase(std::find(m_children.begin(), m_children.end(), node));
	node->SetParent(nullptr);
}

void SceneNode::UpdateTransforms()
{
	if (m_parent != nullptr)
		m_global_transform = m_parent->m_global_transform * m_local_transform;
	else
		m_global_transform = m_local_transform;
	for (unsigned int i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->UpdateTransforms();
	}
}