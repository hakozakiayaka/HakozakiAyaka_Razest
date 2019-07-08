//=============================================================================
//
// タイム処理 [time.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//シーン2D
#include "manager.h"			//マネージャー
#include "number.h"			//ナンバー
#include "time.h"					//タイム

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CTime::m_nTime = 0;
int CTime::m_nTimeData[MAX_TIME] = {};

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIMERIMIT		(60 * 10)

//=============================================================================
// コンストラクタ
//=============================================================================
CTime::CTime() : CScene(6)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apTime[nCntTime] = 0;
	}

	m_nTime = 0;
	m_nTimeState = TIMESTATE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTime::~CTime()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CTime * CTime::Create(void)
{
	CTime * pTime = NULL;

	if (pTime == NULL)
	{
		pTime = new CTime;
	}
	if (pTime != NULL)
	{
		pTime->Init();
	}

	return pTime;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTime::Init(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apTime[nCntTime] = new CNumber;
		m_apTime[nCntTime]->Init();
		m_apTime[nCntTime]->SetPosition(D3DXVECTOR3(590.0f, 40.0f, 0.0f), nCntTime);
	}

	m_nTimeState = TIMESTATE_NORMAL;
	m_nTime = TIMERIMIT;
	AddTime();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apTime[nCntTime]->Uninit();

		if (m_apTime[nCntTime] != NULL)
		{
			delete m_apTime[nCntTime];
			m_apTime[nCntTime] = NULL;
		}
	}

	//自分自身を破棄
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTime::Update(void)
{
	switch (m_nTimeState)
	{
	case TIMESTATE_NORMAL:
		break;

	case TIMESTATE_FINISH:
		m_nTime = 0;
		m_nTimeState = TIMESTATE_NONE;
		break;
	}

	if (m_nTimeState == TIMESTATE_NORMAL)
	{
		m_nTime--;

		if ((m_nTime % 60) == 0)
		{
			for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
			{
				AddTime();
				m_apTime[nCntTime]->Update();
				m_apTime[nCntTime]->SetNumber(m_nTimeData[nCntTime]);
			}

			if (m_nTime == 0)
			{
				m_nTimeState = TIMESTATE_FINISH;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apTime[nCntTime]->Draw();
	}
}

//=============================================================================
// タイムの処理
//=============================================================================
void CTime::AddTime(void)
{
	int nNum = 1000;
	int nNum1 = 100;
	int nCntTime = 0;
	int nTime;

	nTime = m_nTime / 60;			//1フレームの計算

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_nTimeData[nCntTime] = (nTime %  nNum) / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}