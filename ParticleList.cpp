//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "ParticleList.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

ParticleList* ParticleList::m_pSingleton = NULL;

//-----------------------------------------------------------------
// ParticleList methods																				
//-----------------------------------------------------------------

ParticleList::ParticleList()																						
{
	// nothing to create
}

ParticleList::~ParticleList()																						
{
	// nothing to destroy
} 

ParticleList* ParticleList::GetSingleton()
{
	if (m_pSingleton == NULL)
	{
		m_pSingleton = new ParticleList();
	}

	return m_pSingleton;
}

void ParticleList::AddExplosion(Particle::ParticleType type, const int& numParticles, const D3DXVECTOR2& pos, const float& speed, const int& TTL, const float& gravityInfluence, const float& impactAngle, const float& spread)
{
	for (int count = 0; count < numParticles; ++count)
	{
		float centerAngle; // this angle will be the inverted impactangle
		if (impactAngle > 0)
		{
			centerAngle = impactAngle - D3DX_PI;
		}
		else
		{
			centerAngle = impactAngle + D3DX_PI;
		}
		float ang = centerAngle + DegreeToRad(rand() % (static_cast<int>(1.0 * (spread *0.5f) + 1)) - spread);

		Add(type, pos, ang, (rand() % static_cast<int>(speed *0.25f)) + speed, static_cast<int>((rand() % static_cast<int>(TTL * 0.8f)) + (TTL*0.2f)), gravityInfluence);
	}
}
bool ParticleList::Add(Particle::ParticleType type, const D3DXVECTOR2& pos, const float& angle, const int& speed, const int& ttl, const float& gravityInfluence)
{
	for (vector<Particle*>::iterator it = m_Particles.begin(); it != m_Particles.end(); ++it)
	{
		if ((*it) == NULL)
		{
			(*it) = new Particle(type, pos, angle, speed, ttl, gravityInfluence);
			return true;
		}
	}

	m_Particles.push_back(new Particle(type, pos, angle, speed, ttl, gravityInfluence));
	return true;
}
void ParticleList::Tick(float dTime)
{
	for (vector<Particle*>::iterator it = m_Particles.begin(); it != m_Particles.end(); ++it)
	{
		if ((*it) != NULL)
		{
			if ((*it)->isDead())
			{
				delete (*it);
				(*it) = NULL;
			}
			else
			{
				(*it)->Tick(dTime);
			}
		}
	}
}
void ParticleList::Draw()
{
	for (vector<Particle*>::iterator it = m_Particles.begin(); it != m_Particles.end(); ++it)
	{
		if ((*it) != NULL)
		{
			(*it)->Draw();
		}
	}
}

void ParticleList::Clear()
{
	for (vector<Particle*>::iterator it = m_Particles.begin(); it != m_Particles.end(); ++it)
	{
		delete (*it);
		(*it) = NULL;
	}
}





