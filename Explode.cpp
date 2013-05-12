//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Explode.h"
#include "EnemyList.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Explode methods																				
//-----------------------------------------------------------------

Explode::Explode(const D3DXVECTOR2* const pos, const int& radius, const float& growrate, const bool& KillsEnemies):DeathBehaviour(pos), 
																													m_KillsEnemies(KillsEnemies), 
																													m_GrowRate(growrate)																						
{
	m_ExplosionRadius = radius;
}

Explode::~Explode()																						
{
	// nothing to destroy
}

void Explode::Die()
{
	EnemyList::GetSingleton()->AddExplosion(*m_Pos, m_ExplosionRadius, m_GrowRate, m_KillsEnemies); 
}





