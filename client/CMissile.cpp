#include "Pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_fTheta(PI / 3.f)
	, m_vDir(Vec2(1.f, -1.f))
{
	m_vDir.Normalize();

	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}

CMissile::~CMissile()
{

}

void CMissile::Update()
{
	Vec2 vPos = GetPos();

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y -= 600.f * m_vDir.y * fDT;

	SetPos(vPos);
}

void CMissile::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

	Ellipse(_dc, (int)(vRenderPos.x - vScale.x / 2.f), (int)(vRenderPos.y - vScale.y / 2.f)
		, (int)(vRenderPos.x + vScale.x / 2.f), (int)(vRenderPos.y + vScale.y / 2.f));

	ComponentRender(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}