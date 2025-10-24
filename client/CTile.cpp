#include "Pch.h"
#include "CTile.h"

CTile::CTile()
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{

}

void CTile::Update()
{

}

void CTile::Render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vRenderPos.x)
		, int(vRenderPos.y)
		, int(vRenderPos.x + vScale.x)
		, int(vRenderPos.y + vScale.y));
}