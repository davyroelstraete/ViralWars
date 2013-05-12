#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Enemy.h"
#include "JustDie.h"
#include "Homing.h"

//-----------------------------------------------------------------
// SlimeSmall Class																
//-----------------------------------------------------------------
class SlimeSmall : public Enemy
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	SlimeSmall(const D3DXVECTOR2& pos, const float& angle, Hero* target);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~SlimeSmall();

	//---------------------------
	// General Methods
	//---------------------------

	

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	static const int HP = 1;
	static const int SPEED = 250;
	static const float TURNINGSPEED;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	SlimeSmall(const SlimeSmall& t);
	SlimeSmall& operator=(const SlimeSmall& t);
};
