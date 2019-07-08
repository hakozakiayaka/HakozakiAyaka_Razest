//=============================================================================
//
// メッシュシリンダー処理 [meshCylinder.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "meshCylinder.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHCYLINDER_TEX "data/TEXTURE/mesh000.jpg"		//読み込むテクスチャ
#define VERTEX_NUMBER		(18)														//頂点数
#define MAX_POLYGON			(16)														//ポリゴンの数
#define INDEX_NUMBER		(18)														//インデックスの数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;	//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;				//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;		//インデックスバッファへのポインタ
int g_nNumVertexMeshCylinder;														//頂点数
int g_nNumIndexMeshCylinder;															//インデックス数
int g_nNumPolygonMeshCylinder;														//ポリゴン数
MESHCYLINDER g_aMeshCylinder;

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	g_aMeshCylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aMeshCylinder.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aMeshCylinder.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 頂点情報の作成
	MakeVertexMeshCylinder(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshCylinder(void)
{
	//テクスチャの開放
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	// インデックスバッファの開放
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshCylinder(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;							//計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_aMeshCylinder.mtxWorldMeshCylinder);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshCylinder.rot.y, g_aMeshCylinder.rot.x, g_aMeshCylinder.rot.z);
	D3DXMatrixMultiply(&g_aMeshCylinder.mtxWorldMeshCylinder, &g_aMeshCylinder.mtxWorldMeshCylinder, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_aMeshCylinder.pos.x, g_aMeshCylinder.pos.y, g_aMeshCylinder.pos.z);
	D3DXMatrixMultiply(&g_aMeshCylinder.mtxWorldMeshCylinder, &g_aMeshCylinder.mtxWorldMeshCylinder, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_aMeshCylinder.mtxWorldMeshCylinder);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,VERTEX_NUMBER,0, MAX_POLYGON);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;								//頂点情報のポインタ
	WORD * pIdx;										//インデックスへのポインタ
	int nCntV;											//水平
	int nCntH;											//垂直
	float fAngle = (D3DX_PI * 2) / 8;		//一つあたりの角度

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHCYLINDER_TEX, &g_pTextureMeshCylinder);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_NUMBER,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntV = 0; nCntV < 2; nCntV++)
	{	//垂直方向
		for (nCntH = 0; nCntH < 9; nCntH++)
		{	//水平方向  
			// 頂点情報の設定
			pVtx[0].pos.x = sinf(D3DX_PI + (fAngle * nCntH)) * 10.0f;		//角度×半径
			pVtx[0].pos.y = 25.0f + (nCntV * 25.0f);										//高さ
			pVtx[0].pos.z = cosf(D3DX_PI + (fAngle * nCntH)) * 10.0f;		//角度×半径

			//法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(pVtx[0].pos.x, pVtx[0].pos.y, pVtx[0].pos.z);
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);											//正規化する

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (nCntH * 1.0f), 0.0f + (nCntV * 1.0f));

			pVtx += 1;
		}
	}

	// 頂点情報の設定
	//pVtx[0].pos = D3DXVECTOR3(-25.0f, 0.0f, 25.0);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 25.0f);
	//pVtx[2].pos = D3DXVECTOR3(25.0f, 0.0f, 25.0f);

	//pVtx[3].pos = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(25.0f, 0.0f, 0.0f);

	//pVtx[6].pos = D3DXVECTOR3(-25.0f, 0.0f, -25.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -25.0f);
	//pVtx[8].pos = D3DXVECTOR3(25.0f, 0.0f, -25.0f);

	////テクスチャの座標設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//pVtx[4].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[5].tex = D3DXVECTOR2(2.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(2.0f, 1.0f);

	//pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[9].tex = D3DXVECTOR2(2.0f, 0.0f);
	//pVtx[10].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[11].tex = D3DXVECTOR2(2.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffMeshCylinder->Unlock();

	//インデックスをロックし、頂点データへのポインタを取得
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの設定
	pIdx[0] = 9;
	pIdx[1] = 0;

	pIdx[2] = 10;
	pIdx[3] = 1;

	pIdx[4] = 11;
	pIdx[5] = 2;

	pIdx[6] = 12;
	pIdx[7] = 3;

	pIdx[8] = 13;
	pIdx[9] = 4;

	pIdx[10] = 14;
	pIdx[11] = 5;

	pIdx[12] = 15;
	pIdx[13] = 6;

	pIdx[14] = 16;
	pIdx[15] = 7;

	pIdx[16] = 17;
	pIdx[17] = 8;

	//頂点バッファをアンロックする
	g_pIdxBuffMeshCylinder->Unlock();
}