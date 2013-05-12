/*
This class doesnt hold the actual lpD3DSprite, but holds the texture and screen coordinates
so that the engine can draw all sprites at once using a lpD3Dsprite interface.
*/

#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "SpriteEngine.h"

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	bool Init(const tstring& filepath);

	void Draw();
	void DrawByRect(const RECT& rect);

	void SetScale(const D3DXVECTOR2& scale);
	void SetPosition(const D3DXVECTOR2& center, const D3DXVECTOR2& pos);
	void SetPosition(const D3DXVECTOR2& pos);
	void SetRotation(const float& angle);

    const float& GetWidth() const;
    const float& GetHeight() const;
	
	const D3DXVECTOR2& GetPosition() const;
	const D3DXVECTOR2* const GetPositionAdress() const;
	const D3DXVECTOR2& GetCenter() const;
	const float& GetAngle() const;
	const D3DXVECTOR2& GetScale() const;

private:
	LPDIRECT3DTEXTURE9 m_pMyTexture;

	D3DXVECTOR2 m_MyPosition;
	D3DXVECTOR2 m_MyCenter;
	D3DXVECTOR2 m_MyScale;

    float m_MyAngle;

    float m_MyWidth;
    float m_MyHeight;

	Sprite(const Sprite& t);
	Sprite& operator=(const Sprite& t);
};
#endif