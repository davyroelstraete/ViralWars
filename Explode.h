#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "DeathBehaviour.h"

//-----------------------------------------------------------------
// Explode Class																
//-----------------------------------------------------------------
class Explode : public DeathBehaviour
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	Explode(const D3DXVECTOR2* const pos, const int& radius, const float& growrate, const bool& KillsEnemies);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Explode();

	//---------------------------
	// General Methods
	//---------------------------

	void Die();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	int m_ExplosionRadius;
	float m_GrowRate;
	bool m_KillsEnemies;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Explode(const Explode& t);
	Explode& operator=(const Explode& t);
};
