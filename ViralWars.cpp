//-----------------------------------------------------------------
// Game File
// C++ Source - ViralWars.cpp - version 2007 v3_01													
// Copyright Kevin Hoefman - kevin.hoefman@howest.be
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "ViralWars.h"																				

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define GAME_ENGINE (GameEngine::GetSingleton())

//-----------------------------------------------------------------
// ViralWars methods																				
//-----------------------------------------------------------------

ViralWars::ViralWars()																						
{
	// nothing to create
}

ViralWars::~ViralWars()																						
{
	// nothing to destroy
}

// TODO: schrijf hier de implementatie van de functies die je uit commentaar gehaald hebt in de header file. 


 void ViralWars::GameInitialize(HINSTANCE hInstance)			
 {
	AbstractGame::GameInitialize(hInstance);

	GAME_ENGINE->SetTitle(_T("ViralWars"));	
	GAME_ENGINE->RunGameLoop(true);

	// Stel de optionele waarden in
	GAME_ENGINE->SetWidth(1440);
	GAME_ENGINE->SetHeight(900);
    GAME_ENGINE->SetFrameRate(60);
	GAME_ENGINE->ShowMousePointer(false);
 }

 void ViralWars::GameStart()
 {
	 m_pHero = new Hero(IDI_HERO,50,150);
	 EnemyList::GetSingleton()->Init(m_pHero);
	 Enemy* test = new SlimeBig(Vector2(1000,500), Vector2(180), m_pHero);
	 //Enemy* test2 = new SlimeSmall(Vector2(1100,50), Vector2(180), m_pHero);
	 EnemyList::GetSingleton()->Add(test);
	 //EnemyList::GetSingleton()->Add(test2);


 }			
 void ViralWars::GameEnd()
 {
	 delete m_pHero;
	 ParticleList::GetSingleton()->Clear();
 }
 void ViralWars::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
 {
	 m_pHero->HandleMouseClicks(isLeft, isDown);
 }
 void ViralWars::MouseMove(int x, int y, WPARAM wParam)
 {
	 m_pHero->HandleMouse(x, y);
 }

 void ViralWars::GameCycle(RECT rect)
 {
	 GAME_ENGINE->DrawSolidBackground(RGB(255,255,255));
	 EnemyList::GetSingleton()->Tick(rect);
	 EnemyList::GetSingleton()->Draw();
	 m_pHero->Tick(rect);
	 m_pHero->Draw();

	 ParticleList::GetSingleton()->Tick();
	 ParticleList::GetSingleton()->Draw();

	 tstringstream buffer;
	 buffer << _T("Size: ") << EnemyList::GetSingleton()->GetNumberOfLivingEnemies();
	 GAME_ENGINE->DrawString(buffer.str(),10,10);
 }




