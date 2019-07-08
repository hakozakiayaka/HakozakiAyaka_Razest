//=============================================================================
//
// 影の処理 [shadow.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SHADOW_TEX "data/TEXTURE/shadow000.jpg"		//テクスチャの読み込み
#define MAX_SHADOW		(300)											//影の最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;				//テクスチャへのポインタ
Shadow g_aShadow[MAX_SHADOW];										//影の番号

//=============================================================================
// 初期化処理
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	//構造体の初期化
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].fWidth = 0;
		g_aShadow[nCntShadow].fHeight = 0;
		g_aShadow[nCntShadow].fLength = 0;
		g_aShadow[nCntShadow].OtherPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
	}

	// 頂点情報の作成
	MakeVertexShadow(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	//テクスチャの開放
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;							//計算用マトリックス
	int nCntShadow;

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ
	int nCntShadow;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, SHADOW_TEX, &g_pTextureShadow);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// 影の設定
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ
	int nCntShadow = 0;
	int nShadow = 0;
	float fAngle = 0.0f;			//角度を求める

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = D3DXVECTOR3(pos.x, 0.0f, pos.z);
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].fWidth = fWidth;
			g_aShadow[nCntShadow].fHeight = fHeight;
			g_aShadow[nCntShadow].bUse = true;
			g_aShadow[nCntShadow].nIdxShadow = nCntShadow;
			nShadow = nCntShadow;

			//対角線の角度を求める
			fAngle = atan2f(g_aShadow[nCntShadow].fWidth, g_aShadow[nCntShadow].fHeight);

			//辺の長さを求める(平方根の計算)
			g_aShadow[nCntShadow].fLength = sqrtf((g_aShadow[nCntShadow].fWidth * g_aShadow[nCntShadow].fWidth) + (g_aShadow[nCntShadow].fHeight * g_aShadow[nCntShadow].fHeight));

			//頂点を求める
			g_aShadow[nCntShadow].OtherPos.x = sinf(fAngle) * g_aShadow[nCntShadow].fLength;
			g_aShadow[nCntShadow].OtherPos.z = cosf(fAngle) * g_aShadow[nCntShadow].fLength;

			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].OtherPos.x, 0.0f, g_aShadow[nCntShadow].OtherPos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].OtherPos.x, 0.0f, g_aShadow[nCntShadow].OtherPos.z);
			pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].OtherPos.x, 0.0f, -g_aShadow[nCntShadow].OtherPos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].OtherPos.x, 0.0f, -g_aShadow[nCntShadow].OtherPos.z);

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	return nShadow;	//使用している影の番号（インデックス）を返す
}

//=============================================================================
// 影の位置を設定
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	if (g_aShadow[nIdxShadow].bUse == true)
	{
		g_aShadow[nIdxShadow].pos = D3DXVECTOR3(pos.x, 0.0f, pos.z);
	}
}

//=============================================================================
// 影を削除
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	if (g_aShadow[nIdxShadow].bUse == true)
	{
		g_aShadow[nIdxShadow].bUse = false;
	}
}