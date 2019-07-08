//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _EXFFECT_H_		//二重インクルード防止
#define _EXFFECT_H_

#include	"main.h"			//メイン

//*****************************************************************************
// エフェクトクラス
//*****************************************************************************
class CEffect : public CScene2D
{
public:
	CEffect(int nPriority);																					//コンストラクタ
	~CEffect();																									//デストラクタ
	HRESULT Init(void);																					//初期化処理
	void Uninit(void);																							//終了処理
	void Update(void);																						//更新処理
	void Draw(void);																							//描画処理

	//静的メンバ関数
	static CEffect * Create(D3DXVECTOR3 pos, D3DXCOLOR col);				//オブジェクトの生成
	static HRESULT Load(void);																		//テクスチャを読み込む処理
	static void Unload(void);																				//テクスチャを破棄する処理

private:
	D3DXCOLOR								m_col;														// 色
	int												m_nLife;													// 表示時間(寿命)
	float												m_nSize;													//エフェクトのサイズ

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture;												//共有テクスチャへのポインタ
};
#endif