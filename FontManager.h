/*
03-04-08
*/

#ifndef FONTMANAGER_H_INCLUDED
#define FONTMANAGER_H_INCLUDED

#include "SpriteEngine.h"

/*
Creating a Font takes a load of time. This is why the fontmanager exists. As with the texturemanager, it makes sure fonts are only loaded ONCE to avoid
overhead. If u load a Font everytime u draw a string -> fps will drop hard... This manager also contains the simple drawstring functionality which is simply
a part of the LPD3DXFont object. I've made sure a default font is added when the engine boots. Otherwise u need to use AddFont to add other chosen fonts before
drawing strings with it will work!!
*/
class FontManager
{
public:
	struct FontParams
	{
		tstring fontID;
		tstring fontName;
		
		int size;

		bool italic;
	};

	FontManager();
	virtual ~FontManager();

	void OnLostDevice();
	void OnResetDevice();

	bool AddFont(const FontParams& fontParams);	
	void DrawString(const tstring& fontID, const tstring& text,float x,float y,const D3DXCOLOR& color);
	void DrawStringEx(const tstring& fontID, const tstring& drawText, RECT Rectangle, DWORD flags,const D3DXCOLOR& color);

private:
	void Destroy();

	map<tstring,LPD3DXFONT> m_MyFontMap;

	FontManager(const FontManager& t);
	FontManager& operator=(const FontManager& t);
};
#endif