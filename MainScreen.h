/*
Main screen
*/

#ifndef MAINSCREEN_H_INCLUDED
#define MAINSCREEN_H_INCLUDED

#include "AbstractScreen.h"

/*
Screens are made by inhereting from AbstractScreen. To Create own screen, you can use this one as a example!
*/

class MainScreen : public AbstractScreen
{
public:
	MainScreen();
	virtual ~MainScreen();

	bool Initialize();

	void UpdateScene(float dtime);
	void DrawScene();

private:

	MainScreen(const MainScreen& t);
	MainScreen& operator=(const MainScreen& t);
};
#endif