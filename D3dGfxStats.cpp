#include "D3dGfxStats.h"

#include "FontManager.h"

D3dGfxStats::D3dGfxStats(): m_MyFps(0),m_MyMilliSecPerFrame(0)
{
}
D3dGfxStats::~D3dGfxStats()
{
}
bool D3dGfxStats::Initialize()
{
	return true;
}
void D3dGfxStats::OnLostDevice()
{
}
void D3dGfxStats::OnResetDevice()
{
}
void D3dGfxStats::Update(float dtime)
{
	static float numFrames = 0.0f;
	static float TimeElapsed = 0.0f;

	numFrames++;
	TimeElapsed+=dtime;

	if(TimeElapsed>=1.0f)
	{
		//Since u've already passed the 1 second mark, remove one frame
		numFrames--;

		m_MyFps = numFrames;
		m_MyMilliSecPerFrame=1000.0f/m_MyFps;

		numFrames=0.0f;
		TimeElapsed=0.0f;
	}	
}
void D3dGfxStats::DrawFps()
{
	tstringstream buffer;
	buffer<<m_MyFps;
	tstring Message=_T("Frames per Second: ");
	Message+=buffer.str();

	RECT drawRect;
	drawRect.bottom=5;
	drawRect.left=0;
	drawRect.right=5;
	drawRect.top=0;

	SPRITE_ENGINE->GetFontManager()->DrawStringEx(_T(""),Message, drawRect, DT_NOCLIP, D3DCOLOR_XRGB(0,0,0));
}