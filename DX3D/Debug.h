#pragma once

#define Debug DebugManager::GetInstance()

class DebugManager
{
	SINGLETON(DebugManager);
private:
	LPD3DXFONT			m_pFont;
	char				m_str[1024];

public:
	void Destroy();
	void InitText();
	void AddText(string str);
	void AddText(char* str);
	void AddText(float str);
	void AddText(double str);
	void AddText(int str);
	void AddText(DWORD str);
	void AddText(D3DXVECTOR3 str);
	void EndLine();
	void Print();
	void ShowMessageBox();
};

