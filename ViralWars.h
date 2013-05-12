//-----------------------------------------------------------------
// Game File
// C++ Header - ViralWars.h - version 2007 v3_01												
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Resource.h"	
#include "GameEngine.h"
#include "AbstractGame.h"

#include "Vector2.h"
#include "Hero.h"
#include "BulletList.h"
#include "EnemyList.h"
#include "ParticleList.h"

//-----------------------------------------------------------------
// ViralWars Class																
//-----------------------------------------------------------------
class ViralWars : public AbstractGame
{
public:				
	//---------------------------
	// Constructor(s)
	//---------------------------
	ViralWars();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~ViralWars();

	//---------------------------
	// General Methods
	//---------------------------

	void GameInitialize(HINSTANCE hInstance);
	void GameStart();				
	void GameEnd();
	//void GameActivate(HDC hDC, RECT rect);
	//void GameDeactivate(HDC hDC, RECT rect);
	void MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam);
	void MouseMove(int x, int y, WPARAM wParam);
	//void CheckKeyboard();
	//void KeyPressed(TCHAR cKey);
	//void GamePaint(RECT rect);
	void GameCycle(RECT rect);

private:
	// -------------------------
	// Datamembers
	// -------------------------

	Hero* m_pHero;
	
	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	ViralWars(const ViralWars& t);
	ViralWars& operator=(const ViralWars& t);
};
