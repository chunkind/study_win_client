#pragma once

#include "CObject.h"
#include "SelectGDI.h"

class CUI : public CObject
{
private:
	vector<CUI*> m_vecChildUI;
	CUI* m_pParentUI;
	Vec2 m_vFinalPos;
	bool m_bCamAffected;
	bool m_bMouseOn;
	bool m_bLbtnDown;

public:
	Vec2 GetFinalPos() { return m_vFinalPos; }

	CUI* GetParent() { return m_pParentUI; }
	bool IsMouseOn() { return m_bMouseOn; }
	void AddChild(CUI* _pUI)
	{
		m_vecChildUI.push_back(_pUI);
		_pUI->m_pParentUI = this;
	}
	const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

public:
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

private:
	void UpdateChild();
	void FinalUpdateChild();
	void RenderChild(HDC _dc);
	void MouseOnCheck();

public:
	virtual void MouseOn();

	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLBtnClicked();

	CLONE(CUI);

public:
	CUI(bool _bCamAff);
	virtual ~CUI();

	friend class CUIMgr;
};

