//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "MoveBehaviour.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// MoveBehaviour methods																				
//-----------------------------------------------------------------
MoveBehaviour::MoveBehaviour()
{
}
MoveBehaviour::MoveBehaviour(Entity* self, Entity* target)																						
{
	m_pSelf = self;
	m_pTarget = target;
}

MoveBehaviour::~MoveBehaviour()																						
{
	// nothing to destroy
}





