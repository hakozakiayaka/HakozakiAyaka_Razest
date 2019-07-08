//=============================================================================
//
// ロゴ処理 [logo.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _LOGO_H_		//二重インクルード防止
#define _LOGO_H_

#include	"main.h"		//メイン

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LOGOTEXTURE		(9)													//テクスチャの最大数

//*****************************************************************************
// ロゴクラス
//*****************************************************************************
class CLogo : public CScene2D
{
public:
	typedef enum
	{
		LOGOSTATE_NONE = 0,
		LOGOSTATE_FLASH,
		LOGOSTATE_MAX
	} LOGOSTATE;

	CLogo();																											//デフォルトコンストラクタ
	~CLogo();																										//デストラクタ
	HRESULT Init(void);																						//初期化処理
	void Uninit(void);																								//終了処理
	void Update(void);																							//更新処理
	void Draw(void);																								//描画処理

	//静的メンバ関数
	static HRESULT Load(void);																			//テクスチャの割り当て処理
	static void Unload(void);																					//テクスチャの破棄

	//静的メンバ変数
	static CLogo *Create();																					//ロゴの生成

private:
	CScene2D * m_apScene2D[MAX_LOGOTEXTURE];										//ポリゴンの生成
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;												// 頂点バッファへのポインタ
	D3DXCOLOR									m_col;														//色の管理
	int													m_BgMove;												//	背景を動かす変数
	int													m_nCntFlash;											//点滅管理するカウンター
	float													m_fFlash;													//点滅する変数
	LOGOSTATE									m_logoState;											//ロゴのステート

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_LOGOTEXTURE];		//テクスチャのポインタ
};

#endif