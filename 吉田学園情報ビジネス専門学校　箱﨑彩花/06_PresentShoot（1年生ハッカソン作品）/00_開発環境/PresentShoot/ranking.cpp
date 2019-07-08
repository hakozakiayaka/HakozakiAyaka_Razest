//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : 
//
//=============================================================================
#include "ranking.h"
#include "flontpolygon.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_HIGHSCORE		"data/TEXTURE/number001.png"	// 読み込むテクスチャファイル名
#define NUM_HIGHSCORE			(8)								//スコアの桁数
#define MOVE_POS				(80.0f)							//移動量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexHighScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureHighScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHighScore = NULL;		// 頂点バッファへのポインタ
int						g_nHighScore;					// スコア
int						g_nScore2;
int						g_aHighNum[NUM_HIGHSCORE];			// １桁に数字を格納する変数

//=============================================================================
// 初期化処理
//=============================================================================
void InitHighScore(void)
{
	//変数宣言
	int nCntNum;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nHighScore = 0;
	g_nScore2 = 0;

	for (nCntNum = 0; nCntNum < NUM_HIGHSCORE; nCntNum++)
	{
		g_aHighNum[nCntNum] = 0;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_HIGHSCORE,		// ファイルの名前
		&g_pTextureHighScore);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexHighScore(pDevice);

	//タイトルロゴのセット
	SetFlontPolygon(4, D3DXVECTOR3(640.0f, 200.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 400.0f, 100.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitHighScore(void)
{
	// テクスチャの開放
	if (g_pTextureHighScore != NULL)
	{
		g_pTextureHighScore->Release();
		g_pTextureHighScore = NULL;
	}

	// 頂点バッファの開放
	if (g_pTextureHighScore != NULL)
	{
		g_pTextureHighScore->Release();
		g_pTextureHighScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateHighScore(void)
{
	//変数宣言
	int nCntHighScore;

	// 頂点情報を設定
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHighScore = 0; nCntHighScore < NUM_HIGHSCORE; nCntHighScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aHighNum[nCntHighScore]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aHighNum[nCntHighScore]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aHighNum[nCntHighScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aHighNum[nCntHighScore]), 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffHighScore->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawHighScore(void)
{
	//変数宣言
	int nCntHighScore;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHighScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureHighScore);

	// ポリゴンの描画
	for (nCntHighScore = 0; nCntHighScore < NUM_HIGHSCORE; nCntHighScore++)
	{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntHighScore * 4,
			2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexHighScore(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	int nCntHighScore;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_HIGHSCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHighScore,
		NULL);

	// 頂点情報を設定
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

							//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHighScore = 0; nCntHighScore < NUM_HIGHSCORE; nCntHighScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(300.0f + 0.0f + (MOVE_POS * nCntHighScore), 300.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(300.0f + MOVE_POS + (MOVE_POS * nCntHighScore), 300.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f + 0.0f + (MOVE_POS * nCntHighScore), 200.0f + 300.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(300.0f + MOVE_POS + (MOVE_POS * nCntHighScore), 200.0f + 300.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.1f, 0.0f, 0.4f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.1f, 0.0f, 0.4f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.1f, 0.0f, 0.4f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.1f, 0.0f, 0.4f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffHighScore->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void SetHighScore(int nScore)
{
	int nCntNum;			//スコアの桁数のカウンター
 	int nNum = 100000000;
	int nNum2 = 10000000;
	g_nScore2 = nScore;

	if (g_nHighScore < g_nScore2)
	{
		g_nHighScore = g_nScore2;
	}

	for (nCntNum = 0; nCntNum < NUM_HIGHSCORE; nCntNum++)
	{
		g_aHighNum[nCntNum] = (g_nHighScore % nNum) / nNum2;	//格納する数字を計算

														//桁数を１桁減らす
		nNum = nNum / 10;
		nNum2 = nNum2 / 10;

		if (nCntNum == NUM_HIGHSCORE - 1)
		{//初期化する
			nNum = 100000000;
			nNum2 = 10000000;
		}
	}
}