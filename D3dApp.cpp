#include "D3dApp.h"

D3dApp::D3dApp(HINSTANCE hInstance,const tstring& winCaption, D3DDEVTYPE devType, DWORD requestedVp):m_MainWndCaption(winCaption),
																								m_DevType(devType),
																								m_RequestedVp(requestedVp),
																								m_hAppInst(hInstance),
																								m_hMainWnd(NULL),
																								m_pD3dObject(NULL),
																								m_AppPaused(false),
																								m_pMyD3dDevice(NULL)
{
	ZeroMemory(&m_D3dParams, sizeof(m_D3dParams));

	InitMainWindow();
	InitDirect3D();
}
D3dApp::~D3dApp()
{
	ReleaseObject(m_pD3dObject);
	ReleaseObject(m_pMyD3dDevice);
}
/*
The main window is created here! Here users can set the style of the window, its resolution and name...
*/
void D3dApp::InitMainWindow()
{
    //WNDCLASS is a win32 struct containing a load of parameters describing the window. Here u can change the cursor, name, icon,...
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = MainWndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hAppInst;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = _T("D3DWndClassName");

    //This needs to happen! :)
	if( !RegisterClass(&wc) )
	{
		MessageBox(0, _T("RegisterClass FAILED"), 0, 0);
		PostQuitMessage(0);
	}

	// Default to a window with a client area rectangle of 800x600. Adjust the RECT values to change the resolution!
	RECT windowrect = {0, 0,800, 600};

	AdjustWindowRect(&windowrect, WS_CAPTION, false);

    //Create the window with all parameters set
	m_hMainWnd = CreateWindow(_T("D3DWndClassName"), m_MainWndCaption.c_str(), 
		WS_CAPTION, (GetSystemMetrics(SM_CXSCREEN)/2)-(windowrect.right/2),
		(GetSystemMetrics(SM_CYSCREEN)/2)-(windowrect.bottom/2),
		windowrect.right, windowrect.bottom, 0, 0, m_hAppInst, 0); 

	if( !m_hMainWnd )
	{
		MessageBox(0,_T("CreateWindow FAILED"), 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);
}
/*
The D3DDevice is created here! Here users can set parameters such as anti-aliasing...
*/
void D3dApp::InitDirect3D()
{
	// Step 1: Create the IDirect3D9 object.

	m_pD3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if( m_pD3dObject == NULL )
	{
		MessageBox(0, _T("Direct3DCreate9 FAILED"), 0, 0);
		PostQuitMessage(0);
	}

	// Step 2: Verify hardware support for specified formats in windowed and full screen modes.
	
	D3DDISPLAYMODE mode;
	m_pD3dObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
	if(FAILED(m_pD3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, m_DevType, mode.Format, mode.Format, true)))
	{
		MessageBox(0, _T("Hardware Support FAILED"), 0, 0);
		PostQuitMessage(0);
	}
	if(FAILED(m_pD3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, m_DevType, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, false)))
	{
		MessageBox(0, _T("Hardware Support FAILED"), 0, 0);
		PostQuitMessage(0);
	}

	// Step 3: Check for requested vertex processing and pure device.

	D3DCAPS9 caps;
	m_pD3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, m_DevType, &caps);

	DWORD devBehaviorFlags = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		devBehaviorFlags |= m_RequestedVp;
	else
		devBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// If pure device and HW T&L supported
	if( caps.DevCaps & D3DDEVCAPS_PUREDEVICE &&
		devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
			devBehaviorFlags |= D3DCREATE_PUREDEVICE;

	//Enable multithreading!! (Other flags are possible to add using |= syntax, this opens other functionality)
	devBehaviorFlags |= D3DCREATE_MULTITHREADED;

	// Step 4: Fill out the D3DPRESENT_PARAMETERS structure. Multisample = anti-aliasing for instance...

	m_D3dParams.BackBufferWidth            = 0; 
	m_D3dParams.BackBufferHeight           = 0;
	m_D3dParams.BackBufferFormat           = D3DFMT_UNKNOWN;
	m_D3dParams.BackBufferCount            = 1;
	m_D3dParams.MultiSampleType            = D3DMULTISAMPLE_NONE;
	m_D3dParams.MultiSampleQuality         = 0;
	m_D3dParams.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	m_D3dParams.hDeviceWindow              = m_hMainWnd;
	m_D3dParams.Windowed                   = true;
	m_D3dParams.EnableAutoDepthStencil     = true; 
	m_D3dParams.AutoDepthStencilFormat     = D3DFMT_D24S8;
	m_D3dParams.Flags                      = 0;
	m_D3dParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_D3dParams.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 5: Create the device.

	if(FAILED((m_pD3dObject->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		m_DevType,           // device type
		m_hMainWnd,          // window associated with device
		devBehaviorFlags,   // vertex processing
	    &m_D3dParams,            // present parameters
		&m_pMyD3dDevice))))  // return created device
	{
		MessageBox(0,_T("Failed to create the device"),0,0);
		PostQuitMessage(0);
	}

	//Get the directory of the appclication;
	WCHAR appPath[MAX_PATH] = L"";
	int ch = '\\' ;

	GetModuleFileName(0, appPath, sizeof(appPath) - 1);
	tstring AppFileName = wcsrchr(appPath,static_cast<wchar_t>(ch));
	tstring AppPath = appPath;
	AppDirectory = AppPath.substr(0, AppPath.find(AppFileName)+1);
}
/*
This is the main loop which will continue to run as long as the engine is active!
*/
int D3dApp::Run()
{
	MSG msg;
	msg.message = WM_NULL;

    //First use "QueryPerformanceFrequency" (win32 c++ function) to check how many counts per second the program is capable off (in other words the cpu with this program)
	__int64 cntsPerSec=0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);

    //When u know how many counts there will be per second, u can choose how many frames will be drawn per second. For instance, when u want 60 frames per second, u divide
    //the calculated cntsPerSec with 60. Then u know how many counts (ticks) must pass within one second to draw a frame. So instead of drawing each frame after randomly elapsed
    //Counts, u only draw a frame when the wanted counts have passed. Example: 6000 counts per second. Without framecapping, one frame might be drawn after 3 counts of after 50...
    //When u only draw a frame AFTER say 100 counts have passed (6000 / 60) that means u'll only draw 60 frames per second. Why? Cause u'll only have 6000 counts in one second,
    //so only 60 times will there be 100 counts, so 60 times a frame will be rendered!
	DWORD frameCap = (DWORD)(cntsPerSec / 60);
	LONGLONG nextTimeStamp = 0;
	float secsPerCnt=1.0f/(float)cntsPerSec;

    //Here u ask the previous number of counts
	__int64 prevTimeStamp=0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	while(msg.message != WM_QUIT)
	{
        //PeekMessage simply checks for windows messages. If for instance u allow the window to have a "close" button up top. (Which I Don't :p ) Pressing it
        //will send the WM_QUIT message. This would stop the message while loop for instance...
		if(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if(m_AppPaused)
			{
				Sleep(20);
				continue;
			}
			else
			{
                //Calculate the current counts. (Counts don't reset to zero, they keep adding up!!!! so they go above 6000 if u use the example!)
				__int64 currTimeStamp=0;
				QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);

                //U know 100 counts need to be elapsed (again using the example of 6000 counts per second) to draw a frame. Meaning u start with "nextTimeStamp = 0"
                //CurrTimeStamp is will begin at lets say 100 counts -> 100 > 0 so u'll draw a frame. Then "nextimeStamp = currTimeStamp + 100" so u are sure that only
                //after the next 100 counts u'll draw a frame. Since the currTimeStamp is larger than nextTimeStamp --> TADA FRAMECAP :)
				if (currTimeStamp>=nextTimeStamp)
				{
					nextTimeStamp += frameCap;

					if (nextTimeStamp < currTimeStamp)
						nextTimeStamp = currTimeStamp + frameCap;

					float dtime=(currTimeStamp-prevTimeStamp)*secsPerCnt;

					UpdateScene(dtime);
					DrawScene();

					prevTimeStamp=currTimeStamp;	
				}
			}
		}
	}
	return (int)msg.wParam;
}
LRESULT D3dApp::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool minOrMaxed = false;

	RECT clientRect = {0, 0, 0, 0};
	switch( msg )
	{
	case WM_ACTIVATE:
		if( LOWORD(wParam) == WA_INACTIVE )
			m_AppPaused = true;
		else
			m_AppPaused = false;
		return 0;

	case WM_CLOSE:
		DestroyWindow(m_hMainWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(m_hMainWnd, msg, wParam, lParam);
}
void D3dApp::EnableFullScreen(bool enable)
{
	if(enable)
	{
		if(!m_D3dParams.Windowed)return;

		int Width = GetSystemMetrics(SM_CXSCREEN);
		int Height = GetSystemMetrics(SM_CYSCREEN);

		m_D3dParams.BackBufferFormat = D3DFMT_X8R8G8B8;
		m_D3dParams.BackBufferWidth = Width;
		m_D3dParams.BackBufferHeight = Height;

		m_D3dParams.Windowed = false;

		SetWindowLongPtr(m_hMainWnd, GWL_STYLE, WS_POPUP);

		SetWindowPos(m_hMainWnd,HWND_TOP,0,0,Width,Height,SWP_NOZORDER | SWP_SHOWWINDOW);
	}
	else
	{
		if(m_D3dParams.Windowed)return;

		RECT windowrect = {0,0, 800,600};

		AdjustWindowRect(&windowrect,WS_CAPTION,false);

		m_D3dParams.BackBufferFormat = D3DFMT_UNKNOWN;
		m_D3dParams.BackBufferWidth = windowrect.right;
		m_D3dParams.BackBufferHeight = windowrect.bottom;
		m_D3dParams.Windowed = true;

		SetWindowLongPtr(m_hMainWnd, GWL_STYLE, WS_CAPTION);

		SetWindowPos(m_hMainWnd,HWND_TOP,(GetSystemMetrics(SM_CXSCREEN)/2)-(windowrect.right/2),
		(GetSystemMetrics(SM_CYSCREEN)/2)-(windowrect.bottom/2),
			windowrect.right,windowrect.bottom,SWP_NOZORDER | SWP_SHOWWINDOW);
	}

	OnLostDevice();
	m_pMyD3dDevice->Reset(&m_D3dParams);
	OnResetDevice();
}
bool D3dApp::IsDeviceLost()
{
	HRESULT hr = m_pMyD3dDevice->TestCooperativeLevel();

	if(hr==D3DERR_DEVICELOST)
	{
		Sleep(20);
		return true;
	}
	else if(hr==D3DERR_DRIVERINTERNALERROR)
	{
		MessageBox(0,_T("Internal Driver Error... Exiting"),0,0);
		PostQuitMessage(0);
		return true;
	}
	else if(hr==D3DERR_DEVICENOTRESET)
	{
		OnLostDevice();
		m_pMyD3dDevice->Reset(&m_D3dParams);
		OnResetDevice();
		return false;
	}
	else
	{
		return false;
	}
}
HINSTANCE D3dApp::GetAppInst() const
{
	return m_hAppInst;
}
HWND D3dApp::GetMainWnd() const
{
	return m_hMainWnd;
}
LPDIRECT3DDEVICE9 D3dApp::GetD3dDevice() const
{
	return m_pMyD3dDevice;
}
const float D3dApp::GetBackBufferWidth() const
{
	return static_cast<float>(m_D3dParams.BackBufferWidth);
}
const float D3dApp::GetBackBufferHeight() const
{
	return static_cast<float>(m_D3dParams.BackBufferHeight);
}
const tstring& D3dApp::GetAppDirectory()
{
	return AppDirectory;
}