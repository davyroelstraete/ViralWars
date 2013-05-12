//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "BoundingCircle.h"		
#include "Entity.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// BoundingCircle methods																				
//-----------------------------------------------------------------
BoundingCircle::BoundingCircle()																						
{
	m_ParentPos = NULL;
	m_Radius = 0;
	m_pDebugBitmap = new Sprite();
	m_pDebugBitmap= NULL;
}
BoundingCircle::BoundingCircle(const D3DXVECTOR2* const pos, const float& radius)																						
{
	m_ParentPos = pos;
	m_Radius = radius;
	m_pDebugBitmap = new Sprite();
	m_pDebugBitmap->SetRotation(0.0f);
}

BoundingCircle::~BoundingCircle()																						
{
	DestroyObject(m_pDebugBitmap);
}

BoundingCircle& BoundingCircle::operator=(const BoundingCircle& t)
{
	this->m_ParentPos = t.GetParentPosition();
	this->m_Radius = t.GetRadius();
	return (*this);
}

const D3DXVECTOR2* const BoundingCircle::GetParentPosition() const
{
	return m_ParentPos;
}
const float& BoundingCircle::GetRadius() const
{
	return m_Radius;
}
bool BoundingCircle::HitTest(const float& x, const float& y) const
{
	//if the distance between the click and the center of the circle is less than the radius, you've clicked inside the circle
	double distance = D3DXVec2Length(&((*m_ParentPos) - (D3DXVECTOR2(x,y))));
	return (distance < m_Radius);
}
bool BoundingCircle::CollidesWith(const BoundingCircle* const c) const
{
	//if the distance between the two centers is less than the sum of the radii, than the circles are colliding
	double distance = D3DXVec2Length(&((*m_ParentPos) - (*(c->GetParentPosition()))));
	return (distance < (m_Radius + c->GetRadius()));
}
void BoundingCircle::SetRadius(const float& radius)
{
	m_Radius = radius;
}
void BoundingCircle::Draw() const
{
	m_pDebugBitmap->SetPosition(D3DXVECTOR2(m_pDebugBitmap->GetWidth() * 0.5f, m_pDebugBitmap->GetHeight() * 0.5f), *m_ParentPos);
	m_pDebugBitmap->SetScale(D3DXVECTOR2(m_Radius / m_pDebugBitmap->GetWidth(), m_Radius / m_pDebugBitmap->GetWidth()));
	m_pDebugBitmap->Draw();
}





