#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CObject.h"

//old
//CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	//old
	//g_obj.SetPos(Vec2((float)(m_ptResolution.x / 2), (float)(m_ptResolution.y / 2)));
	//g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void CCore::progress()
{
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();

	//old
	//update();
	//render();
	//new
	// ȭ�� Ŭ����
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	CSceneMgr::GetInst()->update();
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);
}

//old
//void CCore::update()
//{
//	Vec2 vPos = g_obj.GetPos();
//
//	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
//	{
//		vPos.x -= 100.f * fDT;
//	}
//
//	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
//	{
//		vPos.x += 100.f * fDT;
//	}
//
//	g_obj.SetPos(vPos);
//}

//old
//void CCore::render()
//{
//	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
//
//	Vec2 vPos = g_obj.GetPos();
//	Vec2 vScale = g_obj.GetScale();
//
//	Rectangle(m_memDC
//		, int(vPos.x - vScale.x / 2.f)
//		, int(vPos.y - vScale.y / 2.f)
//		, int(vPos.x + vScale.x / 2.f)
//		, int(vPos.y + vScale.y / 2.f));
//
//	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
//		, m_memDC, 0, 0, SRCCOPY);
//}