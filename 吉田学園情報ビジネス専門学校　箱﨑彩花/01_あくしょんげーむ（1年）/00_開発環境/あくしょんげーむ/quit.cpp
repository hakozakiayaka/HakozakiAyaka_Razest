//===============================================================================
//
// クウィット処理 [quit.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include"quit.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define QUIT_TEXTURE	 "data/TEXTURE/pause002.png"		//読み込むテクスチャ

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureQuit = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffQuit = NULL;	//頂点バッファへのポインタ
QUITSTATE g_QuitState;

//===============================================================================
//クウィット初期化処理
//===============================================================================
void InitQuit(void)
{
	//変数宣言
	VERTEX_2D * pVtx;						//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスを取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, QUIT_TEXTURE, &g_pTextureQuit);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffQuit,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

	//クウィット背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(436, 430, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(784, 430, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(436, 542, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(784, 542, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//クウィットの色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//クウィット背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;	//頂点データのポインタを4つ分進める

	//頂点バッファをアンロックする
	g_pVtxBuffQuit->Unlock();
}

//===============================================================================
//クウィット終了処理
//===============================================================================
void UninitQuit(void)
{
	//テクスチャの破棄
	if (g_pTextureQuit != NULL)
	{
		g_pTextureQuit->Release();
		g_pTextureQuit = NULL;
	}
	
	//頂点バッファの破棄
	if (g_pVtxBuffQuit != NULL)
	{
		g_pVtxBuffQuit->Release();
		g_pVtxBuffQuit = NULL;
	}
}

//===============================================================================
//クウィット更新処理
//===============================================================================
void UpdateQuit(void)
{
	VERTEX_2D * pVtx;						//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_QuitState)
	{
	case QUITSTATE_SELECT:
		//コンティニューの色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case 	QUITSTATE_NONE:
		//コンティニューの色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffQuit->Unlock();
}

//===============================================================================
//クウィット描画処理
//===============================================================================
void DrawQuit(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	
	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffQuit, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);	

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureQuit);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===============================================================================
//クウィットの設定
//===============================================================================
void  SetQuit(QUITSTATE state)
{
	g_QuitState = state;
}