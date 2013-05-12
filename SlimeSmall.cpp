//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SlimeSmall.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

const float SlimeSmall::TURNINGSPEED = 0.05f;

//-----------------------------------------------------------------
// SlimeSmall methods																				
//-----------------------------------------------------------------

SlimeSmall::SlimeSmall(const D3DXVECTOR2& pos, const float& angle, Hero* tgt) :Enemy(_T("SlimeSmall"),pos,angle, HP, SPEED, tgt)
{
	// nothing to create
	SetMoveBehaviour(new Homing(this, tgt, static_cast<float>(TURNINGSPEED), static_cast<float>(SPEED)));
	SetDeathBehaviour(new JustDie(GetPositionAdress()));

	m_Score = 100;
}

SlimeSmall::~SlimeSmall()																						
{
	// nothing to destroy
}







