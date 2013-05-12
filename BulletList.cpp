//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "BulletList.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// BulletList methods																				
//-----------------------------------------------------------------

BulletList::BulletList()																						
{
	// nothing to create
}

BulletList::~BulletList()																						
{
	for (BLi it = m_Bulletlist.begin(); it != m_Bulletlist.end(); ++it)
	{
		delete (*it);
	}
}

int BulletList::CollidesWith(const BoundingCircle* const bc)
{
	int NumCollisions = 0;

	for (BLi it = m_Bulletlist.begin(); it != m_Bulletlist.end(); ++it)
	{
		if (!((*it)->isDead()))
		{
			if ((*it)->CollidesWith(bc))
			{
				D3DXVECTOR2 impactDir = (*(bc->GetParentPosition())) - (*it)->GetPosition();
				float impactAngle = atan2(impactDir.y, impactDir.x);
				ParticleList::GetSingleton()->AddExplosion(Particle::BULLET, rand()%3 + 5, (*it)->GetPosition(), 300.0f, 75, 0.05f, impactAngle, 60);
				(*it)->Die();
				++NumCollisions;
			}
		}
	}

	return NumCollisions;
}

bool BulletList::Add(const D3DXVECTOR2& pos, const float& angle)
{
	for (BLi it = m_Bulletlist.begin(); it != m_Bulletlist.end(); ++it)
	{
		if ((*it)->isDead())
		{
			(*it)->ReInit(pos, angle);
			return true;
		}
	}
	Bullet* NewBullet = new Bullet(pos, angle);
	m_Bulletlist.push_back(NewBullet);
	return true;
}

void BulletList::Tick(float dtime)
{
	for (BLi it = m_Bulletlist.begin(); it != m_Bulletlist.end(); ++it)
	{
		if (!((*it)->isDead()))
		{
			(*it)->Tick(dtime);
		}
	}
}

void BulletList::Draw()
{
	for (BLi it = m_Bulletlist.begin(); it != m_Bulletlist.end(); ++it)
	{
		if (!((*it)->isDead())) (*it)->Draw();
	}
}

int BulletList::GetSize()
{
	return m_Bulletlist.size();
}

void BulletList::Clear()
{
	for (BLi it = m_Bulletlist.begin(); it != m_Bulletlist.end(); ++it)
	{
		(*it)->Die();
	}
}


