#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "SpriteEngine.h"
#include "Sprite.h"

//-----------------------------------------------------------------
// BoundingCircle Class																
//-----------------------------------------------------------------
class BoundingCircle
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	BoundingCircle();
	BoundingCircle(const D3DXVECTOR2* const pos, const float& radius);

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~BoundingCircle();

	//---------------------------
	// General Methods
	//---------------------------
	BoundingCircle& operator=(const BoundingCircle& t);

	const D3DXVECTOR2* const GetParentPosition() const;
	const float& GetRadius() const;
	bool HitTest(const float& x, const float& y) const; //to be used to check if the mousecursor is inside the bounding circle
	bool CollidesWith(const BoundingCircle* const c) const; //checks if the bounding circle collides/intersects with c;
	void Draw() const;

	void SetRadius(const float& radius);

private:
	// -------------------------
	// Datamembers
	// -------------------------
	
	Sprite* m_pDebugBitmap;
	const D3DXVECTOR2* m_ParentPos;
	float m_Radius;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	BoundingCircle(const BoundingCircle& t);
};
