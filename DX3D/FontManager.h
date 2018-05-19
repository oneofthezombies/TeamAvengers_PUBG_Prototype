#pragma once
#define g_pFontMgr FontManager::GetInstance()

namespace FONT
{
	enum FontType
	{
		NORMAL,
		QUEST
	};
}
class FontManager
{
	SINGLETON(FontManager)
private:
	map <FONT::FontType, LPD3DXFONT> m_mapFont;
public:
	LPD3DXFONT GetFont(FONT::FontType e);
	void Destroy();
};

