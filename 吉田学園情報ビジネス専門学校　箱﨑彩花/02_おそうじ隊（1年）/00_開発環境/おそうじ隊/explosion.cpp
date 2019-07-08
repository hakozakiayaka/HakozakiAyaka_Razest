//=============================================================================
//
// 爆発の処理 [explosion.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include"main.h"
#include"explosion.h"
#include "player.h"
#include "shadow.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EXPLOSION_TEX "data/TEXTURE/explosion002.png"			//テクスチャの名前
#define MAX_EXPLOSION			(300)												// 爆発の最大数 
#define EXPLOSION_SPEED		(4)													//爆発の速さ
#define EXPLOSION_SIZE			(15.0f)												//爆発の大きさ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntExplosion;

	// 爆発の情報の初期化
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// 頂点情報の作成
	MakeVertexExplosion(pDevice);
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
	VERTEX_3D * pVtx;			//頂点情報のポインタ
	int nCntExplosion;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{	//弾が使用されている
			//カウンター加算
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if ((g_aExplosion[nCntExplosion].nCounterAnim % EXPLOSION_SPEED) == 0)
			{	//爆発の速さ
				g_aExplosion[nCntExplosion].nPatternAnim++;		//パターンNo.更新
			}

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim  * 0.125f) + 0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim * 0.125f) + 0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_aExplosion[nCntExplosion].nPatternAnim *0.125f) + 0.125f, 1.0f);

			if (g_aExplosion[nCntExplosion].pos.y + 30 < 0 || g_aExplosion[nCntExplosion] .nPatternAnim > 7)
			{
				g_aExplosion[nCntExplosion].bUse = false;	//使用していない状態にする
			}
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 爆発の描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			//計算用マトリックス
	int nCntExplosion;

	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//Zテスト
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aExplosion[nCntExplosion].mtxWorldBullet);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//逆行列の設定
			g_aExplosion[nCntExplosion].mtxWorldBullet._11 = mtxView._11;
			g_aExplosion[nCntExplosion].mtxWorldBullet._12 = mtxView._21;
			g_aExplosion[nCntExplosion].mtxWorldBullet._13 = mtxView._31;
			g_aExplosion[nCntExplosion].mtxWorldBullet._21 = mtxView._12;
			g_aExplosion[nCntExplosion].mtxWorldBullet._22 = mtxView._22;
			g_aExplosion[nCntExplosion].mtxWorldBullet._23 = mtxView._32;
			g_aExplosion[nCntExplosion].mtxWorldBullet._31 = mtxView._13;
			g_aExplosion[nCntExplosion].mtxWorldBullet._32 = mtxView._23;
			g_aExplosion[nCntExplosion].mtxWorldBullet._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_aExplosion[nCntExplosion].mtxWorldBullet, &g_aExplosion[nCntExplosion].mtxWorldBullet, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aExplosion[nCntExplosion].mtxWorldBullet);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}

	//レンダーステートの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//Zテストを元に戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ
	int nCntExplosion;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEX, &g_pTextureExplosion);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//爆発の座標設定
		pVtx[0].pos = D3DXVECTOR3(-EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EXPLOSION_SIZE, EXPLOSION_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EXPLOSION_SIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EXPLOSION_SIZE, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//爆発の色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
// 爆発の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;
	VERTEX_3D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;							//位置
			g_aExplosion[nCntExplosion].col = col;								//カラー
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_aExplosion[nCntExplosion].nCounterAnim = 0;				//アニメーションカウンター
			g_aExplosion[nCntExplosion].nPatternAnim = 0;				//アニメーションのパターン数
			g_aExplosion[nCntExplosion].bUse = true;						//使用している状態にする
			break;																					//必ず必要
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}