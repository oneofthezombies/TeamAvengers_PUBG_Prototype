#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(char * fullPath)
{
	if (fullPath == NULL) return NULL;

	return GetTexture(string(fullPath));
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(string fullPath)
{
	if (fullPath == "") return NULL;

	if (m_mapTexture.find(fullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileA(g_pDevice, fullPath.c_str(),
			&m_mapTexture[fullPath]);
	}
	return m_mapTexture[fullPath];
}

void TextureManager::Destroy()
{
	for (auto it : m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTexture.clear();
}
