//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL1					 "data/MODEL/bed.x"							//モデルの読み込み[ベッド]
#define MODEL2					 "data/MODEL/airplane000.x"			//モデルの読み込み[机]
#define MODEL3					 "data/MODEL/kuma.x"						//モデルの読み込み[くま]
#define MAX_MODEL	(3)																//モデルの最大数

#define MODEL_TEX1		"date/TEXTURE/t.jpg "						//テクスチャの読み込み

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureModel = NULL;			//テクスチャへのポインタ
Model g_aModel[MAX_MODEL];

//=============================================================================
// 初期化処理
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスの取得
	int nNumVtx;															//頂点数
	DWORD sizeFVF;													//頂点フォーマットのサイズ
	BYTE * pVtxBuff;														//頂点バッファへのポインタ

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aModel[0].pBuffMatModel,
		NULL,
		&g_aModel[0].nNumMatModel,
		&g_aModel[0].pMeshModel);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aModel[1].pBuffMatModel,
		NULL,
		&g_aModel[1].nNumMatModel,
		&g_aModel[1].pMeshModel);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aModel[2].pBuffMatModel,
		NULL,
		&g_aModel[2].nNumMatModel,
		&g_aModel[2].pMeshModel);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// 構造体の初期設定
		g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntModel].fShadowWidth = 0;
		g_aModel[nCntModel].fShadowHeight = 0;
		g_aModel[nCntModel].bUse = false;

		//最大値と最小値
		g_aModel[nCntModel].vtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
		g_aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);

		//頂点数を取得
		nNumVtx = g_aModel[nCntModel].pMeshModel->GetNumVertices();

		//頂点フォーマットのサイズ
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCntModel].pMeshModel->GetFVF());

		//頂点フォーマットをロック
		g_aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{	//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

			//最小値
			if (vtx.x < g_aModel[nCntModel].vtxMinModel.x)
			{
				g_aModel[nCntModel].vtxMinModel.x = vtx.x;
			}
			if (vtx.z < g_aModel[nCntModel].vtxMinModel.z)
			{
				g_aModel[nCntModel].vtxMinModel.z = vtx.z;
			}

			//最大値
			if (vtx.x > g_aModel[nCntModel].vtxMaxModel.x)
			{
				g_aModel[nCntModel].vtxMaxModel.x = vtx.x;
			}
			if (vtx.z > g_aModel[nCntModel].vtxMaxModel.z)
			{
				g_aModel[nCntModel].vtxMaxModel.z = vtx.z;
			}

			pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
		}

		//頂点バッファをアンロック
		g_aModel[nCntModel].pMeshModel->UnlockVertexBuffer();

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, MODEL_TEX1, &g_pTextureModel);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	// メッシュの開放
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].pMeshModel != NULL)
		{
			g_aModel[nCntModel].pMeshModel->Release();
			g_aModel[nCntModel].pMeshModel = NULL;
		}

		if (g_aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_aModel[nCntModel].pBuffMatModel->Release();
			g_aModel[nCntModel].pBuffMatModel = NULL;
		}
	}

	//テクスチャの開放
	if (g_pTextureModel != NULL)
	{
		g_pTextureModel->Release();
		g_pTextureModel = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;							//計算用マトリックス
	D3DMATERIAL9 matDef;										//現在のマトリックス保存用
	D3DXMATERIAL * pMat;											//マテリアルデータへのポインタ

	////Zテスト
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);

			// 移動（位置）を反映
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aModel[nCntModel].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャをNULLにする
				pDevice->SetTexture(0, NULL);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureModel);

				// モデル(パーツ)の描画
				g_aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);

			////Zテストを元に戻す
			//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		}
	}
}

//=============================================================================
// モデルの取得
//=============================================================================
Model * GetModel(void)
{
	return &g_aModel[0];
}

//=============================================================================
// モデルの当たり判定
//=============================================================================
void CollisionModel(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld)
{
	//プレイヤーの取得
	Player * pPlayer = GetPlayer();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			if (pPos->x + pPlayer->vtxMinPlayer.x < g_aModel[nCntModel].vtxMaxModel.x + g_aModel[nCntModel].pos.x
				&& pPos->x + pPlayer->vtxMaxPlayer.x > g_aModel[nCntModel].vtxMinModel.x + g_aModel[nCntModel].pos.x)
			{	//Xの範囲判定
				if (pPosOld->z + pPlayer->vtxMaxPlayer.z <= g_aModel[nCntModel].vtxMinModel.z + g_aModel[nCntModel].pos.z
					&& pPos->z + pPlayer->vtxMaxPlayer.z > g_aModel[nCntModel].vtxMinModel.z + g_aModel[nCntModel].pos.z)
				{	//手前の判定
					pPos->z = g_aModel[nCntModel].vtxMinModel.z + g_aModel[nCntModel].pos.z - pPlayer->vtxMaxPlayer.z;
				}
				if (pPosOld->z + pPlayer->vtxMinPlayer.z >= g_aModel[nCntModel].vtxMaxModel.z + g_aModel[nCntModel].pos.z
					&& pPos->z + pPlayer->vtxMinPlayer.z < g_aModel[nCntModel].vtxMaxModel.z + g_aModel[nCntModel].pos.z)
				{	//奥の判定
					pPos->z = g_aModel[nCntModel].vtxMaxModel.z + g_aModel[nCntModel].pos.z - pPlayer->vtxMinPlayer.z;
				}
			}
			if (pPos->z + pPlayer->vtxMaxPlayer.z < g_aModel[nCntModel].vtxMaxModel.z + g_aModel[nCntModel].pos.z
				&& pPos->z + pPlayer->vtxMaxPlayer.z > g_aModel[nCntModel].vtxMinModel.z + g_aModel[nCntModel].pos.z)
			{	//Zの範囲判定
				if (pPosOld->x + pPlayer->vtxMaxPlayer.x <= g_aModel[nCntModel].vtxMinModel.x + g_aModel[nCntModel].pos.x
					&& pPos->x + pPlayer->vtxMaxPlayer.x > g_aModel[nCntModel].vtxMinModel.x + g_aModel[nCntModel].pos.x)
				{	//右の判定
					pPos->x = g_aModel[nCntModel].vtxMinModel.x + g_aModel[nCntModel].pos.x - pPlayer->vtxMaxPlayer.x;
				}
				if (pPosOld->x + pPlayer->vtxMinPlayer.x >= g_aModel[nCntModel].vtxMaxModel.x + g_aModel[nCntModel].pos.x
					&& pPos->x + pPlayer->vtxMinPlayer.x < g_aModel[nCntModel].vtxMaxModel.x + g_aModel[nCntModel].pos.x)
				{	//左の判定
					pPos->x = g_aModel[nCntModel].vtxMaxModel.x + g_aModel[nCntModel].pos.x - pPlayer->vtxMinPlayer.x;
				}
			}
		}
	}
}

//=============================================================================
// モデルの設定
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCntModel, float fShadowWidth, float fShadowHeight)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{
			g_aModel[nCntModel].pos = pos;
			g_aModel[nCntModel].rot = rot;
			g_aModel[nCntModel].bUse = true;
			g_aModel[nCntModel].nIdxModelShadow = SetShadow(g_aModel[nCntModel].pos, g_aModel[nCntModel].rot, fShadowWidth, fShadowHeight);
			break;
		}
	}
}