//=============================================================================
//
// ゲームの処理 [game.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _GAME_H_		//二重インクルード防止
#define _GAME_H_

#include	"main.h"		//メイン
#include "animal.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;				//プレイヤー
class CAnimal;				//おとも
class CEnemy;				//エネミー
class CNumber;			//ナンバー
class CPause;				//ポーズ

//*****************************************************************************
// ゲームクラス
//*****************************************************************************
class CGame
{
public:
	CGame();																		//コンストラクタ
	~CGame();																	//デストラクタ
	HRESULT Init(void);													//初期化処理
	void Uninit(void);															//終了処理
	void Update(void);														//更新処理
	void Draw(void);															//描画処理

	//静的メンバ関数
	static CPlayer * GetPlayer(void) { return m_pPlayer; }													//プレイヤークラスに値を返す
	static CAnimal * GetAnimal(void) { return m_pAnimal; }												//おともクラスに値を返す
	static CEnemy * GetEnemy(void) { return m_pEnemy; }												//エネミークラスに値を返す
	static CNumber * GetNumber(void) { return m_pNumber; }											//スコアクラスに値を返す
	static CPause * GetPause(void) { return m_pPause; }													//ポーズクラスに値を返す

private:
	//静的メンバ変数
	static CPlayer * m_pPlayer;																							//プレイヤークラスの取得
	static CAnimal * m_pAnimal;																							//おともクラスの取得
	static CEnemy * m_pEnemy;																							//エネミークラスの取得
	static CNumber * m_pNumber;																						//スコアクラスの取得
	static CPause * m_pPause;																								//ポーズクラスの取得
	static CScore * m_pScore;																								//スコアクラスの取得
	static int m_nCntTime;																									//

};
#endif