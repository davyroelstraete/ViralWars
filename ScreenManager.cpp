#include "ScreenManager.h"

ScreenManager::ScreenManager():m_pMyOldScreen(NULL),
								m_pMyActiveScreen(NULL)
{
}
ScreenManager::~ScreenManager()
{
	DestroyObject(m_pMyOldScreen);
	DestroyObject(m_pMyActiveScreen);
}
bool ScreenManager::SwitchScreen(AbstractScreen* const newScreen)
{
	DestroyObject(m_pMyOldScreen);
	m_pMyOldScreen = m_pMyActiveScreen;

	m_pMyActiveScreen = newScreen;
	if(!m_pMyActiveScreen->Initialize()) return false;	

	return true;
}
void ScreenManager::UpdateScene(float dtime)
{
	if(m_pMyActiveScreen!=NULL)
		m_pMyActiveScreen->UpdateScene(dtime);
}
void ScreenManager::DrawScene()
{
	if(m_pMyActiveScreen!=NULL)
		m_pMyActiveScreen->DrawScene();
}