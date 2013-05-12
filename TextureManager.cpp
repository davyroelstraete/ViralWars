#include "TextureManager.h"

class DestroyAllModelTextures{
public:
	void operator()(pair<tstring, LPDIRECT3DTEXTURE9> dePair){
		dePair.second->Release();
	}
};
TextureManager::TextureManager(){

}
TextureManager::~TextureManager(){
	for_each(m_MyTextureMap.begin(), m_MyTextureMap.end(), DestroyAllModelTextures());
}
const LPDIRECT3DTEXTURE9 TextureManager::CreateTexture(const tstring& textureFileName){
	map<tstring , LPDIRECT3DTEXTURE9>::iterator checkIt = m_MyTextureMap.find(textureFileName);
	if( checkIt == m_MyTextureMap.end()){
		LPDIRECT3DTEXTURE9 newTex;
		if(FAILED(D3DXCreateTextureFromFile(SPRITE_ENGINE->GetD3dDevice(), textureFileName.c_str(), &newTex)))
			return NULL;
		m_MyTextureMap.insert(make_pair(textureFileName, newTex));
		return newTex;
	}else{
		return (*checkIt).second;
	}
}