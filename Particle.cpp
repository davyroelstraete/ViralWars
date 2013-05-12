//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Particle.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Particle methods																				
//-----------------------------------------------------------------

Particle::Particle()																					
{
	// nothing to create
}

Particle::Particle(ParticleType type, const D3DXVECTOR2& pos, const float& angle, const int& speed, const int& ttl, const float& gravityInfluence)
{
	m_Type = type;
	switch (m_Type)
	{
	case BULLET:
		m_pBitmap = new Entity();
		m_pBitmap->Init(_T("BulletParticle"), pos, angle);
		break;
	case SLIME:
		m_pBitmap = new Entity();
		m_pBitmap->Init(_T("SlimeParticle"), pos, angle);
		break;
	case SMOKE:
		m_pBitmap = new Entity();
		m_pBitmap->Init(_T("SmokeParticle"), pos, angle);
		break;
	}
	m_Pos = pos;
	m_Angle = angle;
	m_Speed = speed;
	m_TTL = ttl;
	m_CurrentLifetime = 0;
	m_GravityInfluence = gravityInfluence;
	m_IsDead = false;
}

Particle::~Particle()																						
{
	DestroyObject(m_pBitmap);
}

void Particle::Tick(float dTime)
{
	D3DXVECTOR2 gravity = D3DXVECTOR2(0, 1.0f * m_CurrentLifetime * m_GravityInfluence);
	D3DXVECTOR2 m_Dir = D3DXVECTOR2(cos(m_Angle), sin(m_Angle));
	m_Dir *= static_cast<float>(m_Speed) * dTime;
	m_Dir += gravity;
	D3DXVec2Normalize(&m_Dir,&m_Dir);

	m_Pos += m_Dir* static_cast<float>(m_Speed) * dTime;

	m_pBitmap->SetPosition(m_Pos);
	m_pBitmap->SetRotation(m_Angle);


	if (m_CurrentLifetime >= m_TTL) m_IsDead = true;

	m_CurrentLifetime++;
}

void Particle::Draw()
{
	m_pBitmap->Draw();
}

bool Particle::isDead()
{
	return m_IsDead;
}




