//=============================================================================
//
// ポーズ処理 [Pausemenu.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "Pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PAUSEBG_TEXTURENAME			"data\\TEXTURE\\pause_frame.png"	// 読み込むテクスチャファイル(フレーム)
#define PAUSECONTINUE_TEXTURENAME	"data\\TEXTURE\\pause_100.png"		// 読み込むテクスチャファイル(コンテニュー)
#define PAUSERETRY_TEXTURENAME		"data\\TEXTURE\\pause_101.png"		// 読み込むテクスチャファイル(リトライ)
#define PAUSEQUIT_TEXTURENAME		"data\\TEXTURE\\pause_102.png"		// 読み込むテクスチャファイル(クイット)
#define PAUSEBG_POS_X				(0)									// 背景の左上X座標
#define PAUSEBG_POS_Y				(0)									// 背景の左上Y座標
#define PAUSEBG_WHIDTH				(SCREEN_WIDTH)						// 背景の幅
#define PAUSEBG_HEIGHT				(SCREEN_HEIGHT)						// 背景の高さ
#define MAX_TEXTURE					(4)									// テクスチャの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_TEXTURE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPausebg = NULL;		// 頂点バッファへのポインタ
PAUSESTATE g_PauseMode;									// ポーズの状態
COLORSTATE g_PauseColor;
int g_nSelectMenu;										// 選択項目(0～2)

//=============================================================================
//	頂点情報の設定
//=============================================================================
// 初期化処理
void InitPausemenu(void)
{
	// 初期化
	g_PauseMode = PAUSESTATE_NONE;
	g_PauseColor = PAUSESTATECOLOR_NONE;

	g_nSelectMenu = 0;				// 選択項目(0～2)
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		PAUSEBG_TEXTURENAME,
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
		PAUSECONTINUE_TEXTURENAME,
		&g_pTexturePause[1]);

	D3DXCreateTextureFromFile(pDevice,
		PAUSERETRY_TEXTURENAME,
		&g_pTexturePause[2]);

	D3DXCreateTextureFromFile(pDevice,
		PAUSEQUIT_TEXTURENAME,
		&g_pTexturePause[3]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPausebg,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPausebg->Lock(0, 0, (void**)&pVtx, 0);

	// フレーム =======================================================================
	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(430.0f, 160.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(830.0f, 160.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(430.0f, 550.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(830.0f, 550.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 赤、緑、青
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// つづける =======================================================================
	// 頂点座標の設定
	pVtx[4].pos = D3DXVECTOR3(475.0f, 215.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(785.0f, 215.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(475.0f, 275.0f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(785.0f, 275.0f, 0.0f);

	// rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 赤、緑、青
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	// やりなおす ===========================================================================
	// 頂点座標の設定
	pVtx[8].pos = D3DXVECTOR3(480.0f, 315.0f, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(790.0f, 315.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(480.0f, 375.0f, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(790.0f, 375.0f, 0.0f);

	// rhwの設定
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 赤、緑、青
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	// タイトルにもどる ===========================================================================
	// 頂点座標の設定
	pVtx[12].pos = D3DXVECTOR3(480.0f, 415.0f, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(790.0f, 415.0f, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(480.0f, 475.0f, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(790.0f, 475.0f, 0.0f);

	// rhwの設定
	pVtx[12].rhw = 1.0f;
	pVtx[13].rhw = 1.0f;
	pVtx[14].rhw = 1.0f;
	pVtx[15].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 赤、緑、青
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffPausebg->Unlock();
}

//=============================================================================
//	終了処理
//=============================================================================
void UninitPausemenu(void)
{
	for (int nCntPause = 0; nCntPause < MAX_TEXTURE; nCntPause++)
	{
		// テクスチャの破棄
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffPausebg != NULL)
	{
		g_pVtxBuffPausebg->Release();
		g_pVtxBuffPausebg = NULL;
	}
}

//=============================================================================
//	更新処理
//=============================================================================
void UpdatePausemenu(void)
{
	FADE g_fade = GetFade();

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	if (GetKeyboardTrigger(DIK_S) == true)	// Sキー(下)が押されたかどうか
	{
		PlaySound(SOUND_LABEL_SE_SELECT);

		g_nSelectMenu = (g_nSelectMenu + 1) % 3;
	}
	if (GetKeyboardTrigger(DIK_W) == true)	// Wキー(上)が押されたかどうか
	{
		PlaySound(SOUND_LABEL_SE_SELECT);

		 g_nSelectMenu = (g_nSelectMenu + 2) % 3;
	}

	if (g_nSelectMenu == 0)
	{// CONTINUE
		g_PauseColor = PAUSESTATECOLOR_CONTINUE;

		// 決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if(g_fade != FADE_OUT)
 			{
				g_PauseMode = PAUSESTATE_CONTINUE;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}
	if (g_nSelectMenu == 1)
	{// RETRY
		g_PauseColor = PAUSESTATECOLOR_RETRY;

		// 決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_fade != FADE_OUT)
			{
				g_PauseMode = PAUSESTATE_RETRY;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}
	if (g_nSelectMenu == 2)
	{// QUIT
		g_PauseColor = PAUSESTATECOLOR_QUIT;

		// 決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_fade != FADE_OUT)
			{
				g_PauseMode = PAUSESTATE_QUIT;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}

	switch (g_PauseMode)
	{
	case PAUSESTATE_NONE:
		break;

	case PAUSESTATE_CONTINUE:
		g_PauseMode = PAUSESTATE_NONE;
		SetPause(false);
		break;

	case PAUSESTATE_RETRY:
		g_PauseMode = PAUSESTATE_NONE;

		// フェードモード設定
		SetFade(MODE_GAME);
		break;

	case PAUSESTATE_QUIT:
		g_PauseMode = PAUSESTATE_NONE;

		// フェードモード設定
		SetFade(MODE_TITLE);
		break;
	}

	// 頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPausebg->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_PauseColor)
	{
	case PAUSESTATECOLOR_NONE:
		break;

	case PAUSESTATECOLOR_CONTINUE:
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 赤、緑、青
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// 赤、緑、青
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// 赤、緑、青
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		break;

	case PAUSESTATECOLOR_RETRY:
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// 赤、緑、青
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 赤、緑、青
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// 赤、緑、青
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		break;

	case PAUSESTATECOLOR_QUIT:
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// 赤、緑、青
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	// 赤、緑、青
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 赤、緑、青
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		break;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPausebg->Unlock();
}

//=============================================================================
//	描画処理
//=============================================================================
void DrawPausemenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPausebg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntPause = 0; nCntPause < MAX_TEXTURE; nCntPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[nCntPause]);

		//ポリゴンの描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,
			nCntPause * 4,
			2);	// この2は変えない
	}
}