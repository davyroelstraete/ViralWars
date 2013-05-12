/*
Base class for creating applications.
*/

#ifndef D3DAPP_H_INCLUDED
#define D3DAPP_H_INCLUDED

#include "D3dUtils.h"

/*
This is the most important "base" class for the entire engine. This is the basic functionality for a engine. Users can create own new "engines" by inhereting from
this class and use the basic functionality. This class creates all objects engine's share, such as the window, the d3dDevice and the simple loop. More intel can be found
in the .cpp!
*/
class D3dApp
{		
friend LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
friend int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE prevInstance,PSTR cmdLine,int showCmd);
public:
	D3dApp(HINSTANCE hInstance,const tstring& winCaption, D3DDEVTYPE devType, DWORD requestedVp);
	virtual ~D3dApp();

	virtual bool CheckDeviceCaps()			{return true;}
	virtual void OnLostDevice()				{}
	virtual void OnResetDevice()			{}
	virtual void UpdateScene(float dtime)	{}
	virtual void DrawScene()				{}
	virtual void DrawPostProcess()          {}

	virtual void InitMainWindow();
	virtual void InitDirect3D();

	virtual int Run();
	virtual LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

	void EnableFullScreen(bool enable);
	bool IsDeviceLost();

	HINSTANCE GetAppInst() const;
	HWND GetMainWnd() const;
	LPDIRECT3DDEVICE9 GetD3dDevice() const;

	const float GetBackBufferWidth() const;
	const float GetBackBufferHeight() const;

	const tstring& GetAppDirectory();

protected:
	tstring m_MainWndCaption;
	D3DDEVTYPE m_DevType;
	DWORD m_RequestedVp;

	HINSTANCE m_hAppInst;
	HWND m_hMainWnd;
	LPDIRECT3D9 m_pD3dObject;
	bool m_AppPaused;	

	LPDIRECT3DDEVICE9 m_pMyD3dDevice;
	D3DPRESENT_PARAMETERS m_D3dParams;

	tstring AppDirectory;

private:
	D3dApp(const D3dApp& t);
	D3dApp& operator=(const D3dApp& t);
};
#endif