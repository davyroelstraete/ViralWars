#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "SpriteEngine.h"
#include "DeathBehaviour.h"
#include "MoveBehaviour.h"
#include "Hero.h"
#include "BoundingCircle.h"
#include "Entity.h"
#include "ParticleList.h"

//-----------------------------------------------------------------
// Enemy Class																
//-----------------------------------------------------------------
class Enemy : public Entity
{
public:			
	enum EnemyType
	{
		SLIMEBIG,
		SLIMESMALL,
		COUGHER,
		NUMBER_OF_ENEMYTYPES
	};

	//---------------------------
	// Constructor(s)
	//---------------------------
	Enemy();
	Enemy(const tstring& bitmapName, const D3DXVECTOR2& pos, const float& angle, const int& hp, const int& speed, Hero* target);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Enemy();

	//---------------------------
	// General Methods
	//---------------------------

	void SetMoveBehaviour(MoveBehaviour* move);
	void SetDeathBehaviour(DeathBehaviour* death);
	bool isDead() const;
	void Die();
	void Tick(float dtime);

private:
	// -------------------------
	// Datamembers
	// -------------------------
	

	int m_HP, m_Speed;

	DeathBehaviour* m_pDeathBehaviour;
	MoveBehaviour* m_pMoveBehaviour;

	bool m_isDead;

	Hero* m_pTarget;

protected:

	int m_Score;

	Particle::ParticleType m_DeathParticle;

	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Enemy(const Enemy& t);
	Enemy& operator=(const Enemy& t);
};
