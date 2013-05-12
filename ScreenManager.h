/*
class controlling the active screen.
*/

#ifndef SCREENMANAGER_H_INCLUDED
#define SCREENMANAGER_H_INCLUDED

#include "AbstractScreen.h"

/*
The screenManager simply keeps 2 abstractScreens. The old and active one. It'll call initialize, update en drawscene on the activescreen. The old one is
only used when screens are switched. To avoid trouble the current active one will first move to the old pointer. If u simply delete the active one, there might be
issues if for instance the screen was still in a update or a draw... This only happens if u call "SwitchScreen" in seperate threads or in events. This problem
is handled by not directly deleting the active screen if u switch to a new one!
*/

class ScreenManager
{
public:
	ScreenManager();
	virtual ~ScreenManager();

	bool Initialize();
	bool SwitchScreen(AbstractScreen* const newScreen);
	
	void UpdateScene(float dtime);

	void DrawScene();

private:
	AbstractScreen* m_pMyOldScreen;
	AbstractScreen* m_pMyActiveScreen;

	ScreenManager(const ScreenManager& t);
	ScreenManager& operator=(const ScreenManager& t);
};
#endif