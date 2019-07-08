//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "enemy.h"
#include"main.h"
#include"explosion.h"
#include"bullet.h"
#include "game.h"
#include "score.h"
#include "effect.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TYPE_ENEMY		(4)												// 敵の種類
#define DAMAGE_STATE			(5)												//ダメージ状態
#define ENEMY_LIFE					(5)												//敵のライフ
#define TEX_PATTAERN				(2)												//パターン数
#define TEXTURE_NAME "data/TEXTURE/monster000_1.png"		//テクスチャの名前
#define TEXTURE_NAME2 "data/TEXTURE/monster001_1.png"		//テクスチャの名前
#define TEXTURE_NAME3 "data/TEXTURE/monster002_1.png"		//テクスチャの名前
#define TEXTURE_NAME4 "data/TEXTURE/monster003_1.png"		//テクスチャの名前

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;							// 頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];																	//敵の情報
int g_nNumEnemy;																							//敵の総数

//=============================================================================
// 敵の初期化処理
//=============================================================================
void InitEnemy(void)
{
	// 頂点情報の作成
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].nCntAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nCntMove = 0;
		g_aEnemy[nCntEnemy].nChangeMove = 0;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	// テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME2, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME3, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME4, &g_apTextureEnemy[3]);

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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

	g_nNumEnemy = 0;		//敵の総数をクリア

	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 敵の終了処理
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
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
// 敵の更新処理
//=============================================================================
void UpdateEnemy(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntEnemy = 0;
	float fMoveX = 0;		//角度を求めるためのX
	float fMoveY = 0;		//角度を求めるためのY
	float fangle = 0;			//角度を求める
	float fMoveX2 = 0;		//Xの移動量
	float fMoveY2 = 0;		//Yの移動量

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//ポリゴンの座標設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);

			g_aEnemy[nCntEnemy].nCntAnim++;				//カウンター加算
			if ((g_aEnemy[nCntEnemy].nCntAnim % 40) == 0)
			{	//ポリゴンの速さ
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 2;		//パターンNo.更新
			}

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f + 0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f + 0.5f, 1.0f);
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	//敵が使用されている
			//g_aEnemy[nCntEnemy].nCntBullet++;

			if (g_aEnemy[nCntEnemy].nCntMove > 150 || g_aEnemy[nCntEnemy].nCntMove < -150)
			{
				g_aEnemy[nCntEnemy].nChangeMove *= -1;
			}

			g_aEnemy[nCntEnemy].nCntMove += g_aEnemy[nCntEnemy].nChangeMove;
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].nChangeMove;

			switch (g_aEnemy[nCntEnemy].state)
			{	//敵の状態確認
			case ENEMYSTATE_NORMAL:	//敵が通常状態の時
				//一定時間経過
				if ((rand() % 600) == 0)
				{	//一定時間になったら敵は弾を撃ってくる
					//プレイヤーを取得
					Player * pPlayer;
					pPlayer = GetPlayer();

					//敵の弾がプレイヤーに向かって撃ってくる
					fMoveX = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;		//角度のXを求める
					fMoveY = pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y;		//角度のYを求める
					fangle = atan2f(fMoveX,fMoveY);												//角度求める

					fMoveX2 = sinf(fangle) * 10.0f;
					fMoveY2 = cosf(fangle) * 10.0f;

					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(fMoveX2,fMoveY2, 0.0f),BULLETTYPE_ENEMY);
				}
				break;

			case ENEMYSTATE_DAMADE:	//敵がダメージを受けた
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{	//ダメージ状態が終わったら、体力残ってる
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//敵のダメ―ジ色設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}	
				break;
			}
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 敵の描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	//敵が使用されている
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//ポリゴンの描画
 			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEnemy, 2);
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType, int ChangeMove)
{
	int nCntEnemy;
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{	//敵が使用されていない
			//敵の座標設定
			g_aEnemy[nCntEnemy].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);

			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nCntAnim = 0;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;
			g_aEnemy[nCntEnemy].nLife = ENEMY_LIFE;
			g_aEnemy[nCntEnemy].nCntMove = 0;
			g_aEnemy[nCntEnemy].nChangeMove = ChangeMove;
			g_aEnemy[nCntEnemy].bUse = true;	//使用している状態にする
			g_nNumEnemy++;								//敵の総数を加算する
			break;													//必ず必要
		}

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 敵の取得
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//=============================================================================
// 敵のダメージ処理
//=============================================================================
void HitEnemy(int nCntEnemy,int nDamage)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{	//ライフが0になったら
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		if (g_aEnemy[nCntEnemy].nType == 0)
		{	//きいろの爆発の色
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.9f, 0.4f, 0.1f, 0.7f));
			AddScore(8000);
			g_aEnemy[nCntEnemy].bUse = false;
		}
		else if (g_aEnemy[nCntEnemy].nType == 1)
		{	//みずいろの爆発の色
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.1f, 0.4f, 0.4f, 0.7f));
			AddScore(6000);
			g_aEnemy[nCntEnemy].bUse = false;
		}
		else if (g_aEnemy[nCntEnemy].nType == 2)
		{	//むらさきの爆発の色
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.6f, 0.1f, 0.8f, 0.7f));
			AddScore(4000);
			g_aEnemy[nCntEnemy].bUse = false;
		}
		else if (g_aEnemy[nCntEnemy].nType == 3)
		{	//きみどりの爆発の色
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.1f, 0.7f, 0.3f, 0.7f));
			AddScore(2000);
			g_aEnemy[nCntEnemy].bUse = false;
		}

		g_nNumEnemy--;
		if (g_nNumEnemy <= 0)
		{	//敵が全滅したら
			SetGameState(GAMESTATE_CLEAR);
		}
	}
	else
	{	//ライフが残ってたら
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMADE;
		g_aEnemy[nCntEnemy].nCounterState = DAMAGE_STATE;		//ダメージ状態の時間

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aEnemy[nCntEnemy].nType == 0)
		{	//エビちゃんのダメージの色
			//ダメージの色設定
			pVtx[nCntEnemy * 4].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
			pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
			pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
			pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
		}
		else
		{	//その他の敵
			//ダメージの色設定
			pVtx[nCntEnemy * 4].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		}

		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();
	}
}
