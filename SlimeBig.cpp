//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SlimeBig.h"																			

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// SlimeBig methods																				
//-----------------------------------------------------------------

SlimeBig::SlimeBig(const D3DXVECTOR2& pos, const float& angle, Hero* target) :Enemy(_T("SlimeBig"),pos,angle, HP, SPEED, target)																						
{
	SetDeathBehaviour(new SpawnAdds(GetPositionAdress(), SpawnAdds::SLIMESMALL, 3, _T("enemy")));
	SetMoveBehaviour(new IdlyDrifting(this, target, SPEED));

	m_Score = 50;
}

SlimeBig::~SlimeBig()																						
{
	// nothing to destroy
}






