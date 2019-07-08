//=============================================================================
//
// ブロック処理 [block.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "block.h"
#include "input.h"
#include"main.h"
#include"player.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BLOCK_GROUND "data/TEXTURE/ground.png"		//テクスチャの名前
#define BLOCK_YELLOW "data/TEXTURE/block400.jpg"		//アイテムの下のブロック
#define BLOCK_NORMAL "data/TEXTURE/block000.jpg"	//ブロック

#define MAX_TEXTURE								(3)						//テクスチャの最大数

#define MAX_BLOCK									(300)					// ブロックの最大数
#define OUTSIDE										(20)						//ブロックの外
#define BLOCK_HEIGHT								(30)						//ブロックの高さ
#define BLOCK_WIDTH								(100)					//ブロックの高さ
#define PLAYER_HEIGHT							(70)						//プレイヤーの高さ

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_TEXTURE] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;					// 頂点バッファへのポインタ
Block g_aBlock[MAX_BLOCK];																//ブロックの情報

//=============================================================================
// ブロック情報のデータ
//=============================================================================
BlockInfoSelect g_aBlockInfoSelect[] =
{	//選択画面のブロック設定
	//地面
	{ D3DXVECTOR3(0, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(100, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(200, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(300, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(400, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(500, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(600, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(700, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(800, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(900, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1000, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1100, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1200, 660, 0.0f),100,60,0 },

	//アイテム下のブロック
	//おにぎり
	{ D3DXVECTOR3(250, 630, 0.0f),30,30,1 },
	{ D3DXVECTOR3(280, 630, 0.0f),30,30,1 },
	{ D3DXVECTOR3(250, 600, 0.0f),30,30,1 },
	{ D3DXVECTOR3(280, 600, 0.0f),30,30,1 },
	//ピーマン
	{ D3DXVECTOR3(950, 630, 0.0f),30,30,1 },
	{ D3DXVECTOR3(980, 630, 0.0f),30,30,1 },
	{ D3DXVECTOR3(950, 600, 0.0f),30,30,1 },
	{ D3DXVECTOR3(980, 600, 0.0f),30,30,1 },
};

BlockInfoStage1 g_aBlockInfoStage1[] =
{	//おにぎりステージの設定
	//地面
	{ D3DXVECTOR3(0, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(100, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(200, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(300, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(400, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(500, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(600, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(700, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(800, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(900, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(1000, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(1100, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(1200, 690, 0.0f),100,30,0 },

	//一段目、左から--------------------------------
	{ D3DXVECTOR3(20, 530, 0.0f),120,60 ,2},		//1段目　左

	{ D3DXVECTOR3(240, 450, 0.0f),120,60,2 },	//2段目　右

	{ D3DXVECTOR3(10, 310, 0.0f),120,60,2 },		//3段目　左

	//右側
	{ D3DXVECTOR3(240, 190, 0.0f),120,60,2 },		//3段目　左
	{ D3DXVECTOR3(340, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(440, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(540, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(640, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(740, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(840, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(940, 190, 0.0f),100,60,2 },

	//左側
	{ D3DXVECTOR3(1150, 310, 0.0f),120,60,2 },
	{ D3DXVECTOR3(900, 450, 0.0f),120,60,2 },
	{ D3DXVECTOR3(1090, 530, 0.0f),120,60,2 },
};

BlockInfoStage2 g_aBlockInfoStage2[] =
{	//ピーマンステージの設定
	//地面
	{ D3DXVECTOR3(0, 660, 0.0f),100,60 ,0},
	{ D3DXVECTOR3(100, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(200, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(300, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(400, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(500, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(600, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(700, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(800, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(900, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1000, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1100, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1200, 660, 0.0f),100,60,0 },

	//2段目
	{ D3DXVECTOR3(0, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(100, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(200, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(300, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(400, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(500, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(600, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(700, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(800, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1000, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1100, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1200, 580, 0.0f),100,30,2 },

	//
	{ D3DXVECTOR3(0, 460, 0.0f),100,30,2 },
	{ D3DXVECTOR3(100, 460, 0.0f),100,30,2 },

	{ D3DXVECTOR3(0, 340, 0.0f),100,30,2 },
	{ D3DXVECTOR3(70, 340, 0.0f),100,30,2 },

	{ D3DXVECTOR3(0, 220, 0.0f),100,30,2 },
	{ D3DXVECTOR3(50, 220, 0.0f),100,30,2 },

	{ D3DXVECTOR3(0, 100, 0.0f),100,30,2 },
	{ D3DXVECTOR3(30, 100, 0.0f),100,30,2 },

	//左　上から
	{ D3DXVECTOR3(1200, 100, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1170, 100, 0.0f),100,30,2 },

	{ D3DXVECTOR3(1200, 220, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1140, 220, 0.0f),100,30,2 },

	{ D3DXVECTOR3(1200, 360, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1110, 360, 0.0f),100,30,2 },

	{ D3DXVECTOR3(1200, 460, 0.0f),100,30,2 },

	//中心
	{ D3DXVECTOR3(400, 400, 0.0f),30,30,2 },
	{ D3DXVECTOR3(800, 400, 0.0f),30,30,2 },
	{ D3DXVECTOR3(585, 360, 0.0f),30,30,2 },

	{ D3DXVECTOR3(960, 140, 0.0f),30,30,2 },

};

//=============================================================================
// ブロックの初期化処理
//=============================================================================
void InitBlock(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	// デバイスの取得
	pDevice = GetDevice();

	//ステージを取得
	GAMESTAGE pStage;
	pStage = GetGameStage();

	// ブロックの情報の初期化
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0;
		g_aBlock[nCntBlock].fHeight = 0;
		g_aBlock[nCntBlock].nCntType = 0;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_NORMAL;
		g_aBlock[nCntBlock].bLand = false;
		g_aBlock[nCntBlock].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BLOCK_GROUND, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_YELLOW, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_NORMAL, &g_pTextureBlock[2]);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//ブロックの座標設定
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

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
	
	switch (pStage)
	{
	case GAMESTAGE_SELECT:
		for (nCntBlock = 0; nCntBlock < (sizeof g_aBlockInfoSelect / sizeof(BlockInfoSelect)); nCntBlock++)
		{
			SetBlock(g_aBlockInfoSelect[nCntBlock].pos, g_aBlockInfoSelect[nCntBlock].fWidth, g_aBlockInfoSelect[nCntBlock].fHeight, g_aBlockInfoSelect[nCntBlock].nTexType);
		}
		break;

	case GAMESTAGE1:
		for (nCntBlock = 0; nCntBlock < (sizeof g_aBlockInfoStage1 / sizeof(BlockInfoStage1)); nCntBlock++)
		{
			SetBlock(g_aBlockInfoStage1[nCntBlock].pos, g_aBlockInfoStage1[nCntBlock].fWidth, g_aBlockInfoStage1[nCntBlock].fHeight, g_aBlockInfoStage1[nCntBlock].nTexType);
		}
		break;

	case GAMESTAGE2:
		for (nCntBlock = 0; nCntBlock < (sizeof g_aBlockInfoStage2 / sizeof(BlockInfoStage2)); nCntBlock++)
		{
			SetBlock(g_aBlockInfoStage2[nCntBlock].pos, g_aBlockInfoStage2[nCntBlock].fWidth, g_aBlockInfoStage2[nCntBlock].fHeight, g_aBlockInfoStage2[nCntBlock].nTexType);
		}
		break;
	}
}

//=============================================================================
// ブロックの終了処理
//=============================================================================
void UninitBlock(void)
{
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_TEXTURE; nCntBlock++)
	{
		// テクスチャの開放
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================
// ブロックの更新処理
//=============================================================================
void UpdateBlock(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntBlock;

	//プレイヤーを取得
	Player * pPlayer;
	pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{	//ブロックが使用されている

			//ブロックの大きさ座標設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの描画処理
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//ステージを取得
	GAMESTAGE pStage;
	pStage = GetGameStage();

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse == true)
			{
					// テクスチャの設定
					pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nTexType]);

				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBlock, 2);
			}
		}
}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nTexType)
{	
	int nCntBlock;
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++,pVtx += 4)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{	//ブロックが使用されている

			g_aBlock[nCntBlock].pos = pos;
			//ブロックの大きさ座標設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].nTexType = nTexType;
			g_aBlock[nCntBlock].bUse = true;										//使用している状態にする
			break;																					//必ず必要
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// ブロックの当たり判定処理
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove,float fWidth,float fHeight)
{
	//プレイヤーを取得
	Player * pPlayer;
	pPlayer = GetPlayer();

	int nCntBlock;
	bool bLand = false;		//着地したかどうか

	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{	//ブロックが使われているかどうか
			g_aBlock[nCntBlock].bLand = false;

			if (pPlayer->state == PLAYERSTATE_NORMAL)
			{	//通常状態
				if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - OUTSIDE && g_aBlock[nCntBlock].pos.x <= pPos->x + OUTSIDE)
				{	//上から、ブロックの幅にプレイヤーが入ってるかどうか（乗ってるかどうか）
					if (g_aBlock[nCntBlock].pos.y >= pPosOld->y &&	//プレイヤー前回の位置がブロックの高さよりも上だったら
						g_aBlock[nCntBlock].pos.y <= pPos->y)				//プレイヤー現在の位置がブロックの高さよりも下だったら
					{	//ｙ［足元］にめり込んだ
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y;		//地面の高さ
						pMove->y = 0.0f;
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT <= pPosOld->y &&		//プレイヤー前回の位置がブロックの位置より下だったら
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT >= pPos->y)						//プレイヤーの現在の位置がブロックの位置よりも上だったら	
					{	//ｙ[顔]がめり込んだ
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT;
						pMove->y = 0.0f;
					}
					//横の当たり判定
					if (g_aBlock[nCntBlock].bLand == false)
					{	//ブロックの当たり判定が使用されているかどうか
						if (g_aBlock[nCntBlock].pos.y <= pPosOld->y &&																				//プレイヤー現在の位置がブロックの位置より上だったら
							g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT >= pPos->y)		//プレイヤー現在の位置がブロックの位置より下だったら	
						{
							bLand = true;
							g_aBlock[nCntBlock].bLand = true;
							pPos->x = pPosOld->x;
							pMove->x = 0.0f;
						}
					}
				}
			}
			else if (pPlayer->state == PLAYERSTATE_SIZEUP)
			{	//おにぎり
				if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - OUTSIDE * 1.5f && g_aBlock[nCntBlock].pos.x <= pPos->x + OUTSIDE * 1.5f)
				{	//上から、ブロックの幅にプレイヤーが入ってるかどうか（乗ってるかどうか）
					if (g_aBlock[nCntBlock].pos.y >= pPosOld->y &&	//プレイヤー前回の位置がブロックの高さよりも上だったら
						g_aBlock[nCntBlock].pos.y <= pPos->y)				//プレイヤー現在の位置がブロックの高さよりも下だったら
					{	//ｙ［足元］にめり込んだ
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y;		//地面の高さ
						pMove->y = 0.0f;
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT * 1.5f <= pPosOld->y &&		//プレイヤー前回の位置がブロックの位置より下だったら
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT * 1.5f >= pPos->y)						//プレイヤーの現在の位置がブロックの位置よりも上だったら	
					{	//ｙ[顔]がめり込んだ
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT * 1.5f;
						pMove->y = 0.0f;
					}
					//横の当たり判定
					if (g_aBlock[nCntBlock].bLand == false)
					{	//ブロックの当たり判定が使用されているかどうか
						if (g_aBlock[nCntBlock].pos.y <= pPosOld->y &&																				//プレイヤー現在の位置がブロックの位置より上だったら
							g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT * 1.5f >= pPos->y)		//プレイヤー現在の位置がブロックの位置より下だったら	
						{
							bLand = true;
							g_aBlock[nCntBlock].bLand = true;
							pPos->x = pPosOld->x;
							pMove->x = 0.0f;
						}
					}
				}
			}
			else if (pPlayer->state == PLAYERSTATE_SIZEDOWN)
			{	//ピーマン
				if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - OUTSIDE / 2 && g_aBlock[nCntBlock].pos.x <= pPos->x + OUTSIDE / 2)
				{	//上から、ブロックの幅にプレイヤーが入ってるかどうか（乗ってるかどうか）
					if (g_aBlock[nCntBlock].pos.y >= pPosOld->y &&	//プレイヤー前回の位置がブロックの高さよりも上だったら
						g_aBlock[nCntBlock].pos.y <= pPos->y)				//プレイヤー現在の位置がブロックの高さよりも下だったら
					{	//ｙ［足元］にめり込んだ
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y;		//地面の高さ
						pMove->y = 0.0f;
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT / 2 <= pPosOld->y &&		//プレイヤー前回の位置がブロックの位置より下だったら
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT / 2 >= pPos->y)						//プレイヤーの現在の位置がブロックの位置よりも上だったら	
					{	//ｙ[顔]がめり込んだ
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT / 2;
						pMove->y = 0.0f;
					}
					//横の当たり判定
					if (g_aBlock[nCntBlock].bLand == false)
					{	//ブロックの当たり判定が使用されているかどうか
						if (g_aBlock[nCntBlock].pos.y <= pPosOld->y &&																				//プレイヤー現在の位置がブロックの位置より上だったら
							g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT / 2 >= pPos->y)		//プレイヤー現在の位置がブロックの位置より下だったら	
						{
							bLand = true;
							g_aBlock[nCntBlock].bLand = true;
							pPos->x = pPosOld->x;
							pMove->x = 0.0f;
						}
					}
				}
			}
		}
	}
	return bLand;
}