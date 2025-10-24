#pragma once

#include "CObject.h"

class CUI : public CObject
{
private:

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	CLONE(CUI);

public:
	CUI();
	~CUI();
};

