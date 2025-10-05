#pragma once

class CCore
{
public:
	SINGLE(CCore)

private:
	HWND		m_hWnd;
	POINT		m_ptResolution;
	HDC			m_hDC;

	HBITMAP		m_hBit;
	HDC			m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	HDC GetMainDC() { return m_hDC; }
	void progress();

private:

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
};