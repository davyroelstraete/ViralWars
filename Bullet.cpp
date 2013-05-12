//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Bullet.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// X methods																				
//-----------------------------------------------------------------

Bullet::Bullet(const D3DXVECTOR2& pos, const float& angle) : Entity()																				
{
	m_isDead = false;
	Init(_T("Bullet"), pos, angle);
}

Bullet::~Bullet()																						
{
	// nothing to destroy
}

bool Bullet::isDead()
{
	return m_isDead;
}

void Bullet::Die()
{
	m_isDead = true;
}

void Bullet::Tick(float dtime)
{
	D3DXVECTOR2 pos = GetPosition();
	pos += (D3DXVECTOR2(cos(GetAngle()), sin(GetAngle())) * BULLETSPEED * dtime);
	SetPosition(pos);


	//the bullet is outside of the screen, so he can be removed
	if ((pos.x < 0.0f - BULLETWIDTH) || (pos.x > SPRITE_ENGINE->GetBackBufferWidth() + BULLETWIDTH) || (pos.y < 0.0f - BULLETHEIGHT) || (pos.y > SPRITE_ENGINE->GetBackBufferHeight() + BULLETHEIGHT))
	{
		m_isDead = true;
	}
}

void Bullet::ReInit(const D3DXVECTOR2& pos, const float& angle)
{
	m_isDead = false;
	SetPosition(pos);
	SetRotation(angle);
}


