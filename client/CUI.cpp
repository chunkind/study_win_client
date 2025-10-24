#include "Pch.h"
#include "CUI.h"

CUI::CUI()
{

}

CUI::~CUI()
{

}

void CUI::Update()
{

}

void CUI::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y)
	);
}