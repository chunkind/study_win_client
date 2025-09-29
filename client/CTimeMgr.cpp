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
	// �ʴ� ī��Ʈ ���´���(�鸸����) GetTickCount -> ��� �ʴ� õ�̰� ��Ȯ������ �ʴ�.
	QueryPerformanceCounter(&m_llPrevCount);

	//old
	//QueryPerformanceFrequency(&m_llFrequency);
	//new
	// �ʴ� ī��Ʈ Ƚ��
	// GetTickCount�� �ʴ� 1000�̶�� ������ �־�������(1�ʰ��������� ī��Ʈ�� 1õ�� ���̳���)
	// QueryPerformanceCounter �� 1�� ���������� ī��Ʈ���� �󸶳� ���̰������� ���ؿ;��Ѵ�.
	QueryPerformanceFrequency(&m_llFrequency); // �ʴ� �󸶳� ���� �������
}

void CTimeMgr::update()
{
	//old
	/*wchar_t szBuffer[266] = {};
	swprintf_s(szBuffer, L"CurCount : %d, Frequency : %d", m_llCurCount, m_llFrequency);
	SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);*/

	//new
	// �� �����ӿ� �ɸ� �ð�
	QueryPerformanceCounter(&m_llCurCount);

	//new
	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�. (1�����Ӵ� ī��Ʈ��)
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

	//new
	// ����ī��Ʈ ���� ���簪���� ����(�������� ����� ���ؼ�)
	m_llPrevCount = m_llCurCount;

	//new
	// �ʴ� ������Ƚ�� -> m_dDT�� ����(1/m_dDT) => �ʹ� �̼��ѽð��̶� �Ҿ����ϴ�.
	// => 1�ʵ��� ���ȣ��Ǵ� ī��Ʈ�� ���¹���� �ϰڴ�.
	++m_iCallCount;
	m_dAcc += m_dDT; // DT ���� (DT:�����Ӱ� �ɸ��ð�) => �귯�� �ð�

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