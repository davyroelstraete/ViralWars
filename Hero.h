#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "SpriteEngine.h"
#include "DirectInput.h"
#include "BulletList.h"
#include "Entity.h"
#include "BoundingCircle.h"

//-----------------------------------------------------------------
// X Class																
//-----------------------------------------------------------------
class Hero : public Entity
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	Hero(D3DXVECTOR2 pos);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Hero();

	//---------------------------
	// General Methods
	//---------------------------

	BulletList* GetBulletList();
	void Tick(float dTime);
	void Draw();
	void Die();
	bool isDead();

	void AddPoints(const int& points);

	void Respawn();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	Entity* m_pReticule;

	static const float HEROSPEED;
	static const float BULLETCOOLDOWN;

	float m_CurrentCooldown;
	D3DXVECTOR2 m_ReticulePos;
	bool m_isFacingRight, m_isShooting, m_isDead;

	int m_CurrentPoints;

	BulletList* m_pBulletList;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Hero(const Hero& t);
	Hero& operator=(const Hero& t);
};
