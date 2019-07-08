//=============================================================================
//
// ライフ処理 [life.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "life.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_LIFE		"data/TEXTURE/life001.png"	// 読み込むテクスチャファイル名

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		// 頂点バッファへのポインタ
int g_nLife;																				//ライフ
bool g_bUse[MAXPLAYER_LIFE];

//=============================================================================
// 初期化処理
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntLife;

	//ライフの初期化
	 g_nLife = 0;

	 //ライフが使われているかどうか
	 for (nCntLife = 0; nCntLife < MAXPLAYER_LIFE; nCntLife++)
	 {
		 g_bUse[nCntLife] = true;
	 }

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
								TEXTURE_LIFE,			// ファイルの名前
								&g_pTextureLife);		// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexLife(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLife(void)
{
	// テクスチャの開放
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLife(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntLife;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAXPLAYER_LIFE; nCntLife++)
	{
		if (g_bUse[nCntLife] == true)
		{
			//テクスチャの座標設定
			pVtx[0].pos = D3DXVECTOR3(0.0f + (60.0f * (MAXPLAYER_LIFE - nCntLife - 1)), 5.0f , 0.0f);
			pVtx[1].pos = D3DXVECTOR3(50.0f + (60.0f * (MAXPLAYER_LIFE - nCntLife - 1)), 5.0f , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f + (60.0f * (MAXPLAYER_LIFE - nCntLife - 1)), 55.0f , 0.0f);
			pVtx[3].pos = D3DXVECTOR3(50.0f + (60.0f * (MAXPLAYER_LIFE - nCntLife - 1)), 55.0f , 0.0f);
		}
		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntLife;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	// ポリゴンの描画
	for (nCntLife = 0; nCntLife < MAXPLAYER_LIFE; nCntLife++)
	{
		if (g_bUse[nCntLife] == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureLife);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntLife, 2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntLife;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAXPLAYER_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	//ライフテクスチャの座標設定
	for (nCntLife = 0; nCntLife < MAXPLAYER_LIFE; nCntLife++)
	{
		pVtx[0].pos = D3DXVECTOR3(0.0f + (40 * nCntLife), 200.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(60.0f + (40 * nCntLife), 200.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f + (40 * nCntLife), 250.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(60.0f + (40 * nCntLife), 250.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// ライフの設定
//=============================================================================
void SetLife(int nLifeDown)
{
	int nCntLife;
	int nLostLife = 0;

	nLostLife = MAXPLAYER_LIFE - nLifeDown;

	for (nCntLife = 0; nCntLife < nLostLife; nCntLife++)
	{
		if (g_bUse[nCntLife] == true)
		{
			g_bUse[nCntLife] = false;
		}
	}
}