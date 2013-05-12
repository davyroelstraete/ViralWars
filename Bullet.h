#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Entity.h"
#include "SpriteEngine.h"

//-----------------------------------------------------------------
// X Class																
//-----------------------------------------------------------------
class Bullet : public Entity
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	Bullet(const D3DXVECTOR2& pos, const float& angle);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Bullet();

	//---------------------------
	// General Methods
	//---------------------------

	void ReInit(const D3DXVECTOR2& pos, const float& angle);
	void Tick(float dtime);
	bool isDead();
	void Die();  //should we ever need special bullets, we can have them implement a death behaviour, such as exploding or spawning adds (frag grenade)

private:
	// -------------------------
	// Datamembers
	// -------------------------
	

	static const int BULLETWIDTH = 8;
	static const int BULLETHEIGHT = 8;
	static const int BULLETSPEED = 450;

	bool m_isDead;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Bullet(const Bullet& t);
	Bullet& operator=(const Bullet& t);
};
