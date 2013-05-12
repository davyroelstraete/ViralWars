//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Hero.h"
#include "FontManager.h"

//-----------------------------------------------------------------
// static inits
//-----------------------------------------------------------------
const float Hero::BULLETCOOLDOWN = 0.1f;
const float Hero::HEROSPEED = 300.0f;

//-----------------------------------------------------------------
// X methods																				
//-----------------------------------------------------------------

Hero::Hero(D3DXVECTOR2 pos) :Entity(), m_isFacingRight(true),
										m_isShooting(false),
										m_isDead(false),
										m_ReticulePos(D3DXVECTOR2(0.0f,0.0f)),
										m_CurrentCooldown(0.0f),
										m_CurrentPoints(0)
{
	m_pReticule = new Entity();
	m_pReticule->Init(_T("Reticule"),D3DXVECTOR2(SPRITE_ENGINE->GetBackBufferWidth() * 0.5f, SPRITE_ENGINE->GetBackBufferHeight() * 0.5f), 0.0f);

	Init(_T("Spaceship"), D3DXVECTOR2(SPRITE_ENGINE->GetBackBufferWidth() * 0.5f, SPRITE_ENGINE->GetBackBufferHeight() * 0.5f), 0.0f);

	m_pBulletList = new BulletList();
}

Hero::~Hero()																						
{
	DestroyObject(m_pReticule);
	DestroyObject(m_pBulletList);
}

BulletList* Hero::GetBulletList()
{
	return m_pBulletList;
}

void Hero::Die()
{
	m_isDead = true;
}
bool Hero::isDead()
{
	return m_isDead;
}
void Hero::AddPoints(const int& points)
{
	m_CurrentPoints += points;
}

void Hero::Respawn()
{
	m_pBulletList->Clear();
	m_isDead = false;
	SetPosition( D3DXVECTOR2(SPRITE_ENGINE->GetBackBufferWidth() * 0.5f, SPRITE_ENGINE->GetBackBufferHeight() * 0.5f));
	m_CurrentPoints = 0;
}

void Hero::Tick(float dTime)
{
	//Handle input
	D3DXVECTOR2 m_Dir = D3DXVECTOR2(0.0f,0.0f);
	if(SPRITE_ENGINE->GetInput()->IsKeyDown(DIK_W))
	{
		m_Dir.y = -1;
	}
	if (SPRITE_ENGINE->GetInput()->IsKeyDown(DIK_S))
	{
		m_Dir.y = 1;
	}
	
	if(SPRITE_ENGINE->GetInput()->IsKeyDown(DIK_A))
	{
		m_Dir.x = -1;
	}
	if(SPRITE_ENGINE->GetInput()->IsKeyDown(DIK_D))
	{
		m_Dir.x = 1;
	}

	//calculate speedvector
	D3DXVec2Normalize(&m_Dir, &m_Dir);
	float m_Angle = atan2(m_Dir.y, m_Dir.x);
	m_Dir*= (HEROSPEED * dTime);

	//Move the hero and backup previousposition
	D3DXVECTOR2 previousPos = GetPosition();
	SetPosition(GetPosition() + m_Dir);
	SetRotation(m_Angle);

	//Check screen boundaries
	if ((GetPosition().x < (0.0f + (GetWidth()/2))) || (GetPosition().x > SPRITE_ENGINE->GetBackBufferWidth() - (GetWidth()/2))) SetPosition(D3DXVECTOR2(previousPos.x, GetPosition().y));
	if ((GetPosition().y < (0.0f + (GetHeight()/2))) || (GetPosition().y > SPRITE_ENGINE->GetBackBufferHeight() - (GetHeight()/2))) SetPosition(D3DXVECTOR2(GetPosition().x, previousPos.y));


	//--------------------------------------
	// Update the reticule
	//--------------------------------------
	m_ReticulePos = SPRITE_ENGINE->GetInput()->GetMouseXY();
	m_pReticule->SetPosition(m_ReticulePos);


	//--------------------------------------
	// Shooting main cannon
	//--------------------------------------
	m_isShooting = SPRITE_ENGINE->GetInput()->MouseButtonDown(0);
	if (m_isShooting)
	{
		if (m_CurrentCooldown >= BULLETCOOLDOWN)
		{
			D3DXVECTOR2 bulletDir = m_ReticulePos - GetPosition();
			float bulletAngle = atan2(bulletDir.y, bulletDir.x);
			m_pBulletList->Add(GetPosition(), bulletAngle);
			m_CurrentCooldown = 0.0f;
		}
	}
	m_CurrentCooldown+= dTime;

	//update the bullets shot by the main cannon
	m_pBulletList->Tick(dTime);
}

void Hero::Draw()
{
	m_pBulletList->Draw();
	Entity::Draw();
	m_pReticule->Draw();

	tstringstream buffer;
	buffer << _T("Score: ") << m_CurrentPoints;
	SPRITE_ENGINE->GetFontManager()->DrawString(_T("Tahoma"),buffer.str(),10,10, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}


