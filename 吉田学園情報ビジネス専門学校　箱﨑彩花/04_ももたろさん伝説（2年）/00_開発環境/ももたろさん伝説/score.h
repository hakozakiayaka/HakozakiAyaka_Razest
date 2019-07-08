//=============================================================================
//
// スコア処理 [score.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _SCORE_H_		//二重インクルード防止
#define _SCORE_H_

#include	"main.h"		//メイン
#include	"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScore;
class CNumber;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DUGIT_NUMBER		(8)
#define RANKING_NUMBER	(5)

//*****************************************************************************
// スコアクラス
//*****************************************************************************
class CScore : public CScene
{
public:
	typedef enum
	{
		SCOREMODE_NONE = 0,
		SCOREMODE_GAME,
		SCOREMODE_RANKING,
		SCOREMODE_MAX
	} SCOREMODE;

	CScore();																		//コンストラクタ
	virtual ~CScore();														//デストラクタ
	virtual HRESULT Init(void) = 0;									//初期化処理
	virtual void Uninit(void) = 0;										//終了処理
	virtual void Update(void) = 0;										//更新処理
	virtual void Draw(void) = 0;										//描画処理

	void SetScore(int nScore);											//スコアの設定
	int GetScore(void);														//スコアを取得

	//静的メンバ関数
	static void AddScore(int nValue);								//スコアの加算
	static CScore * Create(SCOREMODE mode);				//スコアの生成

protected:
	static int m_nScore;													//スコアをいれる
	static int m_nScoreData[DUGIT_NUMBER];				//計算用の変数
};

//*****************************************************************************
// ゲームのスコアクラス
//*****************************************************************************
class CScoreGame : public CScore
{
public:
	CScoreGame();															//コンストラクタ
	~CScoreGame();															//デストラクタ
	HRESULT Init(void);													//初期化処理
	void Uninit(void);															//終了処理
	void Update(void);														//更新処理
	void Draw(void);															//描画処理

private:
	CNumber * m_apNumber[DUGIT_NUMBER];			//[ スコアの桁数 ]
};

//*****************************************************************************
// ランキングのスコアクラス
//*****************************************************************************
class CScoreRanking : public CScore
{
public:
	CScoreRanking();														//コンストラクタ
	~CScoreRanking();														//デストラクタ
	HRESULT Init(void);													//初期化処理
	void Uninit(void);															//終了処理
	void Update(void);														//更新処理
	void Draw(void);															//描画処理
	void SetRanking(int nScore);											//スコアの設定

private:
	CNumber * m_apNumber[RANKING_NUMBER][DUGIT_NUMBER];			//[ スコアの桁数 ]
	int m_nChange;
	int m_nChange2;
	int m_nRankingData[RANKING_NUMBER][DUGIT_NUMBER];
	int m_nNewRank;																							//新しいスコアを点滅
};

#endif