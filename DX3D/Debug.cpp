#include "stdafx.h"
#include "Debug.h"

DebugManager::DebugManager()
{
	D3DXCreateFont(g_pDevice, 12, 6, FW_NORMAL, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("³ª´®°íµñ"), &m_pFont);
}

DebugManager::~DebugManager()
{
}

void DebugManager::Destroy()
{
	SAFE_RELEASE(m_pFont);
}

void DebugManager::InitText()
{
	m_str[0] = '\0';
}

void DebugManager::AddText(string str)
{
	strcat_s(m_str, str.data());
}

void DebugManager::AddText(char* str)
{
	strcat_s(m_str, str);
}

void DebugManager::AddText(float str)
{
	strcat_s(m_str, to_string(str).data());
}

void DebugManager::AddText(double str)
{
	strcat_s(m_str, to_string(str).data());
}

void DebugManager::AddText(int str)
{
	strcat_s(m_str, to_string(str).data());
}

void DebugManager::AddText(DWORD str)
{
	strcat_s(m_str, to_string(str).data());
}

void DebugManager::AddText(D3DXVECTOR3 str)
{
	strcat_s(m_str, (to_string(str.x) + " , " + to_string(str.y) + " , " + to_string(str.z)).c_str());
}

void DebugManager::EndLine()
{
	if (strlen(m_str) == 0) return;

	strcat_s(m_str, "\n");
}

void DebugManager::Print()
{
	RECT rc;
	SetRect(&rc, 8, 8, 8, 8);
#ifdef UNICODE
	m_pFont->DrawText(NULL, CA2W(m_str), strlen(m_str), &rc,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(0, 255, 255));
#else
	m_pFont->DrawText(NULL, (m_str), strlen(m_str), &rc,
		DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(0, 255, 255));
#endif 
	
}

void DebugManager::ShowMessageBox()
{
#ifdef UNICODE
	MessageBox(NULL, CA2W(m_str), _T("DEBUG"), MB_OK);
#else
	MessageBox(NULL, m_str, _T("DEBUG"), MB_OK);
#endif 
}
