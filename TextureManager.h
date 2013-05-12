/**/

#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include "SpriteEngine.h"

/*
Texturemanager functionality isn't complex but handy. When creating a new texture, use the "CreateTexture" function. Internally it'll check wether
the filename is already in the textureMap. If so it'll return a pointer to the texture stored in memory. If not it'll create the new texture and put
it in the map and return the pointer. This makes sure that textures will never be loaded into memory twice! Also de manager will remove all textures from
memory itself! Other objects only hold pointers to the texture they need in memory. The textureManager handles de memory
*/
class TextureManager{
private:
	map<tstring, LPDIRECT3DTEXTURE9> m_MyTextureMap;

	TextureManager(const TextureManager& t);
	TextureManager& operator=(const TextureManager& t);
public:
	TextureManager();
	virtual	~TextureManager();

	const LPDIRECT3DTEXTURE9  CreateTexture(const tstring& textureFileName);
};

#endif

