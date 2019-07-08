//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "score.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define	DUGIT_NUMBER	(8)														//桁数

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
int g_nScore;																				// スコア
int g_aScoreData[DUGIT_NUMBER];											//桁

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntScore;

	// スコアの初期化
	 g_nScore = 0;

	 //スコアの桁、初期化処理
	 for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	 {
		 g_aScoreData[nCntScore] = 0;
	 }

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&g_pTextureScore);		// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexScore(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	// テクスチャの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntScore;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aScoreData[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aScoreData[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aScoreData[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f +(g_aScoreData[nCntScore] * 0.1f), 1.0f);

		//スコアの色設定
		pVtx[0].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.0f, 0.0f, 0.8f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntScore;

	//ステージを取得
	GAMESTAGE pStage;
	pStage = GetGameStage();

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	// ポリゴンの描画
	for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		if (pStage == GAMESTAGE1 || pStage == GAMESTAGE2)
		{	//おにぎりステージ1とピーマンステージ2の時にスコアを表示する
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntScore, 2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntScore;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * DUGIT_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	//スコアの座標設定
	for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		pVtx[0].pos = D3DXVECTOR3(870.0f + (50.0f * nCntScore), 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(920.0f + (50.0f * nCntScore), 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(870.0f + (50.0f * nCntScore), 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(920.0f + (50.0f * nCntScore), 60.0f, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue)
{
	int nNum = 100000000;
	int nNum1 = 10000000;
	int nCntScore;

	g_nScore += nValue;

	for (nCntScore = 0; nCntScore < DUGIT_NUMBER; nCntScore++)
	{
		g_aScoreData[nCntScore] = g_nScore %  nNum / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}