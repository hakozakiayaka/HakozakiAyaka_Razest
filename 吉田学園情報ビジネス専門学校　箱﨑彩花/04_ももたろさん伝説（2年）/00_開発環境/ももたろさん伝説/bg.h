//=============================================================================
//
// 背景処理 [bg.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _BG_H_			//二重インクルード防止
#define _BG_H_

#include	"main.h"		//メイン

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEXTURE		(11)															//テクスチャの最大数
#define BG_PRIORITY			(0)															//背景の優先順位

//テクスチャ名
#define BG_SKY						"data/TEXTURE/sky000.jpg"				//空
#define BG_MOUNTAIN			"data/TEXTURE/mountain.png"			//山
#define BG_FOREST				"data/TEXTURE/weed.png"				//草
#define BG_FIELD					"data/TEXTURE/field.png"					//地面
#define BG_FRONTWEED		"data/TEXTURE/frontweed.png"		//手前の草
#define BG_STONE					"data/TEXTURE/stone.png"				//鬼ヶ島
#define BG_TITLE					"data/TEXTURE/title.jpg"					//タイトル
#define BG_GAMECLEAR		"data/TEXTURE/gameclear.jpg"			//ゲームクリア
#define BG_GAMEOVER			"data/TEXTURE/gameover.jpg"			//ゲームオーバー
#define BG_RANKING				"data/TEXTURE/pausemenu.jpg"		//ランキング
#define BG_TUTORIAL01		"data/TEXTURE/tutorial01.png"			//チュートリアル1枚目
#define BG_TUTORIAL02		"data/TEXTURE/tutorial02.png"			//チュートリアル2枚目

//*****************************************************************************
// 背景クラス
//*****************************************************************************
class CBg : public CScene
{
public:
	typedef enum
	{
		BGSTATE_NONE = 0,
		BGSTATE_MOVE,
		BGSTATE_MAX
	} BGSTATE;

	CBg();																										//デフォルトコンストラクタ
	~CBg();																									//デストラクタ
	HRESULT Init(void);																				//初期化処理
	void Uninit(void);																						//終了処理
	void Update(void);																					//更新処理
	void Draw(void);																						//描画処理

	//静的メンバ関数
	static CBg *Create();																				//背景の生成
	static HRESULT Load(void);																	//テクスチャの割り当て処理
	static void Unload(void);																			//テクスチャの破棄
	D3DXVECTOR3 GetPos(void) { return m_pos; }

private:
	CScene2D * m_apScene2D[MAX_TEXTURE];										//ポリゴンの生成
	D3DXVECTOR3								m_pos;												//背景の位置
	D3DXVECTOR3								m_move;											//移動量
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;										// 頂点バッファへのポインタ
	int													m_BgMove;										//	背景を動かす変数
	BGSTATE											m_bgState;										//状態管理の変数

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_TEXTURE];		//テクスチャのポインタ
};

#endif