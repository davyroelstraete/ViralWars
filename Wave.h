#pragma once

#include "SpriteEngine.h"
#include "Enemy.h"
#include "EnemyList.h"
#include "Hero.h"

//-----------------------------------------------------------------
// Wave Class																
//-----------------------------------------------------------------
class Wave
{
public:	

	enum WaveType
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		RANDOM_ON_SCREEN,
		RANDOM_ON_SCREEN_EDGE,
		CIRCLE,
		NUMBER_OF_WAVETYPES
	};
			
	//---------------------------
	// Constructor(s)
	//---------------------------
	Wave(Enemy::EnemyType enemyType, const int& NumEnemies, WaveType waveType, const float& spawnrate, Hero* target);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~Wave();

	//---------------------------
	// General Methods
	//---------------------------

	void Tick(float dTime);
	bool IsFinished();

private:
	// -------------------------
	// Datamembers
	// -------------------------
	Hero* m_pTarget;

	RECT m_Screen;

	static const int BORDERWIDTH = 80;

	int m_NumberOfSpawnedEnemies, m_TotalEnemiesToSpawn;
	float m_ElapsedTime, m_TimeBetweenIndividualSpawns;
	WaveType m_WaveType;
	Enemy::EnemyType m_EnemyType;

	bool m_isFinished;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	Wave(const Wave& t);
	Wave& operator=(const Wave& t);
};
