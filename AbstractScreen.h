/*
Abstract for screens.
*/

#ifndef ABSTRACTSCREEN_H_INCLUDED
#define ABSTRACTSCREEN_H_INCLUDED

#include "SpriteEngine.h"

/*
Base class for screens, inheret from this class to create a new screentype
*/
class AbstractScreen
{
public:
	AbstractScreen();
	virtual ~AbstractScreen();

	virtual bool Initialize() = 0;

	virtual void UpdateScene(float dtime) = 0;

	virtual void DrawScene() = 0;

protected:

	AbstractScreen(const AbstractScreen& t);
	AbstractScreen& operator=(const AbstractScreen& t);
};
#endif