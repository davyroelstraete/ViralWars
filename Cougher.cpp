//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Cougher.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
const float Cougher::TURNINGSPEED = 0.05f;
//-----------------------------------------------------------------
// Cougher methods																				
//-----------------------------------------------------------------

Cougher::Cougher(const D3DXVECTOR2& pos, const float& angle, Hero* target) :Enemy(_T("Koffoom"),pos,angle, HP, SPEED, target)
{
	SetDeathBehaviour(new Explode(GetPositionAdress(), 400, 0.03f, false));
	SetMoveBehaviour(new Homing(this, target, TURNINGSPEED, static_cast<float>(SPEED)));

	m_Score = 500;
	m_DeathParticle = Particle::SMOKE;
}

Cougher::~Cougher()																						
{
	// nothing to destroy
}

