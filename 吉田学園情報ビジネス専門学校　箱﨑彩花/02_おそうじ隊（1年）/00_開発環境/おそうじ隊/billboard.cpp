//=============================================================================
//
// ビルボード処理 [billboard.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"
#include "fade.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BILLBOARD_TEX	 "data/TEXTURE/mio.jpg"				//テクスチャの読み込み
#define BILLBOARD_TEX1 "data/TEXTURE/enemy.png"			//テクスチャの読み込み

#define MAX_BILLBOARD	(100)
#define MAX_TEX				(2)												//テクスチャの最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard[MAX_TEX] = {};				//テクスチャへのポインタ
Billboard g_billboard[MAX_BILLBOARD];
int g_nNumItem;

//=============================================================================
// 初期化処理
//=============================================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	int nCntBillboard;

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_billboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_billboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_billboard[nCntBillboard].bUse = false;
	}
	g_nNumItem= 0;		//ビルボードの枚数を初期化

	// 頂点情報の作成
	MakeVertexBillboard(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBillboard(void)
{
	//テクスチャの開放
	for (int nCntBillboard = 0; nCntBillboard < MAX_TEX; nCntBillboard++)
	{
		if (g_pTextureBillboard[nCntBillboard] != NULL)
		{
			g_pTextureBillboard[nCntBillboard]->Release();
			g_pTextureBillboard[nCntBillboard] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBillboard(void)
{
	FADE g_fade = GetFade();
	Player * pPlayer = GetPlayer();

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_billboard[nCntBillboard].bUse == true)
		{
			if (g_billboard[nCntBillboard].pos.x + 10> pPlayer->pos.x
				&& g_billboard[nCntBillboard].pos.x - 10 < pPlayer->pos.x
				&& g_billboard[nCntBillboard].pos.z + 10 > pPlayer->pos.z
				&& g_billboard[nCntBillboard].pos.z - 10 < pPlayer->pos.z)
			{
				AddScore(20000);
				DeleteBillboard(nCntBillboard);
			}

			//影の位置設定
			SetPositionShadow(g_billboard[nCntBillboard].nIdxBillboardShadow, g_billboard[nCntBillboard].pos);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			//計算用マトリックス
	int nCntBillboard;

	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_billboard[nCntBillboard].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_billboard[nCntBillboard].mtxWorldBillboard);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//逆行列の設定
			g_billboard[nCntBillboard].mtxWorldBillboard._11 = mtxView._11;
			g_billboard[nCntBillboard].mtxWorldBillboard._12 = mtxView._21;
			g_billboard[nCntBillboard].mtxWorldBillboard._13 = mtxView._31;
			g_billboard[nCntBillboard].mtxWorldBillboard._21 = mtxView._12;
			g_billboard[nCntBillboard].mtxWorldBillboard._22 = mtxView._22;
			g_billboard[nCntBillboard].mtxWorldBillboard._23 = mtxView._32;
			g_billboard[nCntBillboard].mtxWorldBillboard._31 = mtxView._13;
			g_billboard[nCntBillboard].mtxWorldBillboard._32 = mtxView._23;
			g_billboard[nCntBillboard].mtxWorldBillboard._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_billboard[nCntBillboard].pos.x, g_billboard[nCntBillboard].pos.y, g_billboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_billboard[nCntBillboard].mtxWorldBillboard, &g_billboard[nCntBillboard].mtxWorldBillboard, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_billboard[nCntBillboard].mtxWorldBillboard);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBillboard[g_billboard[nCntBillboard].nTexType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);
		}
	}

	//レンダーステートの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ
	int nCntBillboard;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BILLBOARD_TEX, &g_pTextureBillboard[0]);
	D3DXCreateTextureFromFile(pDevice, BILLBOARD_TEX1, &g_pTextureBillboard[1]);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
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
	g_pVtxBuffBillboard->Unlock();
}

//=============================================================================
// ビルボードの設定
//=============================================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTexType)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_billboard[nCntBillboard].bUse == false)
		{
			g_billboard[nCntBillboard].pos = pos;
			g_billboard[nCntBillboard].rot = rot;
			g_billboard[nCntBillboard].nTexType = nTexType;
			g_billboard[nCntBillboard].bUse = true;

			g_nNumItem++;		//ビルボードの総数を加算する

			//影の初期設定
			g_billboard[nCntBillboard].nIdxBillboardShadow = SetShadow(g_billboard[nCntBillboard].pos, g_billboard[nCntBillboard].rot, 10.0f, 10.0f);
			break;
		}
	}
}

//=============================================================================
// アイテムを消す処理
//=============================================================================
void DeleteBillboard(int nCntBillboard)
{
	g_nNumItem--;
	DeleteShadow(g_billboard[nCntBillboard].nIdxBillboardShadow);
	g_billboard[nCntBillboard].bUse = false;
	if (g_nNumItem <= 0)
	{
		SetGameState(GAMESTATE_CLEAR);
	}
}