//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "ranking.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_RANKSCORE		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define	DUGIT_NUMBER	(8)	//桁数
//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexRankScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureRankScore = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		// 頂点バッファへのポインタ
int g_nRankScore;																				// ランキング
//int g_aRankScoreData[8];																	//桁

//=============================================================================
// 初期化処理
//=============================================================================
void InitRankScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ランキングの初期化
	 g_nRankScore = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_RANKSCORE,			// ファイルの名前
								&g_pTextureRankScore);		// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexRankScore(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRankScore(void)
{
	// テクスチャの開放
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRankScore(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntRankScore;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRankScore = 0; nCntRankScore < DUGIT_NUMBER; nCntRankScore++)
	{
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nRankScore * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_nRankScore * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_nRankScore * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (g_nRankScore * 0.1f), 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRankScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntRankScore;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankScore);

	// ポリゴンの描画
	for (nCntRankScore = 0; nCntRankScore < DUGIT_NUMBER; nCntRankScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRankScore, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexRankScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntRankScore;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * DUGIT_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	//ランキングの座標設定
	for (nCntRankScore = 0; nCntRankScore < DUGIT_NUMBER; nCntRankScore++)
	{
		pVtx[0].pos = D3DXVECTOR3(870.0f + (50.0f * nCntRankScore), 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(920.0f + (50.0f * nCntRankScore), 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(870.0f + (50.0f * nCntRankScore), 75.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(920.0f + (50.0f * nCntRankScore), 75.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();
}

//=============================================================================
// ランキングの設定
//=============================================================================
void SetRankScore(int nScore)
{
	if (nScore > g_nRankScore)
	{
		g_nRankScore = nScore;
	}
}