//=============================================================================
//
// ポーズ半透明画面 [pause_fade.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "pausefade.h"
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PAUSEFADE_WHIDTH		(SCREEN_WIDTH)										//背景の幅
#define PAUSEFADE_HEIGHT		(SCREEN_HEIGHT)										//背景の高さ
#define PAUSEFADE_POS_X		(0)	//背景の左上X座標
#define PAUSEFADE_POS_Y		(0)	//背景の左上Y座標

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePauseFade = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseFade = NULL;		//頂点バッファへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
void InitPauseFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseFade,
		NULL);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPauseFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(PAUSEFADE_POS_X, PAUSEFADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSEFADE_POS_X + PAUSEFADE_WHIDTH, PAUSEFADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSEFADE_POS_X, PAUSEFADE_POS_Y + PAUSEFADE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSEFADE_POS_X + PAUSEFADE_WHIDTH, PAUSEFADE_POS_Y + PAUSEFADE_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseFade->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPauseFade(void)
{

	// テクスチャの開放
	if (g_pTexturePauseFade != NULL)
	{
		g_pTexturePauseFade->Release();
		g_pTexturePauseFade = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseFade != NULL)
	{
		g_pVtxBuffPauseFade->Release();
		g_pVtxBuffPauseFade = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePauseFade(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPauseFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseFade);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,											//開始する頂点のインデックス
		2);											//プリミティブの数
}