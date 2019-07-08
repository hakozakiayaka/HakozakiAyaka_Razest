//=============================================================================
//
// 爆発の処理 [explosion.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _EXPLOSION_H_		//二重インクルード防止
#define _EXPLOSION_H_

#include	"main.h"				//メイン

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE								(80)			//ポリゴンの中心点からのサイズ
#define EXPLOSION_SPEED		(10)			//爆発のスピード
#define MAX_BULLET				(256)		//弾の最大数

//テクスチャ
#define EXPLOSION_NAME		"data/TEXTURE/explosion000.png"

//*****************************************************************************
// 爆発クラス
//*****************************************************************************
class CExplosion : public CScene2D
{
public:
	CExplosion();																//コンストラクタ
	~CExplosion();															//デストラクタ
	HRESULT Init(void);													//初期化処理
	void Uninit(void);															//終了処理
	void Update(void);														//更新処理
	void Draw(void);															//描画処理

	//静的メンバ関数
	static CExplosion * Create(D3DXVECTOR3 pos);		//オブジェクトの生成
	static HRESULT Load(void);										//テクスチャを読み込む処理
	static void Unload(void);												//テクスチャを破棄する処理

private:
	int												m_nCntAnim;			//アニメーションのカウンター
	int												m_nPatternAnim;		//アニメーションのNo.

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture;				//共有テクスチャへのポインタ
};
#endif