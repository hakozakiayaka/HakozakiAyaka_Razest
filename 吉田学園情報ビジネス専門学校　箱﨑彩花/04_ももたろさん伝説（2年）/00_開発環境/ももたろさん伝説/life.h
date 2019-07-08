//=============================================================================
//
// ライフ処理 [life.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _LIFE_H_			//二重インクルード防止
#define _LIFE_H_

#include	"main.h"		//メイン

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LIFE_TEX		"data/TEXTURE/momo.png"

//*****************************************************************************
// ライフクラス
//*****************************************************************************
class CLife : CScene2D
{
public:
	CLife();																							//コンストラクタ
	~CLife();																							//デストラクタ
	HRESULT Init(void);																		//初期化処理
	void Uninit(void);																				//終了処理
	void Update(void);																			//更新処理
	void Draw(void);																				//描画処理
	void SetLife(int nLifeDown);															//スコアの設定
	static int GetLife(void) { return m_nLife; }										//ライフクラスの取得

	//静的メンバ関数
	static CLife * Create(D3DXVECTOR3 pos, int nCntLife);				//ライフの生成
	static HRESULT Load(void);															//テクスチャを読み込む処理
	static void Unload(void);																	//テクスチャを破棄する処理

private:
	static int								m_nLife;												//ライフ
	D3DXVECTOR3					m_pos;													//位置

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9		m_pTexture;								// テクスチャへのポインタ
};

#endif