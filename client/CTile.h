#pragma once

#include "CObject.h"

class CTexture;

class CTile : public CObject
{
private:
	CTexture* m_pTileTex;
	int m_iImgIdx;

public:
	void SetTexture(CTexture* _pTex)
	{
		m_pTileTex = _pTex;
	}

private:
	virtual void Update();
	virtual void Render(HDC _dc);

	//CLONE(CTile);
	CTile* Clone() { return new CTile(*this); }

public:
	CTile();
	~CTile();
};

