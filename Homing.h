#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "MoveBehaviour.h"

//-----------------------------------------------------------------
// Homing Class																
//-----------------------------------------------------------------
class Homing : public MoveBehaviour
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	Homing(Entity* self, Entity* target, const float& turningspeed, const float& movespeed);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Homing();

	//---------------------------
	// General Methods
	//---------------------------

	void Move(float dtime);

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	float m_TurningSpeed, m_MoveSpeed;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Homing(const Homing& t);
	Homing& operator=(const Homing& t);
};
