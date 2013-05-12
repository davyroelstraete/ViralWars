#include "MainScreen.h"

#include "GameScreen.h"
#include "DirectInput.h"
#include "FontManager.h"
#include "ScreenManager.h"

/*
Always include the parts from the Engine you use in the .cpp!! Not in .h!!!
*/

MainScreen::MainScreen()
{
}
MainScreen::~MainScreen()
{
	EnemyList::GetSingleton()->Clear();
	ParticleList::GetSingleton()->Clear();
}
/*
Use the initialize to create objects and check whether it succeeds or not. Return false to end
*/
bool MainScreen::Initialize()
{
	SPRITE_ENGINE->EnableCursor(true);
	SPRITE_ENGINE->EnableFullScreen(true);
	return true;
}
/*
UpdateScene updates at 60 frames a second max. dtime corresponds to the time passed since previous frame in terms of seconds
*/
void MainScreen::UpdateScene(float dtime)
{
    /*
    Example of handling input, simply call the GetInput() from the Engine and use functionality. Check allows either isPressed or isDown
    */


    if(SPRITE_ENGINE->GetInput()->IsKeyPressed(DIK_ESCAPE)) SPRITE_ENGINE->ShutDownEngine();

    /*
    Mousebutton are numbered. 0 = left, 1 = right and 2 equals middle mouse button
    MouseDx, MouseDy, MouseDz correspond to mousemovements and scroll normally
    */
    if(SPRITE_ENGINE->GetInput()->MouseButtonPressed(1)) SPRITE_ENGINE->GetScreenManager()->SwitchScreen(new GameScreen());

    /*
    To change screens, call the ScreenManager and simply use SwitchScreen and create the new one.
    */
}
void MainScreen::DrawScene()
{
    /*
    To draw text, use the FontManager which allows to choose standard Fonts, position and color for the text
    */
    SPRITE_ENGINE->GetFontManager()->DrawString(_T("Arial"), _T("Press Right Mouse button to Continue"), 0.0f,
                                                SPRITE_ENGINE->GetBackBufferHeight() - 20.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}