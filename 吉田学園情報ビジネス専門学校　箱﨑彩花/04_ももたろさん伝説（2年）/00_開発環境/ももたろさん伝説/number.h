//=============================================================================
//
// ナンバー処理 [number.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _NUMBER_H_		//二重インクルード防止
#define _NUMBER_H_

#include	"main.h"			//メイン

//*****************************************************************************
// ナンバークラス
//*****************************************************************************
class CNumber
{
public:
	CNumber();																							//コンストラクタ
	~CNumber();																						//デストラクタ
	HRESULT Init(void);																			//初期化処理
	void Uninit(void);																					//終了処理
	void Update(void);																				//更新処理
	void Draw(void);																					//描画処理
	void SetNumber(int nNumber);															//数字の桁数の設定
	void SetPosition(D3DXVECTOR3 pos, int nCnt);								//位置の設定
	void SetColor(D3DXCOLOR col);														//色の設定

	//静的メンバ関数
	static CNumber * Create(void);															//数字の生成
	static HRESULT Load(void);																//テクスチャの割り当て処理
	static void Unload(void);																		//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;									// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;									// 頂点バッファへのポインタ

	int m_nTimeData[3];
	int m_nTime;
	int m_col;
};

#endif