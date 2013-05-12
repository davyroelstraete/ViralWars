//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Explosion.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Explosion methods																				
//-----------------------------------------------------------------

Explosion::Explosion(const D3DXVECTOR2& pos, const float& maxrange, const float& growspeed, const bool& KillsEnemies):Entity(),
																							m_GrowSpeed(growspeed),
																							m_MaxRadius(maxrange),
																							m_IsDead(false),
																							m_KillsEnemies(KillsEnemies),
																							m_CurrentRadius(0)
{
	Init(_T("Explosion"),pos,0.0f);
	m_BC = new BoundingCircle(GetPositionAdress(), 10.0f);
	SetScale(10.0f / GetWidth());
}

Explosion::~Explosion()																						
{
	// nothing to destroy
}

void Explosion::Tick(float dTime)
{
	if (m_CurrentRadius < m_MaxRadius)
	{
		float currentScale = (GetScale()).x;
		SetScale(currentScale + m_GrowSpeed);
		m_CurrentRadius = GetWidth() * (GetScale()).x * 0.5f;
	}
	else
	{
		m_IsDead = true;
	}
}

void Explosion::Die()
{
	m_IsDead = true;
}

bool Explosion::IsDead()
{
	return m_IsDead;
}
bool Explosion::KillsEnemies()
{
	return m_KillsEnemies;
}

void Explosion::Respawn(const D3DXVECTOR2& pos, const float& maxrange, const float& growspeed, const bool& KillsEnemies)
{
	m_GrowSpeed=growspeed;
	m_MaxRadius=maxrange;
	m_IsDead=false;
	m_KillsEnemies=KillsEnemies;
	m_CurrentRadius = 0;
	SetPosition(pos);
	DestroyObject(m_BC);
	m_BC = new BoundingCircle(GetPositionAdress(), 10.0f);
	SetScale(10.0f / GetWidth());
}






