//===============================================================================
//
// リザルト画面 [result.cpp]
// Author : 箱�ｱ彩花
//
//===============================================================================
#include "main.h"
#include"result.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "BG.h"
#include "sound.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define RESULT_GAMECLEAR				 "data/TEXTURE/mio.jpg"						//読み込むテクスチャ
#define RESULT_GAMEOVER					 "data/TEXTURE/sabosan.jpg"				//読み込むテクスチャ

#define MAX_TEXTURE						(2)									//テクスチャの数
#define RESULT_POS_X						(0)									//背景の左上X座標
#define RESULT_POS_Y						(0)									//背景の左上Y座標
#define RESULT_WIDTH						(SCREEN_WIDTH)			//背景の幅
#define RESULT_HEIGHT					(SCREEN_HEIGHT)			//背景の高さ

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_TEXTURE] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//頂点バッファへのポインタ

//===============================================================================
//リザルト画面初期化処理
//===============================================================================
void InitResult(void)
{
	//変数宣言
	//VERTEX_2D * pVtx;						//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	GAMESTATE pGame;

	//デバイスを取得
	pDevice = GetDevice();
	pGame = GetGameState();


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

#if 0
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	if(pGame == GAMESTATE_CLEAR)
	{
		//背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//背景の色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//背景のテクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	else
	{	//ゲームオーバー
		//ゲームオーバー背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//ゲームオーバー背景の色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

		//ゲームオーバー背景の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

#endif

	//背景の初期化処理
	InitBG();

	if (pGame == GAMESTATE_CLEAR)
	{	//ゲームクリア
		SetBG(1);
	}
	else
	{	//ゲームオーバー
		SetBG(2);
	}
}

//===============================================================================
//リザルト画面終了処理
//===============================================================================
void UninitResult(void)
{
	int nCntResult;

	for (nCntResult = 0; nCntResult < MAX_TEXTURE; nCntResult++)
	{
		//テクスチャの破棄
		if (g_pTextureResult[nCntResult] != NULL)
		{
			g_pTextureResult[nCntResult]->Release();
			g_pTextureResult[nCntResult] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//背景の終了処理
	UninitBG();
}

//===============================================================================
//リザルト画面更新処理
//===============================================================================
void UpdateResult(void)
{
	//フェードの取得
	FADE g_fade = GetFade();

	//決定キーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);
		if (g_fade != FADE_OUT)
		{	//フェードアウト中にEnterキーを押せなくする
			//モード設定
			SetFade(MODE_RANKING);
		}
	}

	//背景の更新処理
	UpdateBG();
}

//===============================================================================
//リザルト画面描画処理
//===============================================================================
void DrawResult(void)
{
	int nCntResult;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//背景の描画処理
	DrawBG();

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntResult = 0; nCntResult < MAX_TEXTURE; nCntResult++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[nCntResult]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntResult, 2);
	}
}