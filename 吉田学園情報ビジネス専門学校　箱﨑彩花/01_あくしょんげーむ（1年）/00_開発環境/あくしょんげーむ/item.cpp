//=============================================================================
//
// アイテムの処理 [item.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "input.h"
#include"main.h"
#include"player.h"
#include "item.h"
#include "score.h"
#include "game.h"
#include "fade.h"
#include "explosion.h"
#include "fadegame.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_NAME "data/TEXTURE/coin000.png"			//テクスチャの名前
#define TEXTURE_NAME1 "data/TEXTURE/onigiri.png"			//テクスチャの名前
#define TEXTURE_NAME2 "data/TEXTURE/piman.png"			//テクスチャの名前
#define MAX_TEXTURE		(3)													//テクスチャの枚数

#define MAX_ITEM				(128)												// アイテムの最大数 
#define ITEM_SPEED			(10)													//アイテムの速さ
#define ITEM_SIZE				(40)													//アイテムの大きさ
#define PLAYER_WIDTH		(30)													//プレイヤーの幅
#define PLAYER_HEIGHT	(70)													//プレイヤーの高さ
#define MINUS					(10)													//アイテムの幅
#define PLUS						(30)													//アイテムの高さ

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItem[MAX_TEXTURE] = {};			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;							// 頂点バッファへのポインタ
Item g_aItem[MAX_ITEM];																			//アイテムの情報
int g_nNumItem;																							//アイテムの総数

//=============================================================================
// アイテム情報のデータ
//=============================================================================
ItemInfoStageSelect g_aItemInfoStageSelect[] =
{
	{ D3DXVECTOR3(270,570,0.0f),20,20,1 },
	{ D3DXVECTOR3(970,570,0.0f),20,20,2 }
};

