//===============================================================================
//
// 背景処理 [bg.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include"bg.h"
#include "game.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define BG_TEXTURE		 "data/TEXTURE/sky005.jpg"						//背景　読み込むテクスチャ
#define BG_TEXTURE1	 "data/TEXTURE/kanban1.png"				//看板　読み込むテクスチャ
#define MAX_BG							(3)													//テクスチャの数

#define BG_POS_X						(0)													//背景の左上X座標
#define BG_POS_Y						(0)													//背景の左上Y座標
#define BG_WIDTH						(SCREEN_WIDTH)							//背景の幅
#define BG_HEIGHT					(SCREEN_HEIGHT)							//背景の高さ
#define VERTEX_NUMBER			(4)													//頂点数

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBG[MAX_BG] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;	//頂点バッファへのポインタ
float g_nBg;

//===============================================================================
//背景初期化処理
//===============================================================================
void InitBG(void)
{
	//変数宣言
	VERTEX_2D * pVtx;						//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスを取得
	pDevice = GetDevice();

	//ステージを取得
	GAMESTAGE pStage;
	pStage = GetGameStage();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE, &g_pTextureBG[0]);

	if (pStage == GAMESTAGE_SELECT)
	{	//選択画面の時だけ使用
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURE1, &g_pTextureBG[1]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUMBER * MAX_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//背景色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//選択画面---------------------------------------------
	if (pStage == GAMESTAGE_SELECT)
	{
		//背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(200, 70, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1000, 70, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(200, 450, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1000, 450, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	pVtx += 4;

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//===============================================================================
//背景終了処理
//===============================================================================
void UninitBG(void)
{
	int nCntBg;

	//テクスチャの破棄
	for (nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		if (g_pTextureBG[nCntBg] != NULL)
		{
			g_pTextureBG[nCntBg]->Release();
			g_pTextureBG[nCntBg] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//===============================================================================
//背景更新処理
//===============================================================================
void UpdateBG(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//ステージを取得
	GAMESTAGE pStage;
	pStage = GetGameStage();

	g_nBg += 0.0001f;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + g_nBg, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + g_nBg, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + g_nBg, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_nBg, 1.0f);

	pVtx += 4;

	//if (pStage == GAMESTAGE_SELECT)
	//{
	//	//背景の座標設定
	//	pVtx[0].pos = D3DXVECTOR3(100, 100, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(300, 100, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(100, 200, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(300, 200, 0.0f);

	//	//テクスチャの座標設定
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//}
	//pVtx += 4;

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//===============================================================================
//背景描画処理
//===============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	int nCntBg;

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);	

	for (nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBG[nCntBg]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBg, 2);
	}
}