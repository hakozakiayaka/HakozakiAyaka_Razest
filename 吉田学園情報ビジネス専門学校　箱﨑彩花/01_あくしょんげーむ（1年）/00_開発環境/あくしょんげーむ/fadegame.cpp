//=============================================================================
//
// フェード処理 [fadegame.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "fadegame.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BG_POS_X						(0)													//背景の左上X座標
#define BG_POS_Y						(0)													//背景の左上Y座標
#define BG_WIDTH						(SCREEN_WIDTH)							//背景の幅
#define BG_HEIGHT					(SCREEN_HEIGHT)							//背景の高さ
#define NUM_POLYGON				(2)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexFadeGame(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureFadeGame = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFadeGame = NULL;	// 頂点バッファへのポインタ
FADEGAME g_FadeGame;																			// フェード状態
GAMESTAGE g_modeGameNext;
D3DXCOLOR g_colorFadeGame;														// フェード色

//=============================================================================
// 初期化処理
//=============================================================================
void InitFadeGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_FadeGame = FADEGAME_IN;													//フェードイン状態
	g_colorFadeGame = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//黒い画面（不透明）にする

	// 頂点情報の設定
	MakeVertexFadeGame(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFadeGame(void)
{
	// テクスチャの開放
	if (g_pTextureFadeGame != NULL)
	{
		g_pTextureFadeGame->Release();
		g_pTextureFadeGame = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffFadeGame != NULL)
	{
		g_pVtxBuffFadeGame->Release();
		g_pVtxBuffFadeGame = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFadeGame(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	if (g_FadeGame != FADEGAME_NONE)
	{
		if (g_FadeGame == FADEGAME_IN)
		{	//フェードイン状態
			g_colorFadeGame.a -= 0.03f;	//画面を透明にしておく
			if (g_colorFadeGame.a <= 0.0f)
			{
				g_colorFadeGame.a = 0.0f;
				g_FadeGame = FADEGAME_NONE;	//何もしていない状態
			}
		}
		else if (g_FadeGame == FADEGAME_OUT)
		{	//フェードアウト状態
			g_colorFadeGame.a += 0.03f;	//画面を不透明にしておく
			if (g_colorFadeGame.a >= 1.0f)
			{
				g_colorFadeGame.a = 1.0f;	
				g_FadeGame = FADEGAME_IN;	//フェードイン状態

				//モード設定
				SetGameStage(g_modeGameNext);
			}
		}
			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffFadeGame->Lock(0, 0, (void**)&pVtx, 0);

			//フェードの色設定
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFadeGame.a);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFadeGame.a);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFadeGame.a);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFadeGame.a);

			//頂点バッファをアンロックする
			g_pVtxBuffFadeGame->Unlock();
	}
}

//=============================================================================
// タイトル画面
//=============================================================================
void DrawFadeGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffFadeGame, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFadeGame);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4 * NUM_POLYGON);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexFadeGame(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFadeGame,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFadeGame->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点バッファの情報を設定
	//フェードの座標設定
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//フェード色設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffFadeGame->Unlock();
}

//=============================================================================
// フェードの設定
//=============================================================================
void SetFadeGame(GAMESTAGE modeNext)
{
	g_FadeGame = FADEGAME_OUT;												//フェードアウト状態にする
	g_modeGameNext = modeNext;
	g_colorFadeGame = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//黒い画面（透明）にする
}

//=============================================================================
// フェードの取得
//=============================================================================
FADEGAME GetFadeGame(void)
{
	return g_FadeGame;
}