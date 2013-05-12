#include "SpriteEngine.h"

#include "Camera.h"
#include "MainScreen.h"
#include "DirectInput.h"
#include "D3dGfxStats.h"
#include "FontManager.h"
#include "ScreenManager.h"
#include "TextureManager.h"

SpriteEngine* SpriteEngine::m_pMySingleton = NULL;

/*
Now This is the only weird thing! THIS "int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,PSTR cmdLine,int showCmd)" Is the 
function that is called by win32! Why Dno! If u create a empty project, this is the main function u'll need to write to start SOMETHING!

Notice what I Do here, simply create a SpriteEngine (stack stack stack -> when the program stops running it calls destructor of the SpriteEngine!) followed by
"Return Engine.Run() !!! -> when this returns 0 the function ENDS. (This loop is handled in D3DApp!)
*/
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,PSTR cmdLine,int showCmd)
{
	SpriteEngine Engine(hInstance,_T("Kinect"), D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
	
	return Engine.Run();
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //Singleton has been made in the WINAPI above this one! This function is called when messages are peeked! Simply check if the D3DApp exists, if so
    //Start sending the messages to the D3DApp and handle them there!

	SpriteEngine*App=0;
	App=App->GetSingleton();
	// Don't start processing messages until the application has been created.
	if( App != 0 )
	{
		return App->msgProc(msg, wParam, lParam);
	}
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}
//------------------------------------------------------------------------------------------------------------
// intizializing the engine
//------------------------------------------------------------------------------------------------------------
SpriteEngine::SpriteEngine(HINSTANCE hInstance,const tstring& winCaption, D3DDEVTYPE devType, DWORD requestedVp):D3dApp(hInstance,winCaption,devType,requestedVp),
                                                                                                            m_pMySpriteBatch(NULL),
																											m_IsRunning(true),
																											m_IsDeviceLost(false),
																											m_IsShowingCursor(true),
																											m_pMyCamera(NULL),
																											m_pMyDxInput(NULL),
																											m_pMyGfxStats(NULL),
																											m_pMyFontManager(NULL),
																											m_pMyScreenManager(NULL),
																											m_pMyTextureManager(NULL)
{
	m_pMySingleton=this;

	if(!CheckDeviceCaps())
	{
		MessageBox(0, _T("checkDeviceCaps() Failed"), 0, 0);
		PostQuitMessage(0);
	}
	if(!InitEngine())
	{
		MessageBox(0, _T("InitEngine() Failed"), 0, 0);
		PostQuitMessage(0);
	}
}
SpriteEngine::~SpriteEngine()
{
    ReleaseObject(m_pMySpriteBatch);

	DestroyObject(m_pMyCamera);
	DestroyObject(m_pMyDxInput);
	DestroyObject(m_pMyGfxStats);
	DestroyObject(m_pMyFontManager);
	DestroyObject(m_pMyScreenManager);
	DestroyObject(m_pMyTextureManager);
}
bool SpriteEngine::CheckDeviceCaps()
{
	D3DCAPS9 caps;
	if(FAILED(m_pMyD3dDevice->GetDeviceCaps(&caps))) return false;;

	// Check for vertex shader version 2.0 support.
	if( caps.VertexShaderVersion < D3DVS_VERSION(2, 0) )
		return false;

	// Check for pixel shader version 2.0 support.
	if( caps.PixelShaderVersion < D3DPS_VERSION(2, 0) )
		return false;

	// Check render target support.  The adapter format can be either the display mode format
	// for windowed mode, or D3DFMT_X8R8G8B8 for fullscreen mode, so we need to test against
	// both.  We use D3DFMT_R32F as the render texture format and D3DFMT_D24X8 as the 
	// render texture depth format.
	D3DDISPLAYMODE mode;
	m_pD3dObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);

	// Windowed.
	if(FAILED(m_pD3dObject->CheckDeviceFormat(D3DADAPTER_DEFAULT, m_DevType, mode.Format, 
		D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE, D3DFMT_R32F)))
		return false;
	if(FAILED(m_pD3dObject->CheckDepthStencilMatch(D3DADAPTER_DEFAULT, m_DevType, mode.Format,
		D3DFMT_R32F, D3DFMT_D24X8)))
		return false;

	// Fullscreen.
	if(FAILED(m_pD3dObject->CheckDeviceFormat(D3DADAPTER_DEFAULT, m_DevType, D3DFMT_X8R8G8B8, 
		D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE, D3DFMT_R32F)))
		return false;
	if(FAILED(m_pD3dObject->CheckDepthStencilMatch(D3DADAPTER_DEFAULT, m_DevType, D3DFMT_X8R8G8B8,
		D3DFMT_R32F, D3DFMT_D24X8)))
		return false;

	return true;
}
void SpriteEngine::OnLostDevice()
{
	m_IsDeviceLost=true;

	if(m_pMyGfxStats!=NULL) m_pMyGfxStats->OnLostDevice();
	if(m_pMySpriteBatch!=NULL) m_pMySpriteBatch->OnLostDevice();
	if(m_pMyFontManager!=NULL) m_pMyFontManager->OnLostDevice();
}
void SpriteEngine::OnResetDevice()
{
	if(m_pMyCamera!=NULL) m_pMyCamera->Update(0.0f);
	if(m_pMyGfxStats!=NULL) m_pMyGfxStats->OnResetDevice();
	if(m_pMySpriteBatch!=NULL) m_pMySpriteBatch->OnResetDevice();
	if(m_pMyFontManager!=NULL) m_pMyFontManager->OnResetDevice();

	m_IsDeviceLost=false;
}
bool SpriteEngine::InitEngine()
{
	srand(static_cast<UINT>(timeGetTime()));

	m_pMyCamera = new Camera();
	if(!m_pMyCamera->Init(D3DXVECTOR3(0.0f,1.0f,-4.0f))) return false;

    if(FAILED(D3DXCreateSprite(m_pMyD3dDevice,&m_pMySpriteBatch))) return false;

	m_pMyDxInput=new DirectInput();
	if(!m_pMyDxInput->Init(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) return false;

	m_pMyGfxStats = new	D3dGfxStats();
	if(!m_pMyGfxStats->Initialize()) return false;


	m_pMyFontManager = new FontManager();
	m_pMyTextureManager = new TextureManager();

	m_pMyScreenManager = new ScreenManager();
	if(!m_pMyScreenManager->SwitchScreen(new MainScreen())) return false;

	return true;
}
//------------------------------------------------------------------------------------------------------------
// update and draw
//------------------------------------------------------------------------------------------------------------
void SpriteEngine::UpdateScene(float dtime)
{
	if(!m_IsRunning) PostQuitMessage(0);

	if(m_pMyDxInput!=NULL) m_pMyDxInput->UpdateInput();

	if(m_pMyCamera!=NULL) m_pMyCamera->Update(dtime);
	if(m_pMyGfxStats!=NULL) m_pMyGfxStats->Update(dtime);
	if(m_pMyScreenManager!=NULL) m_pMyScreenManager->UpdateScene(dtime);
}
void SpriteEngine::DrawScene()
{
	if(!m_IsDeviceLost)
	{
		GetD3dDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
		GetD3dDevice()->BeginScene();

        m_pMySpriteBatch->Begin(D3DXSPRITE_ALPHABLEND);

		if(m_pMyScreenManager!=NULL) m_pMyScreenManager->DrawScene();

        m_pMySpriteBatch->End();

		//if(m_pMyGfxStats!=NULL) m_pMyGfxStats->DrawFps();

		GetD3dDevice()->EndScene();
		GetD3dDevice()->Present(0, 0, 0, 0);
	}
}
//------------------------------------------------------------------------------------------------------------
// Getters for global objects.
//------------------------------------------------------------------------------------------------------------
Camera* SpriteEngine::GetCamera() const
{
	return m_pMyCamera;
}
DirectInput* SpriteEngine::GetInput() const
{
	return m_pMyDxInput;
}
FontManager* SpriteEngine::GetFontManager() const
{
	return m_pMyFontManager;
}
ScreenManager* SpriteEngine::GetScreenManager() const
{
    return m_pMyScreenManager;
}
TextureManager* SpriteEngine::GetTextureManager() const
{
	return m_pMyTextureManager;
}
LPD3DXSPRITE SpriteEngine::GetSpriteBatch() const
{
    return m_pMySpriteBatch;
}
SpriteEngine* SpriteEngine::GetSingleton()
{
		return m_pMySingleton;
}
bool SpriteEngine::IsWindowed() const
{
	if(m_D3dParams.Windowed) return true;
	
	return false;
}
void SpriteEngine::EnableCursor(bool visible)
{
	if (m_IsShowingCursor != visible) ShowCursor(visible);
}
//------------------------------------------------------------------------------------------------------------
// Global handy functions.
//------------------------------------------------------------------------------------------------------------
void SpriteEngine::ShutDownEngine()
{
	m_IsRunning=false;
}