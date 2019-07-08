//=============================================================================
//
// メッシュウォール処理 [meshWall.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "meshWall.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEX		"data/TEXTURE/kabegami.jpg"		//読み込むテクスチャ
#define MESHFIELD_TEX2		"data/TEXTURE/kabegami.jpg"		//読み込むテクスチャ
#define MESHFIELD_TEX3		"data/TEXTURE/kabegami.jpg"		//読み込むテクスチャ
#define MESHFIELD_TEX4		"data/TEXTURE/kabegami.jpg"		//読み込むテクスチャ
#define MESHFIELD_TEX5		"data/TEXTURE/window.jpg"			//読み込むテクスチャ

#define MAX_WALL				(6)													//壁の数
#define MAX_TEX					(5)													//読み込むテクスチャの枚数
#define WIDTH						(10)													//壁の幅何枚か
#define HEIGHT						(6)													//壁の高さ何枚か

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall[MAX_WALL] = {};			//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshWall[MAX_TEX] = {};					//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall[MAX_WALL] = {};			//インデックスバッファへのポインタ
MESHWALL g_aMeshWall[MAX_WALL];

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	int nCntMeshWall;

	for (nCntMeshWall = 0; nCntMeshWall < MAX_WALL; nCntMeshWall++)
	{
		g_aMeshWall[nCntMeshWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].nWidth = 0;
		g_aMeshWall[nCntMeshWall].nHeight = 0;
		g_aMeshWall[nCntMeshWall].bUse = false;
	}

	//壁の設置
	SetMeshWall(D3DXVECTOR3(0.0f, 250.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WIDTH, HEIGHT, 0);								//奥
	SetMeshWall(D3DXVECTOR3(300.0f, 50.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 1, 4);													//窓
	SetMeshWall(D3DXVECTOR3(500.0f, 50.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 1, 4);													//窓
	SetMeshWall(D3DXVECTOR3(900.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5, 0.0f), WIDTH, HEIGHT, 1);				//右
	SetMeshWall(D3DXVECTOR3(-100.0f, 250.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5, 0.0f), WIDTH, HEIGHT, 2);	//左
	SetMeshWall(D3DXVECTOR3(800.0f, 250.0f, -900.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WIDTH, HEIGHT, 3);				//手前

	// 頂点情報の作成
	MakeVertexMeshWall(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshWall(void)
{
	//テクスチャの開放
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_TEX; nCntMeshWall++)
	{
		if (g_pTextureMeshWall[nCntMeshWall] != NULL)
		{
			g_pTextureMeshWall[nCntMeshWall]->Release();
			g_pTextureMeshWall[nCntMeshWall] = NULL;
		}
	}


	// 頂点バッファの開放
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_WALL; nCntMeshWall++)
	{
		if (g_pVtxBuffMeshWall[nCntMeshWall] != NULL)
		{
			g_pVtxBuffMeshWall[nCntMeshWall]->Release();
			g_pVtxBuffMeshWall[nCntMeshWall] = NULL;
		}
	}

	// インデックスバッファの開放
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_WALL; nCntMeshWall++)
	{
		if (g_pIdxBuffMeshWall[nCntMeshWall] != NULL)
		{
			g_pIdxBuffMeshWall[nCntMeshWall]->Release();
			g_pIdxBuffMeshWall[nCntMeshWall] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshWall(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;							//計算用マトリックス
	int nCntMeshWall;

	for (nCntMeshWall = 0; nCntMeshWall < MAX_WALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aMeshWall[nCntMeshWall].mtxWorldMeshWall);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCntMeshWall].rot.y, g_aMeshWall[nCntMeshWall].rot.x, g_aMeshWall[nCntMeshWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorldMeshWall, &g_aMeshWall[nCntMeshWall].mtxWorldMeshWall, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCntMeshWall].pos.x, g_aMeshWall[nCntMeshWall].pos.y, g_aMeshWall[nCntMeshWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorldMeshWall, &g_aMeshWall[nCntMeshWall].mtxWorldMeshWall, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntMeshWall].mtxWorldMeshWall);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall[nCntMeshWall], 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshWall[nCntMeshWall]);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureMeshWall[g_aMeshWall[nCntMeshWall].nTexType]);

				//ポリゴンの描画
				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 4 * nCnt, g_aMeshWall[nCnt].nNumVertexMeshWall, 0, g_aMeshWall[nCnt].nNumPolygonMeshWall);
			}
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ
	WORD * pIdx;					//インデックスへのポインタ
	int nCntY;						//縦
	int nCntX;						//横

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX, &g_pTextureMeshWall[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX2, &g_pTextureMeshWall[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX3, &g_pTextureMeshWall[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX4, &g_pTextureMeshWall[3]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX5, &g_pTextureMeshWall[4]);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		// 頂点バッファを生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshWall[nCnt].nNumVertexMeshWall * MAX_WALL,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMeshWall[nCnt],
			NULL);

		//インデックスバッファの生成
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshWall[nCnt].nNumIndexMeshWall * MAX_WALL,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIdxBuffMeshWall[nCnt],
			NULL);

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffMeshWall[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntY = 0; nCntY <= g_aMeshWall[nCnt].nHeight; nCntY++)
		{	//縦
			for (nCntX = 0; nCntX <= g_aMeshWall[nCnt].nWidth; nCntX++)
			{	//横
				//頂点情報の設定
				pVtx[0].pos = D3DXVECTOR3(-100.0f + (100.0f * nCntX), 50.0f - (50.0f * nCntY), 0.0f);		//幅、高さ

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
		g_pVtxBuffMeshWall[nCnt]->Unlock();

		int nCntIdx = 0;						//インデックスのカウンター

		//インデックスをロックし、頂点データへのポインタを取得
		g_pIdxBuffMeshWall[nCnt]->Lock(0, 0, (void**)&pIdx, 0);

		for (nCntY = 0; nCntY < g_aMeshWall[nCnt].nHeight; nCntY++)
		{
			for (nCntX = 0; nCntX <= g_aMeshWall[nCnt].nWidth; nCntX++, nCntIdx++)
			{
				pIdx[0] = (g_aMeshWall[nCnt].nWidth + 1) + nCntIdx;
				pIdx[1] = nCntIdx;
				pIdx += 2;

				if (nCntX == g_aMeshWall[nCnt].nWidth && nCntY < g_aMeshWall[nCnt].nHeight - 1)
				{
					pIdx[0] = nCntIdx;
					pIdx[1] = (g_aMeshWall[nCnt].nWidth + 1) + nCntIdx + 1;
					pIdx += 2;
				}
			}
		}

		//頂点バッファをアンロックする
		g_pIdxBuffMeshWall[nCnt]->Unlock();
	}
}

