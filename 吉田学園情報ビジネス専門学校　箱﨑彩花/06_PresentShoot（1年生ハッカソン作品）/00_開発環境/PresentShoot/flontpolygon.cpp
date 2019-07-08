//=============================================================================
//
// ポリゴン処理 [flontpolygon.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "flontpolygon.h"
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TEX	(5)				//読みこむテクスチャの最大数
#define MAX_POLYGON	(10)		//背景の最大数

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureFlontPolygon[MAX_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFlontPolygon = NULL;		//頂点バッファへのポインタ
FlontPolygon					g_FlontPolygon[MAX_POLYGON];				//情報設定

//=============================================================================
// スタートボタン初期化処理
//=============================================================================
void InitFlontPolygon(void)
{
	//変数宣言
	char	FlontPolygonName[MAX_TEX][48];		//ファイル名を格納する
	int		nCntTex;
	int     nCntFlontPolygon;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数の初期化
	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_POLYGON; nCntFlontPolygon++)
	{
		g_FlontPolygon[nCntFlontPolygon].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//中心座標
		g_FlontPolygon[nCntFlontPolygon].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//色
		g_FlontPolygon[nCntFlontPolygon].fHight = 0.0f;								//高さ
		g_FlontPolygon[nCntFlontPolygon].fWidth = 0.0f;								//幅
		g_FlontPolygon[nCntFlontPolygon].nTexNum = 0;				//テクスチャの番号
		g_FlontPolygon[nCntFlontPolygon].bUse = false;				//使用していない状態にする
	}

	//テクスチャファイル名を格納する
	wsprintf(&FlontPolygonName[0][0], "data\\TEXTURE\\title_logo.png");		//タイトルロゴ
	wsprintf(&FlontPolygonName[1][0], "data\\TEXTURE\\flam002.png");			//ポーズ台紙
	wsprintf(&FlontPolygonName[2][0], "data\\TEXTURE\\GAMECLEAR.png");		//タイトルロゴ
	wsprintf(&FlontPolygonName[3][0], "data\\TEXTURE\\GAMEOVER.png");			//ポーズ台紙
	wsprintf(&FlontPolygonName[4][0], "data\\TEXTURE\\score_logo.png");			//ポーズ台紙


	//テクスチャの読み込み
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &FlontPolygonName[nCntTex][0],
								  &g_pTextureFlontPolygon[nCntTex]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffFlontPolygon,
								NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTex = 0; nCntTex < MAX_POLYGON; nCntTex++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFlontPolygon->Unlock();
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitFlontPolygon(void)
{
	//変数宣言
	int nCntTex;

	//テクスチャの破棄
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureFlontPolygon[nCntTex] != NULL)
		{
			g_pTextureFlontPolygon[nCntTex]->Release();
			g_pTextureFlontPolygon[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffFlontPolygon != NULL)
	{
		g_pVtxBuffFlontPolygon->Release();
		g_pVtxBuffFlontPolygon = NULL;
	}
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateFlontPolygon(void)
{
}

//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawFlontPolygon(void)
{
	//変数宣言
	int nCntFlontPolygon;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFlontPolygon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_POLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureFlontPolygon[g_FlontPolygon[nCntFlontPolygon].nTexNum]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
								   nCntFlontPolygon * 4,			//開始する頂点のインデックス
								   2);						//プリミティブの数
		}
	}
}

//=============================================================================
// 情報設定
//=============================================================================
void SetFlontPolygon(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHight)
{
	//変数宣言
	int nCntFlontPolygon;
	float fHalfWidth = 0;		//幅
	float fHalfHight = 0;		//高さ

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFlontPolygon->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_POLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == false)
		{
			g_FlontPolygon[nCntFlontPolygon].pos = pos;				//中心座標
			g_FlontPolygon[nCntFlontPolygon].fHight = fHight;			//高さ
			g_FlontPolygon[nCntFlontPolygon].fWidth = fWidth;			//幅
			g_FlontPolygon[nCntFlontPolygon].col = col;				//色

			//幅と高さを設定する
			fHalfWidth = g_FlontPolygon[nCntFlontPolygon].fWidth * 0.5f;
			fHalfHight = g_FlontPolygon[nCntFlontPolygon].fHight * 0.5f;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos.x - fHalfWidth, pos.y - fHalfHight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + fHalfWidth, pos.y - fHalfHight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - fHalfWidth, pos.y + fHalfHight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + fHalfWidth, pos.y + fHalfHight, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_FlontPolygon[nCntFlontPolygon].nTexNum = nTexNum;		//テクスチャの番号
			g_FlontPolygon[nCntFlontPolygon].bUse = true;			//使用している状態にする
			break;
		}

		//該当の位置まで進める
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffFlontPolygon->Unlock();
}

//=============================================================================
// 背景を消す
//=============================================================================
void DeleteFlontPolygon()
{
	//変数宣言
	int nCntFlontPolygon;

	for (nCntFlontPolygon = 0; nCntFlontPolygon < MAX_POLYGON; nCntFlontPolygon++)
	{
		if (g_FlontPolygon[nCntFlontPolygon].bUse == true)
		{
			g_FlontPolygon[nCntFlontPolygon].bUse = false;		//使用していない状態にする
		}
	}
}