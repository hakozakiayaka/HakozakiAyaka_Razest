//=============================================================================
//
// メッシュフィールド処理 [meshField.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "meshField.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEX "data/TEXTURE/jyutan1.jpg"		//読み込むテクスチャ
#define MAX_MESHFIELD	(1)										//フィールドの最大数[使う分だけ]
#define WIDTH					(10)
#define HEIGHT					(10)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField[MAX_MESHFIELD] = {};	//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;										//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField[MAX_MESHFIELD] = {};		//インデックスバッファへのポインタ
MESHFIELD g_aMeshField[MAX_MESHFIELD];

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		g_aMeshField[nCntMeshField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
		g_aMeshField[nCntMeshField].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
		g_aMeshField[nCntMeshField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
		g_aMeshField[nCntMeshField].nWidth = 0;														//幅何枚？
		g_aMeshField[nCntMeshField].nHeight = 0;														//高さ何枚？
		g_aMeshField[nCntMeshField].bUse = false;
	}

	//メッシュフィールドの設置
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WIDTH, HEIGHT);

	// 頂点情報の作成
	MakeVertexMeshField(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	//テクスチャの開放
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// 頂点バッファの開放
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_pVtxBuffMeshField[nCntMeshField] != NULL)
		{
			g_pVtxBuffMeshField[nCntMeshField]->Release();
			g_pVtxBuffMeshField[nCntMeshField] = NULL;
		}
	}

	// インデックスバッファの開放
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_pIdxBuffMeshField[nCntMeshField] != NULL)
		{
			g_pIdxBuffMeshField[nCntMeshField]->Release();
			g_pIdxBuffMeshField[nCntMeshField] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;							//計算用マトリックス

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aMeshField[nCntMeshField].mtxWorldMeshField);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshField[nCntMeshField].rot.y, g_aMeshField[nCntMeshField].rot.x, g_aMeshField[nCntMeshField].rot.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorldMeshField, &g_aMeshField[nCntMeshField].mtxWorldMeshField, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aMeshField[nCntMeshField].pos.x, g_aMeshField[nCntMeshField].pos.y, g_aMeshField[nCntMeshField].pos.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorldMeshField, &g_aMeshField[nCntMeshField].mtxWorldMeshField, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshField[nCntMeshField].mtxWorldMeshField);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshField[nCntMeshField], 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshField[nCntMeshField]);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureMeshField);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshField[nCntMeshField].nNumVertexMeshField, 0, g_aMeshField[nCntMeshField].nNumPolygonMeshField);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ
	WORD * pIdx;					//インデックスへのポインタ
	int nCntY;						//縦
	int nCntX;						//横

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX, &g_pTextureMeshField);

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		// 頂点バッファを生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshField[nCntMeshField].nNumVertexMeshField * MAX_MESHFIELD,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMeshField[nCntMeshField],
			NULL);

		//インデックスバッファの生成
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshField[nCntMeshField].nNumIndexMeshField * MAX_MESHFIELD ,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIdxBuffMeshField[nCntMeshField],
			NULL);

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffMeshField[nCntMeshField]->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntY = 0; nCntY <= g_aMeshField[nCntMeshField].nHeight; nCntY++)
		{	//縦
			for (nCntX = 0; nCntX <= g_aMeshField[nCntMeshField].nWidth; nCntX++)
			{	//横
				//頂点情報の設定
				pVtx[0].pos = D3DXVECTOR3(-100.0f + (100.0f * nCntX), 0.0f, 100.0f - (100.0f * nCntY));

				//法線ベクトルの設定
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//テクスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntY));

				pVtx += 1;
			}
		}

		//頂点バッファをアンロックする
		g_pVtxBuffMeshField[nCntMeshField]->Unlock();

		int nCntIdx = 0;						//インデックスのカウンター

		//インデックスをロックし、頂点データへのポインタを取得
		g_pIdxBuffMeshField[nCntMeshField]->Lock(0, 0, (void**)&pIdx, 0);

		for (nCntY = 0; nCntY < g_aMeshField[nCntMeshField].nHeight; nCntY++)
		{
			for (nCntX = 0; nCntX <= g_aMeshField[nCntMeshField].nWidth; nCntX++, nCntIdx++)
			{
				pIdx[0] = (g_aMeshField[nCntMeshField].nWidth + 1) + nCntIdx;
				pIdx[1] = nCntIdx;
				pIdx += 2;																	//インデックスを進める

				if (nCntX == g_aMeshField[nCntMeshField].nWidth && nCntY < g_aMeshField[nCntMeshField].nHeight - 1)
				{
					pIdx[0] = nCntIdx;
					pIdx[1] = (g_aMeshField[nCntMeshField].nWidth + 1) + nCntIdx + 1;	//上のやつと入れ替え
					pIdx += 2;
				}
			}
		}

		//頂点バッファをアンロックする
		g_pIdxBuffMeshField[nCntMeshField]->Unlock();
	}
}

//=============================================================================
// メッシュフィールドの取得
//=============================================================================
MESHFIELD * GetMeshField(void)
{
	return &g_aMeshField[0];
}

//=============================================================================
// メッシュフィールドの設定
//=============================================================================
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight)
{
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse == false)
		{
			g_aMeshField[nCntMeshField].pos = pos;
			g_aMeshField[nCntMeshField].rot = rot;
			g_aMeshField[nCntMeshField].nWidth = nWidth;
			g_aMeshField[nCntMeshField].nHeight = nHeight;
			g_aMeshField[nCntMeshField].bUse = true;

			//自動計算
			g_aMeshField[nCntMeshField].nNumVertexMeshField = (g_aMeshField[nCntMeshField].nHeight + 1) * (g_aMeshField[nCntMeshField].nWidth + 1);
			g_aMeshField[nCntMeshField].nNumIndexMeshField = (g_aMeshField[nCntMeshField].nWidth * g_aMeshField[nCntMeshField].nHeight) * 2 + (4 * (g_aMeshField[nCntMeshField].nHeight - 1)) + 2;
			g_aMeshField[nCntMeshField].nNumPolygonMeshField = (g_aMeshField[nCntMeshField].nWidth * g_aMeshField[nCntMeshField].nHeight) * 2 + (4 * (g_aMeshField[nCntMeshField].nHeight - 1));

			break;
		}
	}
}