//=============================================================================
//
// シーン2D処理 [scene2D.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _SCENE2D_H_		//二重インクルード防止
#define _SCENE2D_H_

#include	"main.h"				//メイン

//*****************************************************************************
// オブジェクト2Dクラス
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D();																										//デフォルトコンストラクタ
	CScene2D(int nPriority);																						//オーバーロードされたコンストラクタ
	~CScene2D();																										//デストラクタ
	HRESULT Init(void);																							//初期化処理
	void Uninit(void);																									//終了処理
	void Update(void);																								//更新処理
	void Draw(void);																									//描画処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);										//テクスチャを割り当てる為の処理

	//各処理の設定
	void SetPosition(D3DXVECTOR3 pos);																//ポリゴンの設定
	void SetAnimation(float uv, int nPatternAnim);													//アニメーションの設定
	void SetBgMove(int nCntBg, float fScrollSpeed);												//背景を動かす処理
	void SetSize(float fWidth, float fHeight);															//サイズを変更する処理
	void SetColor(D3DXCOLOR col);																		//色の設定
	void SetLife(float fWidth, float fHeight);																//ライフ処理

	//各変数の取得
	D3DXVECTOR3 GetPosition(void) { return m_pos; }											//位置を取得
	int GetPatternAnim(void) { return m_nPatternAnim; }										//パターンアニメーションの取得

	//静的メンバ関数
	static CScene2D *Create();																				//オブジェクトの生成

	D3DXVECTOR3								m_move;														//ポリゴンの移動量

private:
	D3DXVECTOR3								m_pos;															// ポリゴンの位置
	D3DXCOLOR									m_col;															//色
	float													m_fHeight;													//高さ
	float													m_fWidth;													//幅
	int													m_nCntAnim;												//アニメーションのカウンター
	int													m_nPatternAnim;											//アニメーションパターン数

protected:
	LPDIRECT3DTEXTURE9					m_pTexture;													// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;													// 頂点バッファへのポインタ

	float													m_fSize;														//拡大縮小で使う
};
#endif