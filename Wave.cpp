//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Wave.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Wave methods																				
//-----------------------------------------------------------------

Wave::Wave(Enemy::EnemyType enemyType, const int& NumEnemies, WaveType waveType, const float& spawnrate, Hero* target):m_ElapsedTime(0.0f),
																														m_NumberOfSpawnedEnemies(0),
																														m_TotalEnemiesToSpawn(NumEnemies),
																														m_TimeBetweenIndividualSpawns(spawnrate),
																														m_WaveType(waveType),
																														m_EnemyType(enemyType),
																														m_isFinished(false),
																														m_pTarget(target)
{
	m_Screen.top = static_cast<long>(BORDERWIDTH);
	m_Screen.left = static_cast<long>(BORDERWIDTH);
	m_Screen.right = static_cast<long>(SPRITE_ENGINE->GetBackBufferWidth() - BORDERWIDTH);
	m_Screen.bottom = static_cast<long>(SPRITE_ENGINE->GetBackBufferHeight() - BORDERWIDTH);
}

Wave::~Wave()																						
{
}

void Wave::Tick(float dTime)
{
	if (m_ElapsedTime >= m_TimeBetweenIndividualSpawns && m_NumberOfSpawnedEnemies != m_TotalEnemiesToSpawn)
	{
		////////////////////
		// add next enemy //
		////////////////////


		//Calculate next enemy pos and dir, depending on the type of wave
		D3DXVECTOR2 pos;
		float angle = 0.0f;
		int rnd = 0;
		switch (m_WaveType)
		{
			case TOP_LEFT:
				pos.x = static_cast<float>(m_Screen.left + (rand() % 50));
				pos.y = static_cast<float>(m_Screen.top + (rand() % 50));
				angle = DegreeToRad(GetRandomFloat(0.0f,90.0f));
				break;
			case TOP_RIGHT:
				pos.x = static_cast<float>(m_Screen.right - (rand() % 50));
				pos.y = static_cast<float>(m_Screen.top + (rand() % 50));
				angle = DegreeToRad(GetRandomFloat(90.0f,180.0f));
				break;
			case BOTTOM_LEFT:
				pos.x = static_cast<float>(m_Screen.left + (rand() % 50));
				pos.y = static_cast<float>(m_Screen.bottom - (rand() % 50));
				angle = DegreeToRad(GetRandomFloat(270.0f,359.0f));
				break;
			case BOTTOM_RIGHT:
				pos.x = static_cast<float>(m_Screen.right - (rand() % 50));
				pos.y = static_cast<float>(m_Screen.bottom - (rand() % 50));
				angle = DegreeToRad(GetRandomFloat(180.0f,270.0f));
				break;
			case RANDOM_ON_SCREEN:
				//keep generating a random position on the screen, until you get one that's at least 200 units away from the enemy
				do
				{
					pos.x = static_cast<float>((rand() % (static_cast<int>(m_Screen.right) - BORDERWIDTH)) + BORDERWIDTH);
					pos.y = static_cast<float>((rand() % (static_cast<int>(m_Screen.bottom) - BORDERWIDTH)) + BORDERWIDTH);
				} while ( D3DXVec2Length(&(pos - m_pTarget->GetPosition())) < 200 );
				angle = DegreeToRad(static_cast<float>(rand()*360));
				break;
			case RANDOM_ON_SCREEN_EDGE:
				rnd = rand()%4;
				if (rnd == 0)
				{
					//Top Edge
					pos.y = static_cast<float>(m_Screen.top + (rand() % 50));
					pos.x = static_cast<float>((rand() % (static_cast<int>(m_Screen.right) - BORDERWIDTH)) + BORDERWIDTH);
					angle = DegreeToRad(GetRandomFloat(0.0f,180.0f));
				}
				else if (rnd == 1)
				{
					//Bottom Edge
					pos.y = static_cast<float>(m_Screen.bottom - (rand() % 50));
					pos.x = static_cast<float>((rand() % (static_cast<int>(m_Screen.right) - BORDERWIDTH)) + BORDERWIDTH);
					angle = DegreeToRad(GetRandomFloat(-180.0f,0.0f));
				}
				else if (rnd == 2)
				{
					//Left Edge
					pos.x = static_cast<float>(m_Screen.left + (rand() % 50));
					pos.y = static_cast<float>((rand() % (static_cast<int>(m_Screen.bottom) - BORDERWIDTH)) + BORDERWIDTH);
					angle = DegreeToRad(GetRandomFloat(-90.0f,90.0f));
				}
				else if (rnd == 3)
				{
					//Right Edge
					pos.x = static_cast<float>(m_Screen.right - (rand() % 50));
					pos.y = static_cast<float>((rand() % (static_cast<int>(m_Screen.bottom) - BORDERWIDTH)) + BORDERWIDTH);
					angle = DegreeToRad(GetRandomFloat(90.0f,270.0f));
				}
				break;
			case CIRCLE:
				float spawnangle = (360.0f / m_TotalEnemiesToSpawn) * m_NumberOfSpawnedEnemies;
				pos = D3DXVECTOR2(SPRITE_ENGINE->GetBackBufferWidth() * 0.5f, SPRITE_ENGINE->GetBackBufferHeight() * 0.5f);
				float radius = (SPRITE_ENGINE->GetBackBufferHeight() * 0.5f) - 2 * BORDERWIDTH;
				pos+= D3DXVECTOR2(cos(spawnangle) * radius, sin(spawnangle) * radius);
				angle = -spawnangle;
				break;
		}

		//Create the next enemy, depending on the enemytype
		Enemy* e;
		switch (m_EnemyType)
		{
		case Enemy::SLIMEBIG:
			e = new SlimeBig(pos, angle, m_pTarget);
			break;
		case Enemy::SLIMESMALL:
			e = new SlimeSmall(pos, angle, m_pTarget);
			break;
		case Enemy::COUGHER:
			int rnd = rand()% 8;
			if (rnd == 0)
			{
				e = new Cougher(pos, angle, m_pTarget);
			}
			else
			{
				e = new SlimeBig(pos, angle, m_pTarget);
			}
			break;
		}

		EnemyList::GetSingleton()->Add(e);
		++m_NumberOfSpawnedEnemies;
		m_ElapsedTime = 0.0f;
	}

	m_ElapsedTime+= dTime;

	if (m_NumberOfSpawnedEnemies == m_TotalEnemiesToSpawn)
	{
		m_isFinished = true;
	}
}

bool Wave::IsFinished()
{
	return m_isFinished;
}




