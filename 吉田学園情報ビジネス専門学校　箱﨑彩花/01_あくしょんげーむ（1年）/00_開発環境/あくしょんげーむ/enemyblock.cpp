//=============================================================================
//
// 敵ブロック処理 [enemyblock.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "enemyblock.h"
#include"main.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_NAME "data/TEXTURE/monster000_1.png"		//テクスチャの名前
#define	MAX_ENEMYBLOCK	(256)	// 敵ブロックブロックの最大数

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureEnemy = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			// 頂点バッファへのポインタ
ENEMYBLOCK g_aEnemyBlock[MAX_ENEMYBLOCK];				//敵ブロックの情報
int g_nNumEnemyBlock;																	//敵ブロックの総数

//=============================================================================
// 敵ブロックの初期化処理
//=============================================================================
void InitEnemyBlock(void)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵ブロックの情報の初期化
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMYBLOCK; nCntEnemy++)
	{
		g_aEnemyBlock[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyBlock[nCntEnemy].state = ENEMYBLOCKSTATE_NORMAL;
		g_aEnemyBlock[nCntEnemy].nCounterState = 0;
		g_aEnemyBlock[nCntEnemy].fHeight = 0;
		g_aEnemyBlock[nCntEnemy].fWidth = 0;
		g_aEnemyBlock[nCntEnemy].bUse = false;
	}

	// テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_apTextureEnemy);

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMYBLOCK,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMYBLOCK; nCntEnemy++)
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
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	g_nNumEnemyBlock = 0;		//敵ブロックの総数をクリア

	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 敵ブロックの終了処理
//=============================================================================
void UninitEnemyBlock(void)
{
	int nCntTex;

	// テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_ENEMYBLOCK; nCntTex++)
	{
		if (g_apTextureEnemy != NULL)
		{
			g_apTextureEnemy ->Release();
			g_apTextureEnemy = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// 敵ブロックの更新処理
//=============================================================================
void UpdateEnemyBlock(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntEnemyBlock = 0;

	//プレイヤーを取得
	Player * pPlayer;
	pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemyBlock = 0; nCntEnemyBlock < MAX_ENEMYBLOCK; nCntEnemyBlock++)
	{	
		if (g_aEnemyBlock[nCntEnemyBlock].bUse == true)
		{
			//ブロックの大きさ座標設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemyBlock].pos.x, g_aEnemyBlock[nCntEnemyBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemyBlock].pos.x + g_aEnemyBlock[nCntEnemyBlock].fWidth, g_aEnemyBlock[nCntEnemyBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemyBlock].pos.x, g_aEnemyBlock[nCntEnemyBlock].pos.y + g_aEnemyBlock[nCntEnemyBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemyBlock].pos.x + g_aEnemyBlock[nCntEnemyBlock].fWidth, g_aEnemyBlock[nCntEnemyBlock].pos.y + g_aEnemyBlock[nCntEnemyBlock].fHeight, 0.0f);
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
}

//=============================================================================
// 敵ブロックの描画処理
//=============================================================================
void DrawEnemyBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMYBLOCK; nCntEnemy++)
	{
		if (g_aEnemyBlock[nCntEnemy].bUse == true)
		{	//敵ブロックが使用されている
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy);

			//ポリゴンの描画
 			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEnemy, 2);
		}
	}
}

//=============================================================================
// 敵ブロックの設定
//=============================================================================
void SetEnemyBlock(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nCntEnemy;
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMYBLOCK; nCntEnemy++)
	{
		if (g_aEnemyBlock[nCntEnemy].bUse == false)
		{	//敵ブロックが使用されていない
			//敵ブロックの座標設定
			g_aEnemyBlock[nCntEnemy].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemy].pos.x - 25, g_aEnemyBlock[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemy].pos.x + 25, g_aEnemyBlock[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemy].pos.x - 25, g_aEnemyBlock[nCntEnemy].pos.y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemy].pos.x + 25, g_aEnemyBlock[nCntEnemy].pos.y + 25, 0.0f);

			g_aEnemyBlock[nCntEnemy].state = ENEMYBLOCKSTATE_NORMAL;
			g_aEnemyBlock[nCntEnemy].nCounterState = 0;
			g_aEnemyBlock[nCntEnemy].bUse = true;	//使用している状態にする
			g_nNumEnemyBlock++;									//敵ブロックの総数を加算する
			break;																//必ず必要
		}

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 敵ブロックのダメージ処理
//=============================================================================
void CollisionEnemyBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);


		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();
}
