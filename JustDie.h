#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "DeathBehaviour.h"

//-----------------------------------------------------------------
// JustDie Class																
//-----------------------------------------------------------------
class JustDie : public DeathBehaviour
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	JustDie(const D3DXVECTOR2* const pos);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~JustDie();

	//---------------------------
	// General Methods
	//---------------------------
	
	void Die();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	JustDie(const JustDie& t);
	JustDie& operator=(const JustDie& t);
};
