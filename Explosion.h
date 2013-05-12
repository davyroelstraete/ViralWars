#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Entity.h"

//-----------------------------------------------------------------
// Explosion Class																
//-----------------------------------------------------------------
class Explosion : public Entity
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	Explosion(const D3DXVECTOR2& pos, const float& maxrange, const float& growspeed, const bool& KillsEnemies);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Explosion();

	//---------------------------
	// General Methods
	//---------------------------

	void Tick(float dTime);
	void Die();
	bool IsDead();
	bool KillsEnemies();
	void Respawn(const D3DXVECTOR2& pos, const float& maxrange, const float& growspeed, const bool& KillsEnemies);

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	float m_GrowSpeed, m_MaxRadius, m_CurrentRadius;

	bool m_IsDead, m_KillsEnemies;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Explosion(const Explosion& t);
	Explosion& operator=(const Explosion& t);
};
