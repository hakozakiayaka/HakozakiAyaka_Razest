//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "enemy.h"
#include "Game.h"
#include "fade.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(4)									// 敵の種類
#define ENEMY_TEXTURE0		"data\\TEXTURE\\Clow.png"		//敵のテクスチャの名前0
#define PLAYER_PATTERN		(2)
#define ENEMY_SIZE			(60)

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEnemy = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// 頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];										//敵の情報
int g_nNumEnemy;												//敵の総数

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;// 頂点情報の作成
	int nCntEnemy;

	// デバイスの取得
	pDevice = GetDevice();

	// 敵の情報の初期化
	// 敵の情報の初期化
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nCntAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nDirectionMove = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	g_nNumEnemy = 0;

	// テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE0, &g_pTextureEnemy);

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
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//一つ目の頂点の場所指定
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//二つ目の頂点の場所指定（右回り）
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);//三つ目の頂点の場所指定（右回り）

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つずらす
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	//テクスチャの破棄
	if (g_pTextureEnemy != NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;// 頂点情報の作成
	Player*pPlayer;
	pPlayer = GetPlayer();


	//頂点バッファをロック
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NOMAL:
				//横移動
				g_aEnemy[nCntEnemy].nDirectionMove = 1;
				g_aEnemy[nCntEnemy].CntMove = 3;
				g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].CntMove;

				break;

			case ENEMYSTATE_DAMAGE:
				//横移動
				g_aEnemy[nCntEnemy].nDirectionMove = 0;
				g_aEnemy[nCntEnemy].CntMove = 3;
				g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].CntMove;

				break;

			}
			g_aEnemy[nCntEnemy].nCntAnim++;//カウンターの加算

			if ((g_aEnemy[nCntEnemy].nCntAnim % 30) == 0)//一定時間が経過
			{
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % PLAYER_PATTERN;		//パターンを更新
			}

			/*if (g_aEnemy[nCntEnemy].pos.x < -50.0f)
			{
				g_aEnemy[nCntEnemy].bUse = false;
			}
			if (g_aEnemy[nCntEnemy].pos.x > SCREEN_WIDTH + 50.0f)
			{
				g_aEnemy[nCntEnemy].bUse = false;
			}*/

			//あたり判定
			if (pPlayer->pos.x + 80 > g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE&&
				pPlayer->pos.x - 80 < g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE&&
				pPlayer->pos.y + 40 > g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE&&
				pPlayer->pos.y - 40 < g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE)
			{//プレイヤーが敵の幅に入っているかどうか
				HitPlayer(1);
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			}

			//テクスチャ座標の設定
			if (g_aEnemy[nCntEnemy].nDirectionMove == 0)
			{//右向きの時
				pVtx[1].tex = D3DXVECTOR2(0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[0].tex = D3DXVECTOR2(0.5f + 0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 1.0f);
			}
			if (g_aEnemy[nCntEnemy].nDirectionMove == 1)
			{//左に向いているとき
				pVtx[0].tex = D3DXVECTOR2(0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 1.0f);
			}

			//座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);//一つ目の頂点の場所指定
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);;//二つ目の頂点の場所指定（右回り）
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);//三つ目の頂点の場所指定（右回り）
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);//三つ目の頂点の場所指定（右回り）

		}
		//該当の位置まで進める
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 描画処理
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
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//敵が使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEnemy);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 4,
				2);
		}
	}
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点をロックして頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//頂点情報を設定
			g_aEnemy[nCntEnemy].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);//左上の頂点Xの場所指定
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);//左上の頂点Xの場所指定
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);//左上の頂点Xの場所指定
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);//左上の頂点Xの場所指定

			g_aEnemy[nCntEnemy].bUse = true;
			g_nNumEnemy++;

			break;
		}
		pVtx += 4;//該当の位置まで進める
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
//=============================================================================
// 敵の取得
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}