//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "DeathBehaviour.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// DeathBehaviour methods																				
//-----------------------------------------------------------------

DeathBehaviour::DeathBehaviour()																						
{
	// nothing to create
}
DeathBehaviour::DeathBehaviour(const D3DXVECTOR2* const pos)																						
{
	m_Pos = pos;
}

DeathBehaviour::~DeathBehaviour()																						
{
	// nothing to destroy
}

void DeathBehaviour::Die()
{

}



