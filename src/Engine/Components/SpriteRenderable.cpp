#include "stdafx.h"

#include "SpriteRenderable.h"

#include "../Game/Game.h"
#include "../Game/GameObject.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components;

SpriteRenderable::SpriteRenderable(GameObject* l_owner, const RenderablePriority::EntryPtr l_renderPriority, Texture* l_texture)
: Renderable(l_owner, l_renderPriority)
, m_sprite()
{
	m_sprite.setTexture(*l_texture, true);
}

SpriteRenderable::SpriteRenderable(GameObject* l_owner, const RenderablePriority::EntryPtr l_renderPriority, Texture* l_texture, const IntRect l_srcRect)
: Renderable(l_owner, l_renderPriority)
, m_sprite()
{
	m_sprite.setTexture(*l_texture, true);
	m_sprite.setTextureRect(l_srcRect);
}

SpriteRenderable::SpriteRenderable(GameObject* l_owner, const RenderablePriority::EntryPtr l_renderPriority, Texture* l_texture, const IntRect l_srcRect, const Vector2f l_scale)
: Renderable(l_owner, l_renderPriority)
, m_sprite()
{
	m_sprite.setTexture(*l_texture, true);
	m_sprite.setTextureRect(l_srcRect);
	m_sprite.setScale(l_scale);
}

ReferenceType::RuntimeType SpriteRenderable::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType SpriteRenderable::RuntimeType()
{
	return "ToD::Components::SpriteRenderable";
}

Sprite SpriteRenderable::GetSprite() const
{
	return m_sprite;
}

void SpriteRenderable::Process(const Time l_gameTime)
{
	m_sprite.setPosition(GetOwner()->GetPosition());
	Get<Game::Shared>()->GetRenderWindow().draw(m_sprite);	
}
