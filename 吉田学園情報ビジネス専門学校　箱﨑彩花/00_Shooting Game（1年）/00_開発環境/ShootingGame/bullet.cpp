//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include"main.h"
#include"player.h"
#include"explosion.h"
#include"enemy.h"
#include "effect.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_BULLET								(300)									// 弾の最大数
#define LIFE												(50)										//弾の飛距離
#define POLYGON_RANGE							(30)										//弾が敵に当たるときの範囲
#define BULLET_TEXTURE_NAME "data/TEXTURE/bullet002.png"	//テクスチャの名前

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nLife;							//寿命
	BULLETTYPE type;			//弾の種類
	bool bUse;						//使用しているかどうか
} Bullet;

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// 頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];												//弾の情報

//=============================================================================
// 弾の初期化処理
//=============================================================================
void InitBullet(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 弾の情報の初期化
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_NAME, &g_pTextureBullet);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//弾の座標設定
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
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 弾の終了処理
//=============================================================================
void UninitBullet(void)
{
	// テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 弾の更新処理
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{	//弾が使用されている
			int nCntEnemy;
			Enemy * pEnemy;

			//弾の位置を移動させる
			//g_aBullet[nCntBullet].pos -= D3DXVECTOR3(0.0f,10.0f,0.0f);
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{	//プレイヤーの弾
				//敵の取得
				pEnemy = GetEnemy();
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 0.3f, 0.5f, 1.0f), 20.0f, 20);

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{	//敵が使用されている
						if (g_aBullet[nCntBullet].pos.x > pEnemy->pos.x - POLYGON_RANGE 
							&& g_aBullet[nCntBullet].pos.x < pEnemy->pos.x + POLYGON_RANGE 
							&& g_aBullet[nCntBullet].pos.y > pEnemy->pos.y - POLYGON_RANGE 
							&& g_aBullet[nCntBullet].pos.y < pEnemy->pos.y + POLYGON_RANGE)
						{	//当たり判定
							HitEnemy(nCntEnemy, 1);
							PlaySound(SOUND_LABEL_SE_HIT000);
							g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
						}
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{	//敵の弾
				Player * pPlayer;

				//プレイヤーの取得
				pPlayer = GetPlayer();
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 16.0f, 10);

				if (pPlayer ->state == PLAYERSTATE_NORMAL)
				{
					if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - POLYGON_RANGE
						&& g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + POLYGON_RANGE
						&& g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - POLYGON_RANGE
						&& g_aBullet[nCntBullet].pos.y < pPlayer->pos.y + POLYGON_RANGE)
					{	//当たり判定
						HitPlayer(1); 

						PlaySound(SOUND_LABEL_SE_HIT001);
						g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
					}
				}
			}

			//弾の大きさ座標設定
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x -10, g_aBullet[nCntBullet].pos.y -10 ,0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x +10, g_aBullet[nCntBullet].pos.y -10, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x -10, g_aBullet[nCntBullet].pos.y +10, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x +10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);

			if (30 + g_aBullet[nCntBullet].pos.y < 0 || 30 -  g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT)
			{
				g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
			}

			//一定時間経過
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 弾の描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	// ポリゴンの描画
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet,  2);
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move ,BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			//弾の大きさ座標設定
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;	//使用している状態にする
			g_aBullet[nCntBullet].nLife = LIFE;
			break;													//必ず必要
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}