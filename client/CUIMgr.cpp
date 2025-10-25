#include "Pch.h"
#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		pUI = GetTargetedUI(pUI);

		if (nullptr != pUI)
		{
			pUI->MouseLbtnDown();
			pUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pUI->MouseLbtnUp();

			if (pUI->m_bLbtnDown)
			{
				pUI->MouseLBtnClicked();
			}

			pUI->m_bLbtnDown = false;
		}
	}
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CUI* pTargetUI = nullptr;
	list<CUI*> queue;

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMouseOn())
		{
			pTargetUI = pUI;
		}
		else
		{
			if (bLbtnAway)
			{
				pUI->m_bLbtnDown = false;
			}
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}

	return pTargetUI;
}
