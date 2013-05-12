/*
Class managing the fps and other graphical stats.
*/

#ifndef D3DGFXSTATS_H_INCLUDED
#define D3DGFXSTATS_H_INCLUDED

#include "SpriteEngine.h"

/*
Basic class which only calculates en displays the current FPS... In the update it just adds one frame everytime the update is called and uses dtime
to check wether one second has passed or not. Quite simple
*/
class D3dGfxStats
{
public:
	D3dGfxStats();
	virtual ~D3dGfxStats();

	bool Initialize();

	void OnLostDevice();
	void OnResetDevice();

	void Update(float dtime);
	void DrawFps();

private:
	float m_MyFps;
	float m_MyMilliSecPerFrame;

	D3dGfxStats(const D3dGfxStats& t);
	D3dGfxStats& operator=(const D3dGfxStats& t);
};
#endif