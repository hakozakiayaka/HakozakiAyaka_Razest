//=============================================================================
//
// ポーズメニュー画面 [pausestand.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "pausestand.h"
#include "main.h"
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define RESULT_TEXTURENAME "data\\TEXTURE\\pausemenu.jpg"					//読み込むテクスチャファイル
#define RESULT_WHIDTH		(600)										//背景の幅
#define RESULT_HEIGHT		(550)										//背景の高さ
#define RESULT_POS_X		((SCREEN_WIDTH / 2) - (RESULT_WHIDTH / 2))	//背景の左上X座標
#define RESULT_POS_Y		((SCREEN_HEIGHT / 2) - (RESULT_HEIGHT / 2))	//背景の左上Y座標

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePauseStand = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseStand = NULL;		//頂点バッファへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
void InitPauseStand(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		RESULT_TEXTURENAME,
		&g_pTexturePauseStand);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseStand,
		NULL);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPauseStand->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_POS_X + RESULT_WHIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y + RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_POS_X + RESULT_WHIDTH, RESULT_POS_Y + RESULT_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseStand->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPauseStand(void)
{
	//テクスチャの破棄
	if (g_pTexturePauseStand != NULL)
	{
		g_pTexturePauseStand->Release();
		g_pTexturePauseStand = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseStand != NULL)
	{
		g_pVtxBuffPauseStand->Release();
		g_pVtxBuffPauseStand = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePauseStand(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPauseStand(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseStand, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseStand);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,											//開始する頂点のインデックス
		2);											//プリミティブの数
}