#include "Sprite.h"

#include "TextureManager.h"

Sprite::Sprite():m_pMyTexture(NULL),
                    m_MyPosition(0.0f, 0.0f),
                    m_MyCenter(0.0f, 0.0f),
                    m_MyScale(1.0f,1.0f),
                    m_MyAngle(0.0f),
                    m_MyWidth(0.0f),
                    m_MyHeight(0.0f)
{
}
Sprite::~Sprite()
{
}
bool Sprite::Init(const tstring& filepath)
{
	m_pMyTexture=SPRITE_ENGINE->GetTextureManager()->CreateTexture(filepath);
	if(m_pMyTexture==NULL) return false;

    D3DSURFACE_DESC textureDesc;
    m_pMyTexture->GetLevelDesc(0, &textureDesc);

    m_MyWidth = static_cast<float>(textureDesc.Width);
    m_MyHeight = static_cast<float>(textureDesc.Height);

	return true;
}
void Sprite::Draw()
{
	D3DXMATRIX Scale;
	D3DXMatrixScaling(&Scale,m_MyScale.x,m_MyScale.y, 1.0f);

	D3DXMATRIX Rotation;
	D3DXMatrixRotationYawPitchRoll(&Rotation,0.0f,0.0f,m_MyAngle);

	D3DXMATRIX Translation;
    D3DXMatrixTranslation(&Translation,m_MyPosition.x,m_MyPosition.y, 0.0f);	

	D3DXMATRIX Transform=Scale*Rotation*Translation;

	SPRITE_ENGINE->GetSpriteBatch()->SetTransform(&Transform);
	SPRITE_ENGINE->GetSpriteBatch()->Draw(m_pMyTexture,NULL,&(D3DXVECTOR3(m_MyCenter.x, m_MyCenter.y,0.0f)),NULL,0xFFFFFFFF);
}
void Sprite::DrawByRect(const RECT& rect)
{
	D3DXMATRIX Scale;
	D3DXMatrixScaling(&Scale,m_MyScale.x,m_MyScale.y, 1.0f);

	D3DXMATRIX Rotation;
	D3DXMatrixRotationYawPitchRoll(&Rotation,0.0f,0.0f,m_MyAngle);

	D3DXMATRIX Translation;
	D3DXMatrixTranslation(&Translation,m_MyPosition.x,m_MyPosition.y, 0.0f);	

	D3DXMATRIX Transform=Scale*Rotation*Translation;

	SPRITE_ENGINE->GetSpriteBatch()->SetTransform(&Transform);

	SPRITE_ENGINE->GetSpriteBatch()->Draw(m_pMyTexture,&rect,&(D3DXVECTOR3(m_MyCenter.x, m_MyCenter.y,0.0f)),NULL,0xFFFFFFFF);
}
void Sprite::SetPosition(const D3DXVECTOR2& center, const D3DXVECTOR2& pos)
{
	m_MyPosition.x = pos.x;
	m_MyPosition.y = pos.y;

    m_MyCenter.x = center.x;
    m_MyCenter.y = center.y;
}
void Sprite::SetPosition(const D3DXVECTOR2& pos)
{
	m_MyPosition.x = pos.x;
	m_MyPosition.y = pos.y;
}
void Sprite::SetRotation(const float& angle)
{
	m_MyAngle=angle;
}
void Sprite::SetScale(const D3DXVECTOR2& scale)
{
	m_MyScale.x = scale.x;
	m_MyScale.y = scale.y;
}
const float& Sprite::GetWidth() const
{
    return m_MyWidth;
}
const float& Sprite::GetHeight() const
{
    return m_MyHeight;
}
const D3DXVECTOR2& Sprite::GetPosition() const
{
	return m_MyPosition;
}
const D3DXVECTOR2* const Sprite::GetPositionAdress() const
{
	return &m_MyPosition;
}
const D3DXVECTOR2& Sprite::GetCenter() const
{
	return m_MyCenter;
}
const float& Sprite::GetAngle() const
{
	return m_MyAngle;
}
const D3DXVECTOR2& Sprite::GetScale() const
{
	return m_MyScale;
}