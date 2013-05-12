#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Bullet.h"
#include "ParticleList.h"
#include "BoundingCircle.h"

//-----------------------------------------------------------------
// BulletList Class																
//-----------------------------------------------------------------
class BulletList
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	BulletList();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~BulletList();

	//---------------------------
	// General Methods
	//---------------------------

	bool Add(const D3DXVECTOR2& pos, const float& angle);
	int CollidesWith(const BoundingCircle* const bc); // returns the number of bullets colliding with the bounding circle
	void Tick(float dtime);
	void Draw();
	int GetSize();
	void Clear();

private:
	

	// -------------------------
	// Datamembers
	// -------------------------

	typedef vector<Bullet*> BL;
	typedef vector<Bullet*>::iterator BLi;

	BL m_Bulletlist;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	BulletList(const BulletList& t);
	BulletList& operator=(const BulletList& t);
};
