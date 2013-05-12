/*
Class wich checks keyboard and mouse input.
*/

#ifndef DIRECTINPUT_H_INCLUDED
#define DIRECTINPUT_H_INCLUDED

#include "SpriteEngine.h"

/*
This class might look "complicated" in implementation, but it is standard stuff. This is just how u open keyboard and mouse input with directX. I've encapsulated most
directX functions to initialize the keyboard/mouse and it's update. Users need only to use the simple functions to check wether buttons are pressed or not...

DirectX uses a Interface for input devices called "IDirectInputDevice" (notice the I for interface :) ) As u might notice there are 2 input devices used here. Mouse and 
keyboard. So 2 IDirectInputDevices are made and initialized in a equal manner. The initalize should just be taken as it is. Not much to comprehend, this is just how devices
are initialized.

By calling "Acquire" on inputDevices u receive the current "state" of the device. Meaning which buttons are pressed or not... Before the acquire there's a check to see if
the devices are active or enabled to acquire data from!
*/
class DirectInput
{
public:
	DirectInput();
	virtual ~DirectInput();

	bool Init(DWORD keyboardCoopFlags, DWORD mouseCoopFlags);

	void UpdateInput();

	bool IsKeyDown(unsigned char key);
	bool IsKeyPressed(unsigned char key);

	void IdentifyKey();

	bool MouseButtonDown(int button);
	bool MouseButtonPressed(int Button);

	D3DXVECTOR2 GetMouseXY() const;

	float GetMouseDx() const;
	float GetMouseDy() const;
	float GetMouseDz() const;

private:
	IDirectInput8* m_pdInput;

	IDirectInputDevice8* m_pMyKeyboard;
	char m_KeyboardState[256];

	int IsKeyPressedOldkey;
	int IsMousePressedOldButton;

	IDirectInputDevice8* m_pMyMouse;
	DIMOUSESTATE2 m_MouseState;

	DirectInput(const DirectInput& t);
	DirectInput& operator=(const DirectInput& t);
};
#endif