//=============================================================================
// 壁の設定
//=============================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight, int nTexType)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aMeshWall[nCntWall].bUse == false)
		{
			g_aMeshWall[nCntWall].pos = pos;
			g_aMeshWall[nCntWall].rot = rot;
			g_aMeshWall[nCntWall].nTexType = nTexType;
			g_aMeshWall[nCntWall].nWidth = nWidth;
			g_aMeshWall[nCntWall].nHeight = nHeight;
			g_aMeshWall[nCntWall].bUse = true;

			//自動計算
			g_aMeshWall[nCntWall].nNumVertexMeshWall = (g_aMeshWall[nCntWall].nHeight + 1) * (g_aMeshWall[nCntWall].nWidth + 1);
			g_aMeshWall[nCntWall].nNumIndexMeshWall = (g_aMeshWall[nCntWall].nWidth * g_aMeshWall[nCntWall].nHeight) * 2 + (4 * (g_aMeshWall[nCntWall].nHeight - 1)) + 2;
			g_aMeshWall[nCntWall].nNumPolygonMeshWall = (g_aMeshWall[nCntWall].nWidth * g_aMeshWall[nCntWall].nHeight) * 2 + (4 * (g_aMeshWall[nCntWall].nHeight - 1));

			break;
		}
	}
}