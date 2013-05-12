/*
GameEngine
*/

#ifndef SPRITEENGINE_H_INCLUDED
#define SPRITEENGINE_H_INCLUDED

#include "D3dApp.h"

class Camera;
class Sprite;
class SkinnedMesh;
class DirectInput;
class D3dGfxStats;
class FontManager;
class ScreenManager;
class TextureManager;

/*
All objects that can be made are added here so u'll only need to include in the .cpp for functionality. Keeps the .h kinda clean...
*/


/*
Guess u kinda understand singleton, this defines SPRITE_ENGINE as calling SpriteEngine::GetSingleton()
*/
#define SPRITE_ENGINE (SpriteEngine::GetSingleton())

class SpriteEngine:public D3dApp
{
public:
	SpriteEngine(HINSTANCE hInstance,const tstring& winCaption, D3DDEVTYPE devType, DWORD requestedVp);
	virtual ~SpriteEngine();

	bool CheckDeviceCaps();
	void OnLostDevice();
	void OnResetDevice();

	bool InitEngine();

	void UpdateScene(float dtime);
	void HandleInput();
	void DrawScene();

	void ShutDownEngine();

	bool IsWindowed() const;
	void EnableCursor(bool visible);

	Camera* GetCamera() const;
	DirectInput* GetInput() const;
	FontManager* GetFontManager() const;
	ScreenManager* GetScreenManager() const;
	TextureManager* GetTextureManager() const;

    LPD3DXSPRITE GetSpriteBatch() const;

	static SpriteEngine* GetSingleton();

private:
	static SpriteEngine* m_pMySingleton;

    LPD3DXSPRITE m_pMySpriteBatch;

	bool m_IsRunning;
	bool m_IsDeviceLost;
	bool m_IsShowingCursor;

	Camera* m_pMyCamera;
	DirectInput* m_pMyDxInput;
	D3dGfxStats* m_pMyGfxStats;
	FontManager* m_pMyFontManager;
	ScreenManager* m_pMyScreenManager;
	TextureManager* m_pMyTextureManager;

	SpriteEngine(const SpriteEngine& t);
	SpriteEngine& operator=(const SpriteEngine& t);
};
#endif