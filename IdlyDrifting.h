#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "MoveBehaviour.h"
#include "Entity.h"

//-----------------------------------------------------------------
// IdlyDrifting Class																
//-----------------------------------------------------------------
class IdlyDrifting : public MoveBehaviour
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	IdlyDrifting(Entity* self, Entity* target, const int& speed);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~IdlyDrifting();

	//---------------------------
	// General Methods
	//---------------------------

	virtual void Move(float dtime);

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	D3DXVECTOR2 m_RandomDir;

	RECT m_Rect;

	int m_Speed;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	IdlyDrifting(const IdlyDrifting& t);
	IdlyDrifting& operator=(const IdlyDrifting& t);
};
