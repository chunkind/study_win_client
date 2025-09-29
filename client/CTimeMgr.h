#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr)

private:
	LARGE_INTEGER	m_llCurCount;
	//new
	LARGE_INTEGER	m_llPrevCount;

	LARGE_INTEGER	m_llFrequency;

//new
	double			m_dDT; // ������ ���� �ð���
	double			m_dAcc; // 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount; // �Լ� ȣ�� Ƚ�� üũ
	UINT			m_iFPS; // �ʴ� ȣ�� Ƚ��

public:
	void init();
	void update();
};