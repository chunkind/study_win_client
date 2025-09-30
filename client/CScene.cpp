#include "pch.h"
#include "CScene.h"
//new
#include "CObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	//new
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++i)
		{
			delete m_arrObj[i][j];
		}
	}
}

//new
void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++i)
		{
			m_arrObj[i][j]->update();
		}
	}
}

//new
void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++i)
		{
			m_arrObj[i][j]->render(_dc);
		}
	}
}