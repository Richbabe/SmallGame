
#include "stdafx.h"
#include "SpriteNode.h"

SpriteNode::SpriteNode()
{
}

SpriteNode::~SpriteNode()
{
}

std::shared_ptr<SpriteNode>  SpriteNode::Create(const char * fileName)
{
	return nullptr;
}

void SpriteNode::SetTexture(std::shared_ptr<GameTexture> textture)
{
	m_texture = textture;
}
