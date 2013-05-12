//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Teleporting.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Teleporting methods																				
//-----------------------------------------------------------------

Teleporting::Teleporting(Entity* self, Entity* target):MoveBehaviour(self,target)																						
{
	// nothing to create
}

Teleporting::~Teleporting()																						
{
	// nothing to destroy
}

void Teleporting::Move()
{
}