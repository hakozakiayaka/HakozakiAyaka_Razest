//=============================================================================
//
// フェード処理 [fade.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _FADE_H_		//二重インクルード防止
#define _FADE_H_

#include	"main.h"		//メイン

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CManager;		//マネージャー

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FADE_PRIORITY	(0)															//背景の優先順位

//テクスチャ名
#define LODING_TEX		"data/TEXTURE/lodinglogo.png"				//読み込み中

//*****************************************************************************
// フェードクラス
//*****************************************************************************
class CFade : public CScene
{
public:
	typedef enum
	{	//フェード状態のタイプ分け
		FADE_NONE = 0,															//何もしていない状態
		FADE_IN,																			//フェードイン状態
		FADE_OUT,																		//フェードアウト状態
		FADE_MAX																		//フェード状態の最大数
	} FADE;

	CFade();
	~CFade();																			//デストラクタ
	HRESULT Init(void);															//初期化処理
	void Uninit(void);																	//終了処理
	void Update(void);																//更新処理
	void Draw(void);																	//描画処理

	//静的メンバ関数
	//static HRESULT Load(void);												//テクスチャの割り当て処理
	//static void Unload(void);														//テクスチャの破棄
	static void SetFade(CManager::MODE modeNext);			//フェードの設定
	static FADE GetFade(void) { return m_fade; }					//フェードの取得

private:
	//CScene2D * m_apScene2D;												//ポリゴンの生成

	//静的メンバ変数
	//static LPDIRECT3DTEXTURE9					m_pTexture;		//テクスチャのポインタ
	static LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// 頂点バッファへのポインタ
	static FADE													m_fade;			//フェードの状態
	static CManager::MODE								m_modeNext;	//次のモード
	static D3DXCOLOR										m_colorFade;	//フェードの色
};
#endif