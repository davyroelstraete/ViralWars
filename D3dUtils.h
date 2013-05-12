/*
Utility class containing headers and handy stuff.
*/

#ifndef D3DUTILS_H_INCLUDED
#define D3DUTILS_H_INCLUDED

//---------------------------------------------
// Includes and defines.
//---------------------------------------------
#include <windows.h>
 
#include <string>
#include <tchar.h>
#include <sstream>
#include <algorithm>

#include <d3d9.h> 
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

//Include the containers
#include <vector>
#include <map>
#include <deque>
#include <list>

using namespace std;

//---------------------------------------------
// define tstring.
//---------------------------------------------

#ifdef _UNICODE
	#define tstring wstring
	#define tstringstream wstringstream
	#define tofstream wofstream
	#define tifstream wifstream
	#define tfstream wfstream
#else
	#define tstring string
	#define tstringstream stringstream
	#define tofstream ofstream
	#define tifstream ifstream
	#define tfstream fstream
#endif


//---------------------------------------------
// Globals.
//---------------------------------------------

static const tstring TextureDir = _T("Content\\Textures\\");

//---------------------------------------------
// Cleanup.
//---------------------------------------------

/*
Use these functions for cleanup duty, u'll never have to check if objects are zero, since these do it for u

Note: Use ReleaseObject on DirectX pointers (e.g. LPDIRECT3DTEXTURE9), use DestroyObject on own object pointers
*/

#define ReleaseObject(x) { if(x!=0){ x->Release();x=0;} }
#define DestroyObject(x) { if(x!=0){ delete x;x=0;} }
#define DestroyArray(x) { if(x!=0){ delete[] x;x=0;} }

//---------------------------------------------
// Functors for algorithms
//---------------------------------------------

/*
List of handy functions to use on lists with foreach
*/
template <class T>
class DeleteItemOnHeap
{
public:
	void operator()(T item){
		DestroyObject(item);
	}
};
template <class T>
class ReleaseItemOnHeap
{
	public:
	void operator()(T item){
		ReleaseObject(item);
	}
};
template <class T>
class OnLostDeviceOnPointer
{
	public:
	void operator()(T item){
		if(item!=0)	item->OnLostDevice();
	}
};
template <class T>
class OnResetDeviceOnPointer
{
	public:
	void operator()(T item){
		if(item!=0)	item->OnResetDevice();
	}
};
template <class T>
class DrawOnPointer
{
	public:
	void operator()(T item){
		if(item!=0)	item->Draw();
	}
};
template <class T>
class DrawSpritesOnPointer
{
	public:
	void operator()(T item){
		if(item!=0)	item->DrawSprites();
	}
};
template <class T>
class TimeUpdateOnPointer
{
private:
	float dTime;
public:
	TimeUpdateOnPointer(float dtime):dTime(dtime){}
	void operator()(T item){
		if(item!=0)	item->Update(dTime);
	}
};
template <class T>
class UpdateOnPointer
{
	public:
	void operator()(T item){
		if(item!=0)	item->Update();
	}
};
template <class T>
class HandleInputOnPointer
{
public:
	void operator()(T item){
		if(item != 0) item->HandleInput();
	}
};
//---------------------------------------------
// Generates random float.
//---------------------------------------------
float GetRandomFloat(float a, float b);
//---------------------------------------------
// converts from degrees to radian.
//---------------------------------------------
float DegreeToRad(float degrees);
float RadToDegree(float radian);
//---------------------------------------------

#endif //D3DUTILS_H_INCLUDED