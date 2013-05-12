//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "IdlyDrifting.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// IdlyDrifting methods																				
//-----------------------------------------------------------------

IdlyDrifting::IdlyDrifting(Entity* self, Entity* target, const int& speed):MoveBehaviour(self,target)																						
{
	float rnd = static_cast<float>(rand() % 360);
	m_RandomDir = D3DXVECTOR2(cos(rnd),sin(rnd));
	m_Rect.top = m_Rect.left = 0;
	m_Rect.bottom = static_cast<long>(SPRITE_ENGINE->GetBackBufferHeight());
	m_Rect.right = static_cast<long>(SPRITE_ENGINE->GetBackBufferWidth());
	m_Speed = speed;
}

IdlyDrifting::~IdlyDrifting()																						
{
	// nothing to destroy
}

void IdlyDrifting::Move(float dtime)
{
	D3DXVECTOR2 currentPos = m_pSelf->GetPosition();
	float PreviousX = currentPos.x;
	float PreviousY = currentPos.y;
	currentPos += m_RandomDir*(m_Speed*dtime);

	//if the sprite has reached the bounds of the screen, bounce back
	if ((currentPos.x - (m_pSelf->GetWidth() * 0.5f) < m_Rect.left) || (currentPos.x + (m_pSelf->GetWidth() * 0.5f) > m_Rect.right))
	{
		currentPos.x = PreviousX;
		m_RandomDir.x = -m_RandomDir.x;
	}
	if ((currentPos.y - (m_pSelf->GetHeight() * 0.5f) < m_Rect.top) || (currentPos.y + (m_pSelf->GetHeight() * 0.5f) > m_Rect.bottom))
	{
		currentPos.y = PreviousY;
		m_RandomDir.y = -m_RandomDir.y;
	}

	//m_pSelf->SetRotation(atan2(-m_RandomDir.y,m_RandomDir.x));
	m_pSelf->SetPosition(currentPos);
}





