//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number001.png"	// 読み込むテクスチャファイル名
#define NUM_SCORE			(8)								//スコアの桁数
#define MOVE_POS			(30.0f)							//移動量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
int						g_nScore;					// スコア
int						g_aNum[NUM_SCORE];			// １桁に数字を格納する変数

//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	//変数宣言
	int nCntNum;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// スコアの初期化
	g_nScore = 0;

	for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
	{
		g_aNum[nCntNum] = 0;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&g_pTextureScore);	// テクスチャへのポインタ

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
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	//変数宣言
	int nCntScore;

	// 頂点情報を設定
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aNum[nCntScore]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aNum[nCntScore]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aNum[nCntScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aNum[nCntScore]), 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{	
	//変数宣言
	int nCntScore;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	// ポリゴンの描画
	for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
								nCntScore * 4,
								2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	int nCntScore;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// 頂点情報を設定
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(1020.0f + 0.0f + (MOVE_POS * nCntScore), 10.0f , 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1020.0f + MOVE_POS + (MOVE_POS * nCntScore), 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1020.0f + 0.0f + (MOVE_POS * nCntScore), 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1020.0f + MOVE_POS + (MOVE_POS * nCntScore), 60.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue)
{
	int nCntNum;			//スコアの桁数のカウンター
	int nNum = 100000000;
	int nNum2 = 10000000;

	//スコア加算
	g_nScore += nValue;

	for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
	{
 		g_aNum[nCntNum] = (g_nScore % nNum) / nNum2;	//格納する数字を計算

		//桁数を１桁減らす
		nNum = nNum / 10;
		nNum2 = nNum2 / 10;

		if (nCntNum == NUM_SCORE - 1)
		{//初期化する
			nNum = 100000000;
			nNum2 = 10000000;
		}
	}
}

//========================================================================================
//終了処理
//========================================================================================
int GetScore(void)
{
	return g_nScore;
}
