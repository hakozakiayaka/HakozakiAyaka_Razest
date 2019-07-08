//=============================================================================
//
// ポーズ処理 [pause.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _PAUSE_H_		//二重インクルード防止
#define _PAUSE_H_

#include	"main.h"		//メイン

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PAUSE_PRIORITY			(5)															//ポーズの優先順位
#define PAUSE_TEXTURE			(5)															//テクスチャの最大数
#define PAUSEMENU					(3)															//メニューの数

//テクスチャ名
#define PAUSE_PAUSEMENU	"data/TEXTURE/pausemenu.jpg"			//メニューの背景
#define PAUSE_CONTINUE		"data/TEXTURE/continue.png"				//つづける
#define PAUSE_RETRY				"data/TEXTURE/retry.png"						//やりなおす
#define PAUSE_QUIT					"data/TEXTURE/quit.png"						//タイトルに戻る

//*****************************************************************************
// 背景クラス
//*****************************************************************************
class CPause : public CScene
{
public:
	typedef enum
	{	//ポーズの種類わけ
		PAUSESTATE_NONE = 0,																	//初期化
		PAUSESTATE_CONTINUE,																	//つづける
		PAUSESTATE_RETRY,																		//やりなおす
		PAUSESTATE_QUIT,																			//タイトルに戻る
		PAUSESTATE_MAX																				//ポーズメニューの最大数
	} PAUSESTATE;

	typedef enum
	{	//各メニューが選択された時の色
		PAUSECOLOR_NONE = 0,																	//初期化
		PAUSECOLOR_CONTINUE,																//つづける
		PAUSECOLOR_RETRY,																		//やりなおす
		PAUSECOLOR_QUIT,																			//タイトルに戻る
		PAUSECOLOR_MAX																			//ポーズメニューの最大数
	} PAUSECOLOR;

	CPause();																								//デフォルトコンストラクタ
	~CPause();																								//デストラクタ
	HRESULT Init(void);																				//初期化処理
	void Uninit(void);																						//終了処理
	void Update(void);																					//更新処理
	void Draw(void);																						//描画処理

	//静的メンバ関数
	static CPause * Create();																		//背景の生成
	static HRESULT Load(void);																	//テクスチャの割り当て処理
	static void Unload(void);																			//テクスチャの破棄
	static bool GetPause(void) { return m_bPause; }									//ポーズの状態を取得
	static void SetPause(bool bPause);														//ポーズの設定

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;										// 頂点バッファへのポインタ
	PAUSESTATE									m_PauseState;								//ポーズの状態を管理
	PAUSECOLOR									m_PauseColor;								//ポーズでの色の管理
	int													m_SelectNum;									//	背景を動かす変数

	//静的メンバ変数
	static CScene2D * m_apScene2D[PAUSE_TEXTURE];							//ポリゴンの生成
	static LPDIRECT3DTEXTURE9		m_pTexture[PAUSE_TEXTURE];		//テクスチャのポインタ
	static bool										m_bPause;
};

#endif