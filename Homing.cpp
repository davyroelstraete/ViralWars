//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Homing.h"	

#include "SpriteEngine.h"
#include "FontManager.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Homing methods																				
//-----------------------------------------------------------------

Homing::Homing(Entity* self, Entity* target, const float& turningspeed, const float& movespeed):MoveBehaviour(self,target)																						
{
	m_TurningSpeed = turningspeed;
	m_MoveSpeed = movespeed;
}

Homing::~Homing()																						
{
	// nothing to destroy
}

void Homing::Move(float dtime)
{
	D3DXVECTOR2 dir = m_pTarget->GetPosition() - m_pSelf->GetPosition();
	float distance = D3DXVec2Length(&dir);
	if (distance > 10)
	{
		D3DXVec2Normalize(&dir, &dir);
		D3DXVECTOR2 curDir = D3DXVECTOR2(cos(m_pSelf->GetAngle()), sin(m_pSelf->GetAngle()));

		D3DXVECTOR2 alteredDir; 
		D3DXVec2Lerp(&alteredDir, &curDir, &dir, m_TurningSpeed);
		float alteredAngle = atan2(alteredDir.y, alteredDir.x);

		//update angle and position
		m_pSelf->SetRotation(alteredAngle);
		m_pSelf->SetPosition(m_pSelf->GetPosition() + (D3DXVECTOR2(cos(alteredAngle), sin(alteredAngle)) * m_MoveSpeed * dtime));
	}
}