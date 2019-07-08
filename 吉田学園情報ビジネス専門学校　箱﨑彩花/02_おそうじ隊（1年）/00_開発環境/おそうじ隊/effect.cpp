//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "effect.h"
#include "shadow.h"
#include "fade.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EFFECT_TEX	 "data/TEXTURE/effect000.jpg"				//テクスチャの読み込み

#define MAX_EFFECT		(100)
#define MAX_TEX			(2)												//テクスチャの最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;				//テクスチャへのポインタ
Effect g_Effect[MAX_EFFECT];

//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	int nCntEffect;

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Effect[nCntEffect].fRadius = 0.0f;
		g_Effect[nCntEffect].nLife = 0;
		g_Effect[nCntEffect].bUse = false;
	}

	// 頂点情報の作成
	MakeVertexEffect(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	//テクスチャの開放
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_pTextureEffect != NULL)
		{
			g_pTextureEffect->Release();
			g_pTextureEffect = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{
			g_Effect[nCntEffect].nLife--;
			g_Effect[nCntEffect].fRadius--;

			//エフェクトの大きさ座標設定
			pVtx[0].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x - g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].pos.y - g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x + g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].pos.y - g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x - g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].pos.y + g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x + g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].pos.y + g_Effect[nCntEffect].fRadius, 0.0f);

			if (g_Effect[nCntEffect].nLife == 0)
			{
				g_Effect[nCntEffect].bUse = false;
			}
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			//計算用マトリックス
	int nCntEffect;

	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Effect[nCntEffect].mtxWorldEffect);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//逆行列の設定
			g_Effect[nCntEffect].mtxWorldEffect._11 = mtxView._11;
			g_Effect[nCntEffect].mtxWorldEffect._12 = mtxView._21;
			g_Effect[nCntEffect].mtxWorldEffect._13 = mtxView._31;
			g_Effect[nCntEffect].mtxWorldEffect._21 = mtxView._12;
			g_Effect[nCntEffect].mtxWorldEffect._22 = mtxView._22;
			g_Effect[nCntEffect].mtxWorldEffect._23 = mtxView._32;
			g_Effect[nCntEffect].mtxWorldEffect._31 = mtxView._13;
			g_Effect[nCntEffect].mtxWorldEffect._32 = mtxView._23;
			g_Effect[nCntEffect].mtxWorldEffect._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorldEffect, &g_Effect[nCntEffect].mtxWorldEffect, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].mtxWorldEffect);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//レンダーステートの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ
	int nCntEffect;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX, &g_pTextureEffect);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
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
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// ビルボードの設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{
			g_Effect[nCntEffect].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x - fRadius, g_Effect[nCntEffect].pos.y - fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x + fRadius, g_Effect[nCntEffect].pos.y - fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x - fRadius, g_Effect[nCntEffect].pos.y + fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x + fRadius, g_Effect[nCntEffect].pos.y + fRadius, 0.0f);

			g_Effect[nCntEffect].col = col;
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_Effect[nCntEffect].fRadius = fRadius;
			g_Effect[nCntEffect].nLife = nLife;
			g_Effect[nCntEffect].bUse = true;

			break;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}