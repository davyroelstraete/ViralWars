/*
This class doesnt hold the actual lpD3DSprite, but holds the texture and screen coordinates
so that the engine can draw all sprites at once using a lpD3Dsprite interface.
*/

#pragma once

#include "Sprite.h"
#include "SpriteEngine.h"
#include "TextureManager.h"
#include "BoundingCircle.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	bool Init(const tstring& filepath, const D3DXVECTOR2& pos, const float& angle);

	void Draw();
	void DrawByRect(const RECT& rect);

	bool CollidesWith(const BoundingCircle * const bc);

	void SetScale(const D3DXVECTOR2& scale);
	void SetScale(const float& scale);
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
	const BoundingCircle *const GetBC() const;

protected:
	Sprite* m_pSprite;
	BoundingCircle* m_BC;

	Entity(const Entity& t);
	Entity& operator=(const Entity& t);
};