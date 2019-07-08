//===============================================================================
//
// リトライ処理 [pause.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include"retry.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define RETRY_TEXTURE	 "data/TEXTURE/pause001.png"		//読み込むテクスチャ

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureRetry = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRetry = NULL;	//頂点バッファへのポインタ
RETRYSTATE g_RetryState;

//===============================================================================
//リトライ初期化処理
//===============================================================================
void InitRetry(void)
{
	//変数宣言
	VERTEX_2D * pVtx;						//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	
	//デバイスを取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, RETRY_TEXTURE, &g_pTextureRetry);
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRetry,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

	//リトライ背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(436, 318, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(784, 318, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(436, 430, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(784, 430, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//リトライの色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//リトライ背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;	//頂点データのポインタを4つ分進める

	//頂点バッファをアンロックする
	g_pVtxBuffRetry->Unlock();
}

//===============================================================================
//リトライ終了処理
//===============================================================================
void UninitRetry(void)
{
	//テクスチャの破棄
	if (g_pTextureRetry != NULL)
	{
		g_pTextureRetry->Release();
		g_pTextureRetry = NULL;
	}
	
	//頂点バッファの破棄
	if (g_pVtxBuffRetry != NULL)
	{
		g_pVtxBuffRetry->Release();
		g_pVtxBuffRetry = NULL;
	}
}

//===============================================================================
//リトライ更新処理
//===============================================================================
void UpdateRetry(void)
{
	VERTEX_2D * pVtx;						//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_RetryState)
	{
	case RETRYSTATE_SELECT:
		//リトライの色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case RETRYSTATE_NONE:
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRetry->Unlock();
}

//===============================================================================
//リトライ描画処理
//===============================================================================
void DrawRetry(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	
	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRetry, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);	

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRetry);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0 , 2);
}

//===============================================================================
//リトライの設定処理
//===============================================================================
void SetRetry(RETRYSTATE state)
{
	g_RetryState = state;
}