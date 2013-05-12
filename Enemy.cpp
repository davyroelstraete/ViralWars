//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Enemy.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Enemy methods																				
//-----------------------------------------------------------------

Enemy::Enemy(const tstring& bitmapName, const D3DXVECTOR2& pos, const float& angle, const int& hp, const int& speed, Hero* target)	:Entity(),
																																	m_HP(hp),
																																	m_Speed(speed),
																																	m_pDeathBehaviour(NULL),
																																	m_pMoveBehaviour(NULL),
																																	m_pTarget(target),
																																	m_isDead(false),
																																	m_DeathParticle(Particle::SLIME),
																																	m_Score(0)
{
	Init(bitmapName, pos, angle);
}

Enemy::~Enemy()																						
{
	DestroyObject(m_pDeathBehaviour);
	DestroyObject(m_pMoveBehaviour);
}

void Enemy::SetDeathBehaviour(DeathBehaviour* death)
{
	//destroying the existing behaviour to avoid memory leaks
	DestroyObject(m_pDeathBehaviour);
	m_pDeathBehaviour = death;
}
void Enemy::SetMoveBehaviour(MoveBehaviour* move)
{
	//destroying the existing behaviour to avoid memory leaks
	DestroyObject(m_pMoveBehaviour);
	m_pMoveBehaviour = move;
}

bool Enemy::isDead() const
{
	return m_isDead;
}
void Enemy::Die()
{
	if(!m_isDead)
	{
		m_pDeathBehaviour->Die();
		ParticleList::GetSingleton()->AddExplosion(m_DeathParticle, rand()%6 + 5, GetPosition(), 300.0f, 50, 0.1f, 0.0f, 360.0f); 
		m_pTarget->AddPoints(m_Score);
		m_isDead = true;
	}
}
void Enemy::Tick(float dtime)
{
	m_pMoveBehaviour->Move(dtime);

	//check for Hero collision
	if (CollidesWith( m_pTarget->GetBC()))
	{
		m_pTarget->Die();
	}

	//check for bulletcollisions
	BulletList* bullets = m_pTarget->GetBulletList();
	m_HP -= (bullets->CollidesWith(m_BC));
	if (m_HP <= 0)
	{
		Die();
	}
}





