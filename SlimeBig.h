#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Enemy.h"
#include "Hero.h"
#include "IdlyDrifting.h"
#include "SpawnAdds.h"

//-----------------------------------------------------------------
// SlimeBig Class																
//-----------------------------------------------------------------
class SlimeBig : public Enemy
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	SlimeBig(const D3DXVECTOR2& pos, const float& angle, Hero* target);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~SlimeBig();

	//---------------------------
	// General Methods
	//---------------------------

	

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	static const int HP = 1;
	static const int SPEED = 50;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	SlimeBig(const SlimeBig& t);
	SlimeBig& operator=(const SlimeBig& t);
};