ItemInfoStage1 g_aItemInfoStage1[] =
{
	//1段目
	{ D3DXVECTOR3(35,500,0.0f),10,20,0 },
	{ D3DXVECTOR3(65,500,0.0f),10,20,0 },
	{ D3DXVECTOR3(95,500,0.0f),10,20,0 },

	//2段目
	{ D3DXVECTOR3(255,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(285,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(315,410,0.0f),10,20,0 },

	//3段目
	{ D3DXVECTOR3(35,280,0.0f),10,20,0 },
	{ D3DXVECTOR3(65,280,0.0f),10,20,0 },
	{ D3DXVECTOR3(95,280,0.0f),10,20,0 },

	//一番上の段
	{ D3DXVECTOR3(275,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(305,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(340,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(375,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(405,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(440,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(475,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(505,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(540,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(575,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(605,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(640,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(675,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(705,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(740,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(775,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(805,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(840,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(875,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(905,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(940,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(975,160,0.0f),10,20,0 },

	//左一番上
	{ D3DXVECTOR3(1170,280,0.0f),10,20,0 },
	{ D3DXVECTOR3(1200,280,0.0f),10,20,0 },
	{ D3DXVECTOR3(1230,280,0.0f),10,20,0 },

	//上から２段目
	{ D3DXVECTOR3(930,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(960,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(990,410,0.0f),10,20,0 },

	//上から１段目
	{ D3DXVECTOR3(1120,500,0.0f),10,20,0 },
	{ D3DXVECTOR3(1150,500,0.0f),10,20,0 },
	{ D3DXVECTOR3(1180,500,0.0f),10,20,0 },

	//右　真ん中
	{ D3DXVECTOR3(755,330,0.0f),10,20,0 },
	{ D3DXVECTOR3(740,360,0.0f),10,20,0 },
	{ D3DXVECTOR3(770,360,0.0f),10,20,0 },

	//左　真ん中
	{ D3DXVECTOR3(520,330,0.0f),10,20,0 },
	{ D3DXVECTOR3(505,360,0.0f),10,20,0 },
	{ D3DXVECTOR3(535,360,0.0f),10,20,0 },

	////
	//{ D3DXVECTOR3(535,600,0.0f),10,20,0 },
	//{ D3DXVECTOR3(585,600,0.0f),10,20,0 },
	//{ D3DXVECTOR3(615,600,0.0f),10,20,0 },

};

ItemInfoStage2 g_aItemInfoStage2[] =
{
	//
	{ D3DXVECTOR3(30,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(70,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(100,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(130,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(160,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(190,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(220,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(250,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(280,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(310,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(340,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(370,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(400,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(430,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(460,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(490,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(520,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(550,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(580,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(610,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(640,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(670,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(700,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(730,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(800,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(830,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(860,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1020,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1050,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1080,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1110,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1140,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1170,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1200,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1260,550,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(30,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(70,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(100,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(130,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(160,410,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(30,310,0.0f),10,20,0 },
	{ D3DXVECTOR3(60,310,0.0f),10,20,0 },
	{ D3DXVECTOR3(90,310,0.0f),10,20,0 },
	{ D3DXVECTOR3(120,310,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(30,190,0.0f),10,20,0 },
	{ D3DXVECTOR3(60,190,0.0f),10,20,0 },
	{ D3DXVECTOR3(90,190,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(30,70,0.0f),10,20,0 },
	{ D3DXVECTOR3(60,70,0.0f),10,20,0 },
	{ D3DXVECTOR3(90,70,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(1170,70,0.0f),10,20,0 },
	{ D3DXVECTOR3(1200,70,0.0f),10,20,0 },
	{ D3DXVECTOR3(1230,70,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(1170,190,0.0f),10,20,0 },
	{ D3DXVECTOR3(1200,190,0.0f),10,20,0 },
	{ D3DXVECTOR3(1230,190,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(1170,330,0.0f),10,20,0 },
	{ D3DXVECTOR3(1200,330,0.0f),10,20,0 },
	{ D3DXVECTOR3(1230,330,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(1200,430,0.0f),10,20,0 },
	{ D3DXVECTOR3(1230,430,0.0f),10,20,0 },

	//中心
	{ D3DXVECTOR3(400,370,0.0f),10,20,0 },
	{ D3DXVECTOR3(440,400,0.0f),10,20,0 },
	{ D3DXVECTOR3(330,370,0.0f),10,20,0 },
	{ D3DXVECTOR3(360,370,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(800,370,0.0f),10,20,0 },
	{ D3DXVECTOR3(850,370,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(605,330,0.0f),10,20,0 },
	{ D3DXVECTOR3(605,200,0.0f),10,20,0 },

	{ D3DXVECTOR3(1230,190,0.0f),10,20,0 },

};

//=============================================================================
// アイテムの初期化処理
//=============================================================================
void InitItem(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	//ステージを取得
	GAMESTAGE pStage;
	pStage = GetGameStage();

	// アイテムの情報の初期化
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].nType = 0;
		g_aItem[nCntItem].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME1, &g_pTextureItem[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME2, &g_pTextureItem[2]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//ポリゴンの座標設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//ポリゴンの色設定
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	g_nNumItem = 0;		//アイテムの総数をクリア

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();

	if (pStage == GAMESTAGE_SELECT)
	{	//選択画面で使用するアイテム
		for (nCntItem = 0; nCntItem < (sizeof g_aItemInfoStageSelect / sizeof(ItemInfoStageSelect)); nCntItem++)
		{
			SetItem(g_aItemInfoStageSelect[nCntItem].pos, g_aItemInfoStageSelect[nCntItem].fWidth, g_aItemInfoStageSelect[nCntItem].fHeight, g_aItemInfoStageSelect[nCntItem].nType);
		}
	}
	else if (pStage == GAMESTAGE1)
	{	//ステージ1で使用するアイテム
		for (nCntItem = 0; nCntItem < (sizeof g_aItemInfoStage1 / sizeof(ItemInfoStage1)); nCntItem++)
		{	
			SetItem(g_aItemInfoStage1[nCntItem].pos, g_aItemInfoStage1[nCntItem].fWidth, g_aItemInfoStage1[nCntItem].fHeight, g_aItemInfoStage1[nCntItem].nType);
		}
	}
	else if (pStage == GAMESTAGE2)
	{	//ステージ2で使用するアイテム
		for (nCntItem = 0; nCntItem < (sizeof g_aItemInfoStage2 / sizeof(ItemInfoStage2)); nCntItem++)
		{	
			SetItem(g_aItemInfoStage2[nCntItem].pos, g_aItemInfoStage2[nCntItem].fWidth, g_aItemInfoStage2[nCntItem].fHeight, g_aItemInfoStage2[nCntItem].nType);
		}
	}
}

//=============================================================================
// アイテムの終了処理
//=============================================================================
void UninitItem(void)
{
	int nCnt;

	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		// テクスチャの開放
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// アイテムの更新処理
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{	//アイテムが使用されている
			if(g_aItem[nCntItem].nType == 0)
			{	//コイン
				//カウンター加算
				g_aItem[nCntItem].nCounterAnim++;
				if ((g_aItem[nCntItem].nCounterAnim % ITEM_SPEED) == 0)
				{	//アイテムの速さ
					g_aItem[nCntItem].nPatternAnim++;		//パターンNo.更新
				}

				//テクスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim  * 0.25f) + 0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim * 0.25f) + 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim * 0.25f) + 0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim * 0.25f) + 0.25f, 1.0f);
			}
			else if (g_aItem[nCntItem].nType == 1)
			{	//おにぎり
				//テクスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (g_aItem[nCntItem].nType == 2)
			{	//ピーマン
				//テクスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			//アイテムの座標設定
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - MINUS, g_aItem[nCntItem].pos.y - MINUS, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + PLUS, g_aItem[nCntItem].pos.y - MINUS, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - MINUS, g_aItem[nCntItem].pos.y + PLUS, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + PLUS, g_aItem[nCntItem].pos.y + PLUS, 0.0f);
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// アイテムの描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntItem,  2);
		}
	}
}

//=============================================================================
// アイテムの設定
//=============================================================================
void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	int nCntItem;
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{	//アイテムを使用していない
			//アイテムの座標設定
			g_aItem[nCntItem].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - MINUS, g_aItem[nCntItem].pos.y - MINUS, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + PLUS, g_aItem[nCntItem].pos.y - MINUS, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - MINUS, g_aItem[nCntItem].pos.y + PLUS, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + PLUS, g_aItem[nCntItem].pos.y + PLUS, 0.0f);

			g_aItem[nCntItem].nCounterAnim = 0;
			g_aItem[nCntItem].nPatternAnim = 0;
			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].bUse = true;		//使用している状態にする

			if (g_aItem[nCntItem].nType == 0)
			{	//コインのみ
				g_nNumItem++;		//コインの総数を加算する
			}
			break;							//必ず必要
		}
	}
	pVtx += 4;
	
	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// アイテムの処理
//=============================================================================
void CollisionItem(int nType)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntItem;

	//プレイヤーを取得
	Player * pPlayer;
	pPlayer = GetPlayer();

	//ステージを取得
	GAMESTAGE pStage;
	pStage = GetGameStage();

	//フェードを取得
	FADEGAME  g_fadeGame;
	g_fadeGame = GetFadeGame();
	 
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{	//アイテムが使用されている
			if (g_aItem[nCntItem].nType == 0)
			{	//コイン
				if (g_aItem[nCntItem].pos.x > pPlayer->pos.x - PLAYER_WIDTH
					&& g_aItem[nCntItem].pos.x < pPlayer->pos.x + PLAYER_WIDTH
					&& g_aItem[nCntItem].pos.y > pPlayer->pos.y - PLAYER_HEIGHT
					&& g_aItem[nCntItem].pos.y < pPlayer->pos.y)
				{
					AddScore(100);
					PlaySound(SOUND_LABEL_SE_COIN);
					DeleteItem(nCntItem);
				}
			}
			else if (g_aItem[nCntItem].nType == 1)
			{	//おにぎり
				if (g_aItem[nCntItem].bUse == true)
				{
					if (g_aItem[nCntItem].pos.x > pPlayer->pos.x - PLAYER_WIDTH + 10
						&& g_aItem[nCntItem].pos.x < pPlayer->pos.x + PLAYER_WIDTH + 10
						&& g_aItem[nCntItem].pos.y > pPlayer->pos.y - PLAYER_HEIGHT
						&& g_aItem[nCntItem].pos.y < pPlayer->pos.y)
					{
						pPlayer->state = PLAYERSTATE_SIZEUP;
						DeleteItem(nCntItem);

						if (g_fadeGame != FADE_OUT)
						{	//フェードアウト中にEnterキーを押せなくする
							//モード設定
							SetFadeGame(GAMESTAGE1);
						}
					}
				}
			}
			else if (g_aItem[nCntItem].nType == 2)
			{	//ピーマン
				if (g_aItem[nCntItem].bUse == true)
				{
					if (g_aItem[nCntItem].pos.x > pPlayer->pos.x - PLAYER_WIDTH + 10
						&& g_aItem[nCntItem].pos.x < pPlayer->pos.x + PLAYER_WIDTH + 10
						&& g_aItem[nCntItem].pos.y > pPlayer->pos.y - PLAYER_HEIGHT
						&& g_aItem[nCntItem].pos.y < pPlayer->pos.y)
					{
						pPlayer->state = PLAYERSTATE_SIZEDOWN;
						DeleteItem(nCntItem);

						if (g_fadeGame != FADE_OUT)
						{	//フェードアウト中にEnterキーを押せなくする
							//モード設定
							SetFadeGame(GAMESTAGE2);
						}
					}
				}
			}
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// アイテムを消す処理
//=============================================================================
void DeleteItem(int nCntItem)
{
	g_nNumItem--;
	if (g_aItem[nCntItem].nType == 0)
	{	//コインを全部取った
		SetExplosion(g_aItem[nCntItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f));
		g_aItem[nCntItem].bUse = false;

		if (g_nNumItem <= 0)
		{
			SetGameState(GAMESTATE_CLEAR);
		}
	}
}