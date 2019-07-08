//=============================================================================
//
// シーン処理 [scene.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//2Dポリゴン
#include "bg.h"					//背景
#include "pause.h"				//ポーズ
#include "manager.h"			//マネージャー

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE						(80)			//ポリゴンの中心点からのサイズ

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CScene::m_nNumAll = 0;
bool CScene::m_bPause = false;
CScene * CScene::m_apScene[PRIORITY][MAX_DATA] = {};			//ポリゴンの生成

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			//オブジェクトの設定
			SetObjType(CScene::OBJTYPE_NONE);						//オブジェクトの種類の初期化
			m_apScene[nPriority][nCntScene] = this;					//自分を返す
			m_nID = nCntScene;													//生成された番号を固定する
			m_nPriority = nPriority;												//優先順位の番号を、m_nPriorityに格納する
			m_nNumAll++;															//ポリゴンの総数を加算
			break;
		}
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{	//何も書かない
}

//=============================================================================
// オブジェクトの破棄
//=============================================================================
void CScene::Release(void)
{
	int nID;				//IDを保存する
	int nPriority;		//優先順位の番号を保存

	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		nID = m_nID;
		nPriority = m_nPriority;								//元々ある変数に格納

		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;												//全体の総数から減らす
	}
}

//=============================================================================
// 全てのポリゴンの破棄
//=============================================================================
void CScene::ReleaseAll(void)
{	//全ての処理を終了する
	//ポリゴンの破棄
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				delete m_apScene[nCntPriority][nCntScene];
				m_apScene[nCntPriority][nCntScene] = NULL;
			}
		}
	}
}

//=============================================================================
// フェード以外終了処理
//=============================================================================
void CScene::ReleaseFadeAll(void)
{
	//ポリゴンの破棄
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				if (m_apScene[nCntPriority][nCntScene]->m_objType != OBJTYPE_FADE)
				{	//フェード以外残る
					delete m_apScene[nCntPriority][nCntScene];
					m_apScene[nCntPriority][nCntScene] = NULL;
				}
			}
		}
	}
}


//=============================================================================
// 全てのポリゴンの更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	CManager::MODE mode = CManager::GetMode();

	//ポリゴンの更新
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				if (mode == CManager::MODE_GAME)
				{	//モードがゲームだったら
					bool bPause = CPause::GetPause();
					if (bPause == false)
					{	//ポーズ状態じゃない
						m_apScene[nCntPriority][nCntScene]->Update();
					}
				}
				else
				{
					m_apScene[nCntPriority][nCntScene]->Update();
				}
			}
		}
	}
}

//=============================================================================
// 全てのポリゴンの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	//ポリゴンの描画
	for (int nCntPriotity = 0; nCntPriotity < PRIORITY; nCntPriotity++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCntPriotity][nCntScene] != NULL)
			{
				m_apScene[nCntPriotity][nCntScene]->Draw();
			}
		}
	}
}

//=============================================================================
// オブジェクトの設定
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// オブジェクトの種類を取得する処理
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
// シーンの取得
//=============================================================================
CScene * CScene::GetScene(int nPriority, int nIdx)
{
	return m_apScene[nPriority][nIdx];
}

//=============================================================================
// ポーズの設定
//=============================================================================
void CScene::SetPause(bool bPause)
{
	m_bPause = bPause;
}