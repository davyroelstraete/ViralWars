#include "DirectInput.h"

DirectInput::DirectInput():m_pdInput(NULL),m_pMyKeyboard(NULL),IsKeyPressedOldkey(-1),IsMousePressedOldButton(-1),m_pMyMouse(NULL)
{
	ZeroMemory(&m_KeyboardState,sizeof(m_KeyboardState));
	ZeroMemory(&m_MouseState,sizeof(m_MouseState));
}
DirectInput::~DirectInput()
{
	ReleaseObject(m_pdInput);

	m_pMyKeyboard->Unacquire();
	m_pMyMouse->Unacquire();

	ReleaseObject(m_pMyKeyboard);
	ReleaseObject(m_pMyMouse);
}
bool DirectInput::Init(DWORD keyboardCoopFlags, DWORD mouseCoopFlags)
{
	if(FAILED(DirectInput8Create(SPRITE_ENGINE->GetAppInst(),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&m_pdInput,0))){
		MessageBox(SPRITE_ENGINE->GetMainWnd(),_T("Failed to create DirectInputDevice!"),0,0);
		return false;
	}

	if(FAILED(m_pdInput->CreateDevice(GUID_SysKeyboard,&m_pMyKeyboard,0))){
		MessageBox(SPRITE_ENGINE->GetMainWnd(),_T("Failed to create Keyboard!"),0,0);
		return false;
	}
	if(FAILED(m_pMyKeyboard->SetDataFormat(&c_dfDIKeyboard))) return false;
	if(FAILED(m_pMyKeyboard->SetCooperativeLevel(SPRITE_ENGINE->GetMainWnd(),keyboardCoopFlags)))	return false;

	m_pMyKeyboard->Acquire();

	if(FAILED(m_pdInput->CreateDevice(GUID_SysMouse,&m_pMyMouse,0))){
		MessageBox(SPRITE_ENGINE->GetMainWnd(),_T("Failed to create Mouse!"),0,0);
		return false;
	}
	if(FAILED(m_pMyMouse->SetDataFormat(&c_dfDIMouse2)))	return false;
	if(FAILED(m_pMyMouse->SetCooperativeLevel(SPRITE_ENGINE->GetMainWnd(),mouseCoopFlags)))	return false;

	m_pMyMouse->Acquire();

	return true;
}
void DirectInput::UpdateInput()
{
	if(FAILED(m_pMyKeyboard->GetDeviceState(sizeof(m_KeyboardState),(void**)&m_KeyboardState))){
		ZeroMemory(&m_KeyboardState,sizeof(m_KeyboardState));
		m_pMyKeyboard->Acquire();
	}

	if(FAILED(m_pMyMouse->GetDeviceState(sizeof(m_MouseState),(void**)&m_MouseState))){
		ZeroMemory(&m_MouseState,sizeof(m_MouseState));
		m_pMyMouse->Acquire();
	}
}
bool DirectInput::IsKeyDown(unsigned char key)
{
	return (m_KeyboardState[key] & 0x80) != 0;
}
bool DirectInput::IsKeyPressed(unsigned char key){
	
	bool KeyDown = IsKeyDown(key);
	if(IsKeyPressedOldkey == -1 && KeyDown){
		IsKeyPressedOldkey = key;
		return false;
	}
	if(IsKeyPressedOldkey == key && !KeyDown){
		IsKeyPressedOldkey = -1;
		return true;
	}
	return false;
}
void DirectInput::IdentifyKey(){
	int character=256;
	for(int i = 0; i < 256;  i++){
		if((m_KeyboardState[i] & 0x80) != 0){
			character = i;
			break;
		}
	}
	tstringstream buffer;
	buffer << character;
	buffer << _T("\n");
	OutputDebugString(buffer.str().c_str());
}
bool DirectInput::MouseButtonDown(int button)
{
	return (m_MouseState.rgbButtons[button] & 0x80) != 0;
}
bool DirectInput::MouseButtonPressed(int Button)
{
	bool KeyDown = MouseButtonDown(Button);
	if(IsMousePressedOldButton == -1 && KeyDown){
		IsMousePressedOldButton = Button;
		return false;
	}
	if(IsMousePressedOldButton == Button && !KeyDown){
		IsMousePressedOldButton = -1;
		return true;
	}
	return false;
}
D3DXVECTOR2 DirectInput::GetMouseXY() const
{
	LPPOINT p = new POINT();
	GetCursorPos(p); //get screen coordinates of the cursor
	ScreenToClient(SPRITE_ENGINE->GetMainWnd(), p); //takes the screen coordinates provided by the GetCursorPos function, and transform then into our local window space
	return D3DXVECTOR2(p->x, p->y);
}
float DirectInput::GetMouseDx() const
{
	return static_cast<float>(m_MouseState.lX);
}
float DirectInput::GetMouseDy() const
{
	return static_cast<float>(m_MouseState.lY);
}
float DirectInput::GetMouseDz() const
{
	return static_cast<float>(m_MouseState.lZ);
}