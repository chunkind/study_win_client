#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"
#include <tchar.h>

CTimeMgr::CTimeMgr()
	//old
	/*: m_llCurCount{}
	, m_llFrequency{}*/
	//new
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)

{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	//old
	//QueryPerformanceCounter(&m_llCurCount);
	//new
	// 초당 카운트 세는단위(백만단위) GetTickCount -> 얘는 초당 천이고 정확하지도 않다.
	QueryPerformanceCounter(&m_llPrevCount);

	//old
	//QueryPerformanceFrequency(&m_llFrequency);
	//new
	// 초당 카운트 횟수
	// GetTickCount는 초당 1000이라는 기준이 주어졌지만(1초가벌어지면 카운트가 1천이 차이난다)
	// QueryPerformanceCounter 는 1가 벌어졌을때 카운트값이 얼마나 차이가나는지 구해와야한다.
	QueryPerformanceFrequency(&m_llFrequency); // 초당 얼마나 자주 빈번한지
}

void CTimeMgr::update()
{
	//old
	/*wchar_t szBuffer[266] = {};
	swprintf_s(szBuffer, L"CurCount : %d, Frequency : %d", m_llCurCount, m_llFrequency);
	SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);*/

	//new
	// 한 프레임에 걸린 시간
	QueryPerformanceCounter(&m_llCurCount);

	//new
	// 이전 프레임의 카운팅과, 현재 프레임 카운팅 값의 차이를 구한다. (1프레임당 카운트수)
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	//new
	// 이전카운트 값을 현재값으로 갱신(다음번에 계산을 위해서)
	m_llPrevCount = m_llCurCount;

	//new
	// 초당 프레임횟수 -> m_dDT의 역수(1/m_dDT) => 너무 미세한시간이라 불안정하다.
	// => 1초동안 몇번호출되는 카운트로 새는방법을 하겠다.
	++m_iCallCount;
	m_dAcc += m_dDT; // DT 누적 (DT:프레임간 걸린시간) => 흘러간 시간

	//new
	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS: %d, DT: %d", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}