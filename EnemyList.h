#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Hero.h"
#include "Enemy.h"
#include "SlimeBig.h"
#include "SlimeSmall.h"
#include "Cougher.h"
#include "Explosion.h"

class Wave;

//-----------------------------------------------------------------
// X Class																
//-----------------------------------------------------------------
struct SpawnedAddData
{
	int type;
	D3DXVECTOR2 pos;
};

class EnemyList : public AbstractManager
{
public:

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~EnemyList();

	//---------------------------
	// General Methods
	//---------------------------
	static EnemyList* GetSingleton();

	void Init(Hero* target);
	void NewWave();
	void AddExplosion(const D3DXVECTOR2& pos, const float& maxrange, const float& growspeed, const bool& KillsEnemies);
	bool Add(Enemy* e);
	bool SpawnAdd(const D3DXVECTOR2& pos, const int& type);

	int GetNumberOfLivingEnemies();

	void Tick(float dTime);
	void Draw();

	void Clear();

private:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	EnemyList();

	// -------------------------
	// Datamembers
	// -------------------------
	static EnemyList* m_pSingleton;

	vector<Explosion*> m_Explosions;
	vector<Enemy*> m_Enemies;
	vector<Wave*> m_ActiveWaves;
	vector<SpawnedAddData> m_ToBeAdded; //this vector will be used to store spawned adds, until they are created and added to m_Enemies
	Hero* m_pTarget;

	float m_ElapsedTime;
	int m_TimeBetweenWaves;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	EnemyList(const EnemyList& t);
	EnemyList& operator=(const EnemyList& t);
};
