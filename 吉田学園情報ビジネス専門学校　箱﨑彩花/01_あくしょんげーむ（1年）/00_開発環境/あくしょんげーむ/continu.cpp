//===============================================================================
//
// コンティニュー処理 [continu.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include"continu.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define CONTINU_TEXTURE	 "data/TEXTURE/pause000.png"		//読み込むテクスチャ

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureContinu = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffContinu = NULL;	//頂点バッファへのポインタ
CONTINUESTATE g_ContinueState;

//===============================================================================
//コンティニュー初期化処理
//===============================================================================
void InitContinu(void)
{
	//変数宣言
	VERTEX_2D * pVtx;						//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスを取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, CONTINU_TEXTURE, &g_pTextureContinu);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffContinu,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffContinu->Lock(0, 0, (void**)&pVtx, 0);

	//コンティニュー背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(436, 206, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(784, 206, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(436, 318, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(784, 318, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//コンティニューの色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//コンティニュー背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;	//頂点データのポインタを4つ分進める

	//頂点バッファをアンロックする
	g_pVtxBuffContinu->Unlock();
}

//===============================================================================
//コンティニュー終了処理
//===============================================================================
void UninitContinu(void)
{
	//テクスチャの破棄
	if (g_pTextureContinu != NULL)
	{
		g_pTextureContinu->Release();
		g_pTextureContinu = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffContinu != NULL)
	{
		g_pVtxBuffContinu->Release();
		g_pVtxBuffContinu = NULL;
	}
}

//===============================================================================
//コンティニュー更新処理
//===============================================================================
void UpdateContinu(void)
{
	VERTEX_2D * pVtx;						//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffContinu->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_ContinueState)
	{
	case CONTUNUESTATE_SELECT:
		//コンティニューの色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case CONTINUESTATE_NONE:
		//コンティニューの色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffContinu->Unlock();
}

//===============================================================================
//コンティニュー描画処理
//===============================================================================
void DrawContinu(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	
	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffContinu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);	

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureContinu);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}

//===============================================================================
//コンティニューの設定処理
//===============================================================================
void SetContinue(CONTINUESTATE state)
{
	g_ContinueState = state;
}