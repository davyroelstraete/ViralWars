#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "SpriteEngine.h"

//-----------------------------------------------------------------
// DeathBehaviour Class																
//-----------------------------------------------------------------
class DeathBehaviour
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	DeathBehaviour();
	DeathBehaviour(const D3DXVECTOR2* const pos);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~DeathBehaviour();

	//---------------------------
	// General Methods
	//---------------------------

	virtual void Die();

protected:
	// -------------------------
	// Datamembers
	// -------------------------
	const D3DXVECTOR2* m_Pos;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	DeathBehaviour(const DeathBehaviour& t);
	DeathBehaviour& operator=(const DeathBehaviour& t);
};
