#include "Entity.h"


Entity::Entity():m_pSprite(NULL),
                    m_BC(NULL)
{
}
Entity::~Entity()
{
}
bool Entity::Init(const tstring& filepath, const D3DXVECTOR2& pos, const float& angle)
{
	m_pSprite = new Sprite();
    if(!m_pSprite->Init(TextureDir + filepath + _T(".dds"))) return false;

	SetPosition(D3DXVECTOR2(m_pSprite->GetWidth() *  0.5f, m_pSprite->GetHeight() * 0.5f), pos);
	m_BC = new BoundingCircle(m_pSprite->GetPositionAdress(), m_pSprite->GetWidth() * 0.4f); //radius is 80% of half of the sprite width, the collisions seem more realistic this way 
	SetRotation(angle);
	SetScale(1.0f);

	return true;
}
void Entity::Draw()
{
	m_pSprite->Draw();
}
void Entity::DrawByRect(const RECT& rect)
{
	m_pSprite->DrawByRect(rect);
}

bool Entity::CollidesWith(const BoundingCircle * const bc)
{
	return m_BC->CollidesWith(bc);
}

void Entity::SetPosition(const D3DXVECTOR2& center, const D3DXVECTOR2& pos)
{
	m_pSprite->SetPosition(center, pos);
}
void Entity::SetPosition(const D3DXVECTOR2& pos)
{
	m_pSprite->SetPosition(pos);
}
void Entity::SetRotation(const float& angle)
{
	m_pSprite->SetRotation(angle);
}
void Entity::SetScale(const D3DXVECTOR2& scale)
{
	m_pSprite->SetScale(scale);
	m_BC->SetRadius(GetWidth() * 0.4f * scale.x);
}
void Entity::SetScale(const float& scale)
{
	m_pSprite->SetScale(D3DXVECTOR2(scale, scale));
	m_BC->SetRadius(GetWidth() * 0.4f * scale);
}
const float& Entity::GetWidth() const
{
	return m_pSprite->GetWidth();
}
const float& Entity::GetHeight() const
{
	return m_pSprite->GetHeight();
}

const D3DXVECTOR2& Entity::GetPosition() const
{
	return m_pSprite->GetPosition();
}
const D3DXVECTOR2* const Entity::GetPositionAdress() const
{
	return m_pSprite->GetPositionAdress();
}
const D3DXVECTOR2& Entity::GetCenter() const
{
	return m_pSprite->GetCenter();
}
const float& Entity::GetAngle() const
{
	return m_pSprite->GetAngle();
}
const D3DXVECTOR2& Entity::GetScale() const
{
	return m_pSprite->GetScale();
}
const BoundingCircle *const Entity::GetBC() const
{
	return m_BC;
}