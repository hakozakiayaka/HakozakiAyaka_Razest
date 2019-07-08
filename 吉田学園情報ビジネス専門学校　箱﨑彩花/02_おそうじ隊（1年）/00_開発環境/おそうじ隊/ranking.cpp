//===============================================================================
//
// ランキング画面 [ranking.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include "fade.h"
#include "input.h"
#include "score.h"
#include "ranking.h"
#include "BG.h"
#include "sound.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define RANKING_TEX		"data/TEXTURE/number001.png"	// 読み込むテクスチャファイル名
#define MAX_TEX								(2)
#define RANKING_POS_X					(0)									//ランキングの左上X座標
#define RANKING_POS_Y					(0)									//ランキングの左上Y座標
#define RANKING_WIDTH					(SCREEN_WIDTH)			//ランキングの幅
#define RANKING_HEIGHT					(SCREEN_HEIGHT)			//ランキングの高さ
#define DUGIT_NUMBER					(8)									//スコアの桁数

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;	//頂点バッファへのポインタ
int g_nRanking;																			//ゲームのスコアを引き継ぐ変数
int g_nHighScore[5];																	//最初に入っているスコア[何段あるか]
int g_aRankingData[5][DUGIT_NUMBER];								//ランキング[何段あるか] [桁数]
int g_nChange;																			//ソートの仮置き
int g_nBoss;																					//ソートの仮置き
bool g_nKeep = true;																	//ランキングを保存する
int g_nCntTimeRanking;																//ランキング画面からタイトル画面への切り替えカウンター

//===============================================================================
//ランキング画面初期化処理
//===============================================================================
void InitRanking(void)
{
	//変数宣言
	VERTEX_2D * pVtx;							//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスへのポインタ

	//スコアの桁、構造体の初期化
	for (int nCntRanking2 = 0; nCntRanking2 < 5; nCntRanking2++)
	{
		for (int nCntRanking = 0; nCntRanking < DUGIT_NUMBER; nCntRanking++)
		{
			g_aRankingData[nCntRanking2][nCntRanking] = 0;
		}
	}

	//初期スコアの初期化
	if (g_nKeep == true)
	{
		g_nHighScore[0] = 50000;
		g_nHighScore[1] = 40000;
		g_nHighScore[2] = 30000;
		g_nHighScore[3] = 20000;
		g_nHighScore[4] = 10000;
		g_nKeep = false;
	}

	//ソートの仮置きの初期化
	g_nChange = 0;
	g_nBoss = 0;

	//画面切り替えのカウンター
	g_nCntTimeRanking = 0;

	//ランキング画面にハイスコアを設定
	SetRanking(GetScore());

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, RANKING_TEX, &g_pTextureRanking);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 5 * DUGIT_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRanking2 = 0; nCntRanking2 < 5; nCntRanking2++)
	{	//縦に並べる
		for (int nCntRanking = 0; nCntRanking < DUGIT_NUMBER; nCntRanking++)
		{	//桁数
			//	 頂点情報を設定
			pVtx[0].pos = D3DXVECTOR3(450.0f + (50.0f * nCntRanking), 200.0f + (100.0f * nCntRanking2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500.0f + (50.0f * nCntRanking), 200.0f + (100.0f * nCntRanking2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(450.0f + (50.0f * nCntRanking), 270.0f + (100.0f * nCntRanking2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(500.0f + (50.0f * nCntRanking), 270.0f + (100.0f * nCntRanking2), 0.0f);

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//	ポリゴンの色設定
			pVtx[0].col = D3DXCOLOR(0.5f, 0.7f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.7f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.7f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.7f, 1.0f, 1.0f);

			//	テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;	//頂点データのポインタを4つ分進める
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();

	//背景の初期化処理
	InitBG();
	SetBG(0);

	//毎回ゲームのスコアを更新
	InitScore();
}

//===============================================================================
//ランキング画面終了処理
//===============================================================================
void UninitRanking(void)
{
	//テクスチャの破棄
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	//背景の終了処理
	UninitBG();

	//毎回ゲームのスコアを更新
	UninitScore();
}

//===============================================================================
//ランキング画面更新処理
//===============================================================================
void UpdateRanking(void)
{
	//フェードを取得
	FADE g_fade = GetFade();

	//画面切り替えカウンター
	g_nCntTimeRanking++;

	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntRanking;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRanking2 = 0; nCntRanking2 < 5; nCntRanking2++)
	{
		for (nCntRanking = 0; nCntRanking < DUGIT_NUMBER; nCntRanking++)
		{
			//	テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aRankingData[nCntRanking2][nCntRanking] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aRankingData[nCntRanking2][nCntRanking] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aRankingData[nCntRanking2][nCntRanking] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aRankingData[nCntRanking2][nCntRanking] * 0.1f), 1.0f);

			pVtx += 4;	//頂点データのポインタを4つ分進める
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();

	//決定キーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true || g_nCntTimeRanking % 300 == 0)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);
		if (g_fade != FADE_OUT)
		{	//フェードアウト中にEnterキーを押せなくする
			//モード設定
			SetFade(MODE_TITLE);
		}
	}
	//背景の更新処理
	UpdateBG();

	//毎回ゲームのスコアを更新
	UpdateScore();
}

//===============================================================================
//ランキング画面描画処理
//===============================================================================
void DrawRanking(void)
{
	//背景の描画処理
	DrawBG();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスへのポインタ
	int nCntRanking;

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRanking);

	for (nCntRanking = 0; nCntRanking < DUGIT_NUMBER * 5; nCntRanking++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRanking, 2);
	}
}

//=============================================================================
 //ランキングの設定
//=============================================================================
void SetRanking(int nScore)
{
	//int nCntRanking;
	int nNum = 100000000;
	int nNum1 = 10000000;

	//ハイスコアと現在のスコアを比べる
	for (int nCntRanking2 = 0; nCntRanking2 < 5; nCntRanking2++)
	{
		if (nScore > g_nHighScore[nCntRanking2])
		{
			g_nChange = g_nHighScore[nCntRanking2];		//前回のハイスコアを仮置き
			g_nHighScore[nCntRanking2] = nScore;			//仮置きのハイスコアと比べて、今回のハイスコアを代入

			//順位の入れ替え
			for (int nCntJuni = nCntRanking2 + 1; nCntJuni < 5; nCntJuni++)
			{
				g_nBoss = g_nHighScore[nCntJuni];				//書き換えた順位の、次の順位を仮置き
				g_nHighScore[nCntJuni] = g_nChange;			//空いたところに、1つ上の順位を代入
				g_nChange = g_nBoss;									//終わり
			}
			break;
		}
	}

	//ランキング画面のスコア更新
	for (int nCntRanking2 = 0; nCntRanking2 < 5; nCntRanking2++)
	{
		for (int nCntRanking = 0; nCntRanking < DUGIT_NUMBER; nCntRanking++)
		{
			g_aRankingData[nCntRanking2][nCntRanking] = (g_nHighScore[nCntRanking2] %  nNum) / nNum1;
			nNum = nNum / 10;
			nNum1 = nNum1 / 10;

			if (nCntRanking == DUGIT_NUMBER - 1)
			{	//段数変わったら初期化する
				nNum = 100000000;
				nNum1 = 10000000;
			}
		}
	}

	//毎回ゲームのスコアの描画を更新
	DrawScore();
}