#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Particle.h"

//-----------------------------------------------------------------
// ParticleList Class																
//-----------------------------------------------------------------
class ParticleList
{
public:

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~ParticleList();

	//---------------------------
	// General Methods
	//---------------------------

	static ParticleList* GetSingleton();

	void AddExplosion(Particle::ParticleType type, const int& numParticles, const D3DXVECTOR2& pos, const float& speed, const int& TTL, const float& gravityInfluence, const float& impactAngle, const float& spread);
	bool Add(Particle::ParticleType type, const D3DXVECTOR2& pos, const float& angle, const int& speed, const int& ttl, const float& gravityInfluence);
	void Tick(float dTime);
	void Draw();
	void Clear();
	
private:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	ParticleList();

	// -------------------------
	// Datamembers
	// -------------------------
	static ParticleList* m_pSingleton;

	vector<Particle*> m_Particles;

	//tstring debugstring;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	ParticleList(const ParticleList& t);
	ParticleList& operator=(const ParticleList& t);
};
