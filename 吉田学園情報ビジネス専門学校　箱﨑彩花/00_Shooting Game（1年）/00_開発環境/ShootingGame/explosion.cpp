//=============================================================================
//
// 爆発の処理 [explosion.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include"main.h"
#include"player.h"
#include"explosion.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_EXPLOSION		(128)											// 爆発の最大数 
#define EXPLOSION_SPEED		(4)												//爆発の速さ
#define TEXTURE_NAME "data/TEXTURE/explosion000.png"		//テクスチャの名前

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;				//色
	int nCounterAnim;			//アニメーションカウンター
	int nPatternAnim;			//アニメーションNo.
	bool bUse;						//使用しているかどうか
} Explosion;

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		// 頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];									//爆発の情報

//=============================================================================
// 爆発の初期化処理
//=============================================================================
void InitExplosion(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

	// 爆発の情報の初期化
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureExplosion);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
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

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 爆発の終了処理
//=============================================================================
void UninitExplosion(void)
{
	// テクスチャの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// 爆発の更新処理
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{	//弾が使用されている
			//カウンター加算
			g_aExplosion[nCntExplosion].nCounterAnim++;	

			if ((g_aExplosion[nCntExplosion].nCounterAnim % EXPLOSION_SPEED) == 0)
			{	//爆発の速さ
				g_aExplosion[nCntExplosion].nPatternAnim ++;		//パターンNo.更新
			}

			//爆発の座標設定
			pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x -10, g_aExplosion[nCntExplosion].pos.y -10, 0.0f);
			pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y - 10, 0.0f);
			pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);
			pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);

			//テクスチャの座標設定
			pVtx[nCntExplosion * 4].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim  * 0.125f) + 0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, 0.0f);
			pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim *0.125f) + 0.125f, 1.0f);

			if (g_aExplosion[nCntExplosion].pos.y + 30 < 0 || g_aExplosion[nCntExplosion] .nPatternAnim > 7)
			{
				g_aExplosion[nCntExplosion].bUse = false;	//使用していない状態にする
			}
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 爆発の描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	// ポリゴンの描画
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntExplosion,  2);
		}
	}
}

//=============================================================================
// 爆発の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			//爆発の座標設定
			g_aExplosion[nCntExplosion].pos = pos;
			pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10, g_aExplosion[nCntExplosion].pos.y - 10, 0.0f);
			pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y - 10, 0.0f);
			pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);
			pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 50, g_aExplosion[nCntExplosion].pos.y + 50, 0.0f);

			//爆発の色設定
			g_aExplosion[nCntExplosion].col = col;
			pVtx[nCntExplosion * 4].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[nCntExplosion * 4 + 1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[nCntExplosion * 4 + 2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[nCntExplosion * 4 + 3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_aExplosion[nCntExplosion].nCounterAnim = 0;

			//テクスチャの座標設定
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_aExplosion[nCntExplosion].bUse = true;	//使用している状態にする
			break;																//必ず必要
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}