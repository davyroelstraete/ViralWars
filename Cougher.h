#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Enemy.h"
#include "Hero.h"
#include "Explode.h"
#include "Homing.h"

//-----------------------------------------------------------------
// Cougher Class																
//-----------------------------------------------------------------
class Cougher : public Enemy
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	Cougher(const D3DXVECTOR2& pos, const float& angle, Hero* target);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Cougher();

	//---------------------------
	// General Methods
	//---------------------------


private:
	// -------------------------
	// Datamembers
	// -------------------------

	static const int HP = 3;
	static const int SPEED = 150;
	static const float TURNINGSPEED;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Cougher(const Cougher& t);
	Cougher& operator=(const Cougher& t);
};
