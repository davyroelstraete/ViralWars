#include "GameScreen.h"

#include "DirectInput.h"
#include "FontManager.h"

GameScreen::GameScreen(): m_pHero(NULL)
{
}
GameScreen::~GameScreen()
{
    DestroyObject(m_pHero);
}
bool GameScreen::Initialize()
{
	SPRITE_ENGINE->EnableCursor(false);
    /*
    Initialize the Sprite, use global TextureDir. This corresponds to "Content\Texture\" Follow only by using the name of the file and it's extension
    Textures used should be placed in the corresponding folder in the project folder (Not in the debug or release folder since it is auto copied)
    */
    m_pHero = new Hero(D3DXVECTOR2(SPRITE_ENGINE->GetBackBufferWidth() * 0.5f, SPRITE_ENGINE->GetBackBufferHeight() * 0.5f));

	EnemyList::GetSingleton()->Init(m_pHero);
	EnemyList::GetSingleton()->NewWave();
    /*
    Important functionality! Setposition places THE CENTERPOINT chosen on the image to the position desired. For instance if u want to place the center of the image
    to the center of the screen. Use sprite->GetWidth / 2 and GetHeight / 2 for center and use same as below for screen center.

    Important Note: Directx9 works with textures of 2^n. Eagle.dds is normally 384 * 384 but if u check the return value from GetWidth(), it returns 512. Non power of 2
    texture will be scaled to the closest upper power of 2!!! Mind this when checking for positions!!
    */

	return true;
}
void GameScreen::UpdateScene(float dtime)
{
    if(SPRITE_ENGINE->GetInput()->IsKeyPressed(DIK_ESCAPE)) SPRITE_ENGINE->ShutDownEngine();

	if (!(m_pHero->isDead()))
	{
		m_pHero->Tick(dtime);
		EnemyList::GetSingleton()->Tick(dtime);
		ParticleList::GetSingleton()->Tick(dtime);
	}
	else
	{
		if (SPRITE_ENGINE->GetInput()->MouseButtonPressed(1))
		{
			m_pHero->Respawn();
			ParticleList::GetSingleton()->Clear();
			EnemyList::GetSingleton()->Clear();
		}
	}
}
void GameScreen::DrawScene()
{
    /*
    You can simply draw sprites at full, but you can also draw parts by using drawByRect. Since the eagle contains a space of 128*128 I create such a rectangle. Furthermore
    I move this rectangle towards the other ones with the animationcounter
    */

	EnemyList::GetSingleton()->Draw();
	m_pHero->Draw();
	ParticleList::GetSingleton()->Draw();

	if (m_pHero->isDead())
	{
		SPRITE_ENGINE->GetFontManager()->DrawString(_T("Arial"), _T("Press Right Mouse button to try again"), 0.0f,
                                                SPRITE_ENGINE->GetBackBufferHeight() - 20.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}
}