//=============================================================================
//
// ポーズコンティニュー画面 [pausecontinue.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "pausecontinue.h"
#include "main.h"
#include "input.h"
#include "pause.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CONTINUE_TEXTURENAME "data\\TEXTURE\\continue_logo.png"			//読み込むテクスチャファイル
#define CONTINUE_WHIDTH		(350)											//背景の幅
#define CONTINUE_HEIGHT		(70)											//背景の高さ
#define CONTINUE_POS_X		((SCREEN_WIDTH / 2) - (CONTINUE_WHIDTH / 2))	//背景の左上X座標
#define CONTINUE_POS_Y		(230)											//背景の左上Y座標

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePauseContinue = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseContinue = NULL;			//頂点バッファへのポインタ
CONTINUESTATE g_ContinueState;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPauseContinue(void)
{
	//変数の初期化
	g_ContinueState = CONTINUESTATE_NORMAL;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		CONTINUE_TEXTURENAME,
		&g_pTexturePauseContinue);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseContinue,
		NULL);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(CONTINUE_POS_X, CONTINUE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(CONTINUE_POS_X + CONTINUE_WHIDTH, CONTINUE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(CONTINUE_POS_X, CONTINUE_POS_Y + CONTINUE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(CONTINUE_POS_X + CONTINUE_WHIDTH, CONTINUE_POS_Y + CONTINUE_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseContinue->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPauseContinue(void)
{
	//テクスチャの破棄
	if (g_pTexturePauseContinue != NULL)
	{
		g_pTexturePauseContinue->Release();
		g_pTexturePauseContinue = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseContinue != NULL)
	{
		g_pVtxBuffPauseContinue->Release();
		g_pVtxBuffPauseContinue = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePauseContinue(void)
{
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_ContinueState)
	{
	case CONTINUESTATE_NORMAL:
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		pVtx[1].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		pVtx[2].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		pVtx[3].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		break;

	case CONTINUESTATE_SELECT:
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		break;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffPauseContinue->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPauseContinue(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseContinue, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseContinue);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,											//開始する頂点のインデックス
		2);											//プリミティブの数
}

//=============================================================================
// コンティニューの設定処理
//=============================================================================
void SetPauseContinue(CONTINUESTATE state)
{
	//状態の設定
	g_ContinueState = state;
}