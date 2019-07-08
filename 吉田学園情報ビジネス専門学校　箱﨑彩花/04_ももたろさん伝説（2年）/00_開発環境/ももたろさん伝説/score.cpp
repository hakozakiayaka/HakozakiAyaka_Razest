//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include <time.h>
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "manager.h"			//マネージャー
#include "number.h"			//ナンバー
#include "score.h"				//スコア

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CScore::m_nScore = 0;
int CScore::m_nScoreData[DUGIT_NUMBER] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore() : CScene(6)
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//スコアの初期化
		m_nScoreData[nCntScore] = NULL;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore()
{
	m_nScore = 0;
}

//=============================================================================
// 生成処理
//=============================================================================
CScore * CScore::Create(SCOREMODE mode)
{
	CScore * pScore = NULL;

	switch (mode)
	{
	case SCOREMODE_GAME:							//ゲーム
		pScore = new CScoreGame;
		pScore->Init();
		break;

	case SCOREMODE_RANKING:					//ランキング
		pScore = new CScoreRanking;
		pScore->Init();
		break;
	}

	return pScore;
}

//=============================================================================
// 設定処理
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//=============================================================================
// スコアの取得
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

#if 1
//=============================================================================
// スコアの加算
//=============================================================================
void CScore::AddScore(int nValue)
{
	int nNum = 100000000;			//桁いじったらかえる
	int nNum1 = 10000000;			//桁いじったらかえる
	int nCntScore;

	m_nScore += nValue;

	for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		m_nScoreData[nCntScore] = m_nScore %  nNum / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}

//=============================================================================
// ゲームのコンストラクタ
//=============================================================================
CScoreGame::CScoreGame()
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//ゲーム時のスコア初期化
		m_apNumber[nCntScore] = NULL;
	}
}

//=============================================================================
// ゲームのデストラクタ
//=============================================================================
CScoreGame::~CScoreGame()
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//ゲームを繰り返したときにスコアが残らないようにする為
		m_apNumber[nCntScore] = 0;
	}
}

//=============================================================================
// ゲームの初期化処理
//=============================================================================
HRESULT CScoreGame::Init(void)
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		m_apNumber[nCntScore] = new CNumber;
		m_apNumber[nCntScore]->Create();																								//生成処理
		m_apNumber[nCntScore]->Init();																									//初期化
		m_apNumber[nCntScore]->SetPosition(D3DXVECTOR3(900.0f, 40.0f, 0.0f), nCntScore);			//ゲームスコアの位置を設定
	}
	return S_OK;
}

//=============================================================================
// ゲームの終了処理
//=============================================================================
void CScoreGame::Uninit(void)
{
	//ゲームが終了したらランキングにスコアを渡す
	CManager::SetScore(m_nScore);

	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//終了処理
		m_apNumber[nCntScore]->Uninit();

		if (m_apNumber[nCntScore] != NULL)
		{
			delete m_apNumber[nCntScore];			//メモリの開放
			m_apNumber[nCntScore] = NULL;
		}
	}

	//自分自身を破棄
	CScene::Release();
}

//=============================================================================
// ゲームの更新処理
//=============================================================================
void CScoreGame::Update(void)
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//テクスチャの更新
		m_apNumber[nCntScore]->SetNumber(m_nScoreData[nCntScore]);
	}
}

//=============================================================================
// ゲームの描画処理
//=============================================================================
void CScoreGame::Draw(void)
{
	for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{	//描画処理
		m_apNumber[nCntScore]->Draw();
	}
}

//=============================================================================
// ランキングのコンストラクタ
//=============================================================================
CScoreRanking::CScoreRanking()
{
	//rand使う
	srand((unsigned int)time(0));

	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{
			m_apNumber[nCntRank][nCntScore] = NULL;
			m_nRankingData[nCntRank][nCntScore] = NULL;
		}
	}

	//計算用の変数の初期化
	m_nChange = 0;
	m_nChange2 = 0;
	m_nNewRank = 5;
}

