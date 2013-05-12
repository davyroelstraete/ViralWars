#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "SpriteEngine.h"
#include "Entity.h"


//-----------------------------------------------------------------
// Particle Class																
//-----------------------------------------------------------------
class Particle
{
public:	
	
	static enum ParticleType
	{
		BULLET,
		SLIME,
		SMOKE
	};

	//---------------------------
	// Constructor(s)
	//---------------------------
	Particle();
	Particle(ParticleType type, const D3DXVECTOR2& pos, const float& angle, const int& speed, const int& ttl, const float& gravityInfluence);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Particle();

	//---------------------------
	// General Methods
	//---------------------------

	bool isDead();
	void Tick(float dTime);
	void Draw();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	Entity* m_pBitmap;

	D3DXVECTOR2 m_Pos;
	float m_Angle, m_GravityInfluence;
	int m_Speed, m_TTL, m_CurrentLifetime;

	ParticleType m_Type;

	bool m_IsDead;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Particle(const Particle& t);
	Particle& operator=(const Particle& t);
};
