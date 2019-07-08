//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _MANEGER_H_		//二重インクルード防止
#define _MANEGER_H_

#include	"main.h"				//メイン
#include "score.h"				//スコア

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;					//レンダリング
class CInputKeyboard;		//キーボード
class CDirectXInput;			//ジョイコン
class CFade;						//フェード
class CTitle;							//タイトル
class CTutorial;					//チュートリアル
class CGame;						//ゲーム
class CResult;						//リザルト
class CRanking;					//ランキング
class CSound;						//サウンド
class CScore;						//スコア

//*****************************************************************************
// マネージャークラス
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{	//モードの種類
		MODE_TITLE = 0,																										//タイトル
		MODE_TUTORIAL,																										//チュートリアル
		MODE_GAME,																												//ゲーム
		MODE_GAMECLEAR,																									//ゲームクリア
		MODE_GAMEOVER,																									//ゲームオーバー
		MODE_RANKING,																										//ランキング
		MODE_MAX																												//モードの最大数
	} MODE;

	CManager();																													//コンストラクタ
	~CManager();																													//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);						//初期化処理
	void Uninit(void);																												//終了処理
	void Update(void);																											//更新処理
	void Draw(void);																												//描画処理

	//静的メンバ関数
	static void SetMode(MODE mode);																				//モードの設定処理
	static void SetScore(int nScore) { m_nScore = nScore; }												//スコアの設定処理

	//静的メンバ変数
	static CRenderer * GetRenderer(void) { return m_pRenderer; }										//レンダリングクラスに値を返す
	static CInputKeyboard * GetInputKeyboard(void) { return m_pInputKeyboard; }			//キーボードクラスに値を返す
	static CDirectXInput * GetDirectXInput(void) { return m_pDirectXInput; }					//ジョイコンクラスに値を返す
	static CFade * GetFade(void) { return m_pFade; }															//フェードクラスに値を返す
	static CTitle * GetTitle(void) { return m_pTitle; }															//タイトルクラスに値を返す
	static CTutorial * GetTutorial(void) { return m_pTutorial; }												//チュートリアルクラスに値を返す
	static CGame * GetGame(void) { return m_pGame; }														//ゲームクラスに値を返す
	static CResult * GetResult(void) { return m_pResult; }													//リザルトクラスに値を返す
	static CRanking * GetRanking(void) { return m_pRanking; }											//ランキングクラスに値を返す
	static CSound * GetSound(void) { return m_pSound; }													//サウンドクラスに値を返す
	static MODE GetMode(void) { return m_mode; }															//モードの取得
	static int GetScore(void) { return m_nScore; }																//スコアの取得

	static int m_nHighScore[RANKING_NUMBER];

private:
	//静的メンバ変数
	static MODE m_mode;																									//モードの設定
	static CRenderer * m_pRenderer;																					//レンダリングクラスの取得
	static CInputKeyboard * m_pInputKeyboard;																	//キーボードクラスの取得
	static CDirectXInput * m_pDirectXInput;																		//ジョイコンクラスの取得
	static CFade * m_pFade;																									//フェードクラスの取得
	static CTitle * m_pTitle;																									//タイトルクラスの取得
	static CTutorial * m_pTutorial;																						//チュートリアルクラスの取得
	static CGame * m_pGame;																								//ゲームクラスの取得
	static CResult * m_pResult;																							//リザルトクラスの取得
	static CRanking * m_pRanking;																						//ランキングクラスの取得
	static CSound * m_pSound;																							//サウンドクラスの取得
	static int  m_nScore;

};

#endif