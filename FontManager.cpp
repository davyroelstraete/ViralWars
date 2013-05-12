#include "FontManager.h"

FontManager::FontManager()
{
	FontParams defaultFont;

	defaultFont.fontName = _T("Arial");
	defaultFont.fontID = _T("Default");
	defaultFont.size = 20;
	defaultFont.italic = false;

	AddFont(defaultFont);
}
FontManager::~FontManager()
{
	Destroy();
}
class DestroyFonts
{
public:
	void operator()(pair<tstring, LPD3DXFONT> dePair){
		ReleaseObject(dePair.second);
	}
};
void FontManager::Destroy()
{
	for_each(m_MyFontMap.begin(), m_MyFontMap.end(), DestroyFonts());

	m_MyFontMap.clear();
}
class OnLostFonts
{
public:
	void operator()(pair<tstring, LPD3DXFONT> dePair)
	{
		dePair.second->OnLostDevice();
	}
};
void FontManager::OnLostDevice()
{
	for_each(m_MyFontMap.begin(), m_MyFontMap.end(), OnLostFonts());
}
class OnResetFonts
{
public:
	void operator()(pair<tstring, LPD3DXFONT> dePair)
	{
		dePair.second->OnResetDevice();
	}
};
void FontManager::OnResetDevice()
{
	for_each(m_MyFontMap.begin(), m_MyFontMap.end(), OnResetFonts());	
}
bool FontManager::AddFont(const FontParams& fontParams)
{
	LPD3DXFONT temp;

	if(FAILED(D3DXCreateFont(SPRITE_ENGINE->GetD3dDevice(),
					fontParams.size,
					NULL,
					FW_NORMAL,
					1,
					fontParams.italic,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH || FF_DONTCARE,
					fontParams.fontName.c_str(),
					&temp)
					))
	{
		return false;
	}

	m_MyFontMap.insert(make_pair(fontParams.fontID, temp));

	return true;
}
void FontManager::DrawStringEx(const tstring& fontID, const tstring& drawText, RECT Rectangle, DWORD flags,const D3DXCOLOR& color){
	
	if(m_MyFontMap.empty())
	{
		MessageBox(SPRITE_ENGINE->GetMainWnd(),_T("No fonts were created."),NULL,NULL);
		SPRITE_ENGINE->ShutDownEngine();

		return;
	}

	if(m_MyFontMap.find(fontID) == m_MyFontMap.end())m_MyFontMap.find(_T("Default"))->second->DrawText(NULL,drawText.c_str(),-1,&Rectangle,flags,color);
	else m_MyFontMap.find(fontID)->second->DrawText(NULL,drawText.c_str(),-1,&Rectangle,flags,color);
}
void FontManager::DrawString(const tstring& fontID, const tstring& text,float x,float y,const D3DXCOLOR& color)
{
	if(m_MyFontMap.empty())
	{
		MessageBox(SPRITE_ENGINE->GetMainWnd(),_T("No fonts were created."),NULL,NULL);
		SPRITE_ENGINE->ShutDownEngine();

		return;
	}

	RECT position;
	position.left=static_cast<long>(x);
	position.top=static_cast<long>(y);
	position.right=static_cast<long>(SPRITE_ENGINE->GetBackBufferWidth());
	position.bottom=static_cast<long>(SPRITE_ENGINE->GetBackBufferHeight());
	
	if(m_MyFontMap.find(fontID) == m_MyFontMap.end()) m_MyFontMap.find(_T("Default"))->second->DrawText(NULL,text.c_str(),-1,&position,DT_LEFT | DT_TOP,color);
	else m_MyFontMap.find(fontID)->second->DrawText(NULL,text.c_str(),-1,&position,DT_LEFT | DT_TOP,color);	
}