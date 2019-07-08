//===============================================================================
//
// リザルト画面 [result.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include"result.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define RESULT_GAMECLEAR				 "data/TEXTURE/gameclear.jpg"						//読み込むテクスチャ
#define RESULT_PUSUENTER				 "data/TEXTURE/pushenter.png"						//読み込むテクスチャ
#define RESULT_GAMEOVER					 "data/TEXTURE/gameover1.jpg"						//読み込むテクスチャ
#define RESULT_GAMEOVER_LOGO		 "data/TEXTURE/gameover_logo.png"						//読み込むテクスチャ

#define MAX_TEXTURE						(4)									//テクスチャの数
#define RESULT_POS_X						(0)									//背景の左上X座標
#define RESULT_POS_Y						(0)									//背景の左上Y座標
#define RESULT_WIDTH						(SCREEN_WIDTH)			//背景の幅
#define RESULT_HEIGHT					(SCREEN_HEIGHT)			//背景の高さ

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_TEXTURE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;					//頂点バッファへのポインタ

//===============================================================================
//リザルト画面初期化処理
//===============================================================================
void InitResult(void)
{
	//変数宣言
	VERTEX_2D * pVtx;						//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	GAMESTATE pGame;

	//デバイスを取得
	pDevice = GetDevice();
	pGame = GetGameState();

	if (pGame == GAMESTATE_CLEAR)
	{	//ゲームクリア
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, RESULT_GAMECLEAR, &g_pTextureResult[0]);
		//D3DXCreateTextureFromFile(pDevice, RESULT_PUSUENTER, &g_pTextureResult[1]);
	}
	else
	{	//ゲームオーバー
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, RESULT_GAMEOVER, &g_pTextureResult[0]);
		//D3DXCreateTextureFromFile(pDevice, RESULT_GAMEOVER_LOGO, &g_pTextureResult[1]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	if (pGame == GAMESTATE_CLEAR)
	{	//ゲームクリア
		//ゲームクリア背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//ゲームクリア背景の色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ゲームクリア背景のテクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		////===============================================================================
		////プッシュエンター座標設定
		//pVtx[4].pos = D3DXVECTOR3(310, 620, 0.0f);
		//pVtx[5].pos = D3DXVECTOR3(990, 620, 0.0f);
		//pVtx[6].pos = D3DXVECTOR3(310, 700, 0.0f);
		//pVtx[7].pos = D3DXVECTOR3(990, 700, 0.0f);

		////rhwの設定
		//pVtx[4].rhw = 1.0f;
		//pVtx[5].rhw = 1.0f;
		//pVtx[6].rhw = 1.0f;
		//pVtx[7].rhw = 1.0f;

		////プッシュエンター色設定
		//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		////プッシュエンター設定
		//pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		////============================================================================
		////プッシュエンターロゴの座標設定
		//pVtx[8].pos = D3DXVECTOR3(690, 600, 0.0f);
		//pVtx[9].pos = D3DXVECTOR3(970, 600, 0.0f);
		//pVtx[10].pos = D3DXVECTOR3(690, 650, 0.0f);
		//pVtx[11].pos = D3DXVECTOR3(970, 650, 0.0f);

		////rhwの設定
		//pVtx[8].rhw = 1.0f;
		//pVtx[9].rhw = 1.0f;
		//pVtx[10].rhw = 1.0f;
		//pVtx[11].rhw = 1.0f;

		////プッシュエンターロゴの色設定
		//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		////プッシュエンターロゴの設定
		//pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

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
		////============================================================================
		////ゲームオーバーロゴの座標設定
		//pVtx[4].pos = D3DXVECTOR3(600, 360, 0.0f);
		//pVtx[5].pos = D3DXVECTOR3(990, 360, 0.0f);
		//pVtx[6].pos = D3DXVECTOR3(600, 500, 0.0f);
		//pVtx[7].pos = D3DXVECTOR3(990, 500, 0.0f);

		////rhwの設定
		//pVtx[4].rhw = 1.0f;
		//pVtx[5].rhw = 1.0f;
		//pVtx[6].rhw = 1.0f;
		//pVtx[7].rhw = 1.0f;

		////ゲームオーバーロゴの色設定
		//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		////ゲームオーバーロゴの設定
		//pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		////============================================================================
		////プッシュエンターロゴの座標設定
		//pVtx[8].pos = D3DXVECTOR3(310, 620, 0.0f);
		//pVtx[9].pos = D3DXVECTOR3(990, 620, 0.0f);
		//pVtx[10].pos = D3DXVECTOR3(310, 700, 0.0f);
		//pVtx[11].pos = D3DXVECTOR3(990, 700, 0.0f);

		////rhwの設定
		//pVtx[8].rhw = 1.0f;
		//pVtx[9].rhw = 1.0f;
		//pVtx[10].rhw = 1.0f;
		//pVtx[11].rhw = 1.0f;

		////プッシュエンターロゴの色設定
		//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		////プッシュエンターロゴの設定
		//pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();
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
}

//===============================================================================
//リザルト画面更新処理
//===============================================================================
void UpdateResult(void)
{
	//変数宣言
	FADE g_fade;

	//ポインタの取得
	g_fade = GetFade();

	//決定キーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_fade != FADE_OUT)
		{	//フェードアウト中にEnterキーを押せなくする
			//モード設定
			SetFade(MODE_TITLE);
			PlaySound(SOUND_LABEL_SE_DECIDE);
		}
	}
}

//===============================================================================
//リザルト画面描画処理
//===============================================================================
void DrawResult(void)
{
	int nCntResult;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

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