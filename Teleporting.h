#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "MoveBehaviour.h"

//-----------------------------------------------------------------
// Teleporting Class																
//-----------------------------------------------------------------
class Teleporting : public MoveBehaviour
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	Teleporting(Entity* self, Entity* target);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Teleporting();

	//---------------------------
	// General Methods
	//---------------------------

	virtual void Move();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Teleporting(const Teleporting& t);
	Teleporting& operator=(const Teleporting& t);
};
