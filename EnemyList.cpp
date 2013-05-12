//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "EnemyList.h"
#include "Wave.h"
#include "FontManager.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

EnemyList* EnemyList::m_pSingleton = NULL;

//-----------------------------------------------------------------
// EnemyList methods																				
//-----------------------------------------------------------------

EnemyList* EnemyList::GetSingleton()
{
	if (m_pSingleton == NULL) m_pSingleton = new EnemyList();
	return m_pSingleton;
}

EnemyList::EnemyList():m_pTarget(NULL),
	m_ElapsedTime(0.0f),
	m_TimeBetweenWaves(5)																				
{
}

EnemyList::~EnemyList()																					
{
	// nothing to destroy
}

void EnemyList::Init(Hero* target)
{
	m_pTarget = target;
}

void EnemyList::NewWave()
{
	bool bAdded = false;
	for (vector<Wave*>::iterator it = m_ActiveWaves.begin();it != m_ActiveWaves.end(); ++it)
	{
		if ((*it) == NULL)
		{
			(*it) = new Wave(Enemy::COUGHER,
							9, static_cast<Wave::WaveType>(rand()% static_cast<int>(Wave::NUMBER_OF_WAVETYPES)), 
							0.1f, m_pTarget);
			bAdded = true;
		}
	}
	if (!bAdded)
	{
		Wave* wave = new Wave(Enemy::COUGHER,
								9, static_cast<Wave::WaveType>(rand()% static_cast<int>(Wave::NUMBER_OF_WAVETYPES)), 
								0.1f, m_pTarget);
		m_ActiveWaves.push_back(wave);
	}
}

bool EnemyList::Add(Enemy* e)
{
	for (vector<Enemy*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); ++it)
	{
		if ((*it) == NULL)
		{
			*it = e;
			return true;
		}
	}
	m_Enemies.push_back(e);
	return true;
}

bool EnemyList::SpawnAdd(const D3DXVECTOR2& pos, const int& type)
{
	//this function is called from inside a running loop through the enemies. 
	//If we add an enemy to the vector, the loop will become invalid.
	//So we'll add the data needed to create the add to a new vector, and after the loop has finished, we'll create and add them to m_Enemies.
	SpawnedAddData add;
	add.pos = pos;
	add.type = type;
	m_ToBeAdded.push_back(add);
	return true;
}

void EnemyList::AddExplosion(const D3DXVECTOR2& pos, const float& maxrange, const float& growspeed, const bool& KillsEnemies)
{
	bool bAdded = false;
	for (vector<Explosion*>::iterator it = m_Explosions.begin(); it!=m_Explosions.end(); ++it)
	{
		if ((*it)->IsDead())
		{
			(*it)->Respawn(pos, maxrange, growspeed, KillsEnemies);
			bAdded = true;
		}
	}
	if (!bAdded)
	{
		Explosion* e = new Explosion(pos, maxrange, growspeed, KillsEnemies);
		m_Explosions.push_back(e);
	}
}

void EnemyList::Tick(float dTime)
{
	////////////////////////////////////////////
	//  EXPLOSIONS                            //
	////////////////////////////////////////////

	//Tick the explosions, and kill off anything in the range
	for (vector<Explosion*>::iterator ExplIt = m_Explosions.begin(); ExplIt!=m_Explosions.end(); ++ExplIt)
	{
		//grow the explosions
		if (!((*ExplIt)->IsDead()))
		{
			//does the explosion collide with the hero?
			if (m_pTarget->GetBC()->CollidesWith((*ExplIt)->GetBC()))
			{
				m_pTarget->Die();
			}

			//if this is an explosion that kills enemies, check which enemies must die
			/*
			When enabled, this still bugs out when the explosion kills another koffoom...
			However, right now, the explosion kills all the enemies around, including
			the little slimes spawned by the explosion. This makes the game too easy
			until I add a new datamember to the enemy class that knows which explosion
			triggered it, and make it immune to that explosion. Leave this disabled
			for now...
			*/
			if ((*ExplIt)->KillsEnemies())
			{
				vector<Enemy*>::iterator EnIt = m_Enemies.begin();
				for (EnIt; EnIt!=m_Enemies.end(); ++EnIt)
				{
					if ((*EnIt) != NULL && !(*EnIt)->isDead())
					{
						if((*ExplIt)->GetBC()->CollidesWith((*EnIt)->GetBC()))
						{
							(*EnIt)->Die();
						}
					}
				}
			}
		
			(*ExplIt)->Tick(dTime);
		}
	}

	
	////////////////////////////////////////////
	//  WAVES                                 //
	////////////////////////////////////////////

	//Add a new wave if enough time has passed
	if (m_ElapsedTime >= m_TimeBetweenWaves)
	{
		NewWave();
		m_ElapsedTime = 0.0f;
	}

	//Tick the existing waves to add new enemies, and delete finished waves
	for (vector<Wave*>::iterator it = m_ActiveWaves.begin(); it != m_ActiveWaves.end(); ++it)
	{
		if ((*it) != NULL)
		{
			if ((*it)->IsFinished())
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

	
	////////////////////////////////////////////
	//  ENEMIES                               //
	////////////////////////////////////////////


	//Tick the existing enemies
	for (vector<Enemy*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); ++it)
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

	if (m_ToBeAdded.size() > 0)
	{
		//While cycling through the enemies, we've killed off an enemy that spawns adds, so we'll create and add these now
		for (vector<SpawnedAddData>::iterator it = m_ToBeAdded.begin(); it != m_ToBeAdded.end(); ++it)
		{
			switch((*it).type)
			{

			case SpawnAdds::SLIMESMALL:
				Add(new SlimeSmall((*it).pos, static_cast<float>(rand() % 360), m_pTarget));
				break;
			}
		}

		//we'll make the data vector empty now, so he's ready for the next cycle
		m_ToBeAdded.clear();
	}

	m_ElapsedTime+= dTime;
}

void EnemyList::Draw()
{
	for (vector<Enemy*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); ++it)
	{
		if ((*it) != NULL)
		{
			(*it)->Draw();
		}
	}

	for (vector<Explosion*>::iterator it = m_Explosions.begin(); it != m_Explosions.end(); ++it)
	{
		if (!((*it)->IsDead()))
		{
			(*it)->Draw();
		}
	}
}

void EnemyList::Clear()
{
	for (vector<Enemy*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); ++it)
	{
		delete (*it);
		(*it) = NULL;
	}
	for (vector<Wave*>::iterator it = m_ActiveWaves.begin(); it != m_ActiveWaves.end(); ++it)
	{
		delete (*it);
		(*it) = NULL;
	}
	for (vector<Explosion*>::iterator it = m_Explosions.begin(); it != m_Explosions.end(); ++it)
	{
		(*it)->Die();
	}
	m_ToBeAdded.clear();
}

int EnemyList::GetNumberOfLivingEnemies()
{
	int count = 0;
	for (vector<Enemy*>::iterator it = m_Enemies.begin(); it != m_Enemies.end(); ++it)
	{
		if (((*it) != NULL) && (!((*it)->isDead()))) ++count;
	}
	return count;
}





