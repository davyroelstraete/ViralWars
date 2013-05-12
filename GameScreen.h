/*
Game screen
*/
#pragma once

#include "Hero.h"
#include "EnemyList.h"
#include "Entity.h"
#include "AbstractScreen.h"

/*
This shows a example of how to use sprites and animate them
*/
class GameScreen : public AbstractScreen
{
public:
	GameScreen();
	virtual ~GameScreen();

	bool Initialize();

	void UpdateScene(float dtime);
	void DrawScene();

private:
    Hero* m_pHero;

	GameScreen(const GameScreen& t);
	GameScreen& operator=(const GameScreen& t);
};