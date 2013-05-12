#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Entity.h"

//-----------------------------------------------------------------
// MoveBehaviour Class																
//-----------------------------------------------------------------
class MoveBehaviour
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	MoveBehaviour();
	MoveBehaviour(Entity* self, Entity* target);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~MoveBehaviour();

	//---------------------------
	// General Methods
	//---------------------------

	virtual void Move(float dtime) = 0;  //pure virtual function - you cannot call the function from the baseclass!

protected:
	// -------------------------
	// Datamembers
	// -------------------------
	Entity* m_pSelf;
	Entity* m_pTarget;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	MoveBehaviour(const MoveBehaviour& t);
	MoveBehaviour& operator=(const MoveBehaviour& t);
};