//=============================================================================
// ランキングのデストラクタ
//=============================================================================
CScoreRanking::~CScoreRanking()
{
}

//=============================================================================
// ランキングの初期化処理
//=============================================================================
HRESULT CScoreRanking::Init(void)
{
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{
			m_apNumber[nCntRank][nCntScore] = CNumber::Create();																											//ナンバーの生成
			m_apNumber[nCntRank][nCntScore]->Init();																																	//初期化
			m_apNumber[nCntRank][nCntScore]->SetPosition(D3DXVECTOR3(500.0f, 180.0f + (110.0f * nCntRank), 0.0f), nCntScore);		//位置設定
		}
	}

	m_nScore = 0;

	//スコアの呼び出す
	SetRanking(CManager::GetScore());

	return S_OK;
}

//=============================================================================
// ランキングの終了処理
//=============================================================================
void CScoreRanking::Uninit(void)
{
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{
			if (m_apNumber[nCntRank][nCntScore] != NULL)
			{	//終了処理
				m_apNumber[nCntRank][nCntScore]->Uninit();
				delete m_apNumber[nCntRank][nCntScore];			//メモリの開放
				m_apNumber[nCntRank][nCntScore] = NULL;
			}
		}
	}

	//自分自身を破棄
	CScene::Release();
}

//=============================================================================
// ランキングの更新処理
//=============================================================================
void CScoreRanking::Update(void)
{
	//rand使うため
	int nColRand = rand() % 10 + 1;
	float fColRand = nColRand * 0.1f;

	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{
			if (m_nNewRank < 5)
			{
				m_apNumber[m_nNewRank][nCntScore]->SetColor(D3DXCOLOR(1.0f, fColRand, fColRand, 1.0f));
			}
		}
	}
}

//=============================================================================
// ランキングの描画処理
//=============================================================================
void CScoreRanking::Draw(void)
{
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{	//描画処理
			m_apNumber[nCntRank][nCntScore]->Draw();
		}
	}
}

//=============================================================================
// ランキングの設定処理
//=============================================================================
void CScoreRanking::SetRanking(int nScore)
{
	int nNum = 100000000;
	int nNum1 = 10000000;

	m_nScore = nScore;

	//ハイスコアと現在のハイスコアを比べる
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		if (CManager::m_nHighScore[nCntRank] < m_nScore)
		{
			m_nChange = CManager::m_nHighScore[nCntRank];		//前回のハイスコアを仮置き
			CManager::m_nHighScore[nCntRank] = m_nScore;			//仮置きのハイスコアと比べて、今回のハイスコアを代入

			//順位の更新を記録
			m_nNewRank = nCntRank;

			//順位の入れ替え
			for (int nCntSortRank = nCntRank + 1; nCntSortRank < RANKING_NUMBER; nCntSortRank++)
			{
				m_nChange2 = CManager::m_nHighScore[nCntSortRank];				//書き換えた順位の次の順位を仮置き
				CManager::m_nHighScore[nCntSortRank] = m_nChange;				//空いたところに1つ上の順位を代入
				m_nChange = m_nChange2;																//最終的なスコアの代入
			}
			break;
		}
	}

	//ランキング画面のスコア更新
	for (int nCntRank = 0; nCntRank < RANKING_NUMBER; nCntRank++)
	{
		for (int nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
		{
			m_nRankingData[nCntRank][nCntScore] = (CManager::m_nHighScore[nCntRank] % nNum) / nNum1;
			m_apNumber[nCntRank][nCntScore]->SetNumber(m_nRankingData[nCntRank][nCntScore]);

			nNum = nNum / 10;
			nNum1 = nNum1 / 10;

			if (nCntScore == DUGIT_NUMBER - 1)
			{	//段数終わったら初期化する
				nNum = 100000000;
				nNum1 = 10000000;
			}
		}
	}

	//スコアの初期化
	CManager::SetScore(0);
}

#endif