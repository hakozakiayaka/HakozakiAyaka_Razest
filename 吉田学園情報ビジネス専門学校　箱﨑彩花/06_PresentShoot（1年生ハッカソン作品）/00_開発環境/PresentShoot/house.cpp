//=============================================================================
//
// ハウス処理 [house.cpp]
// Author : 箱崎彩花
//
//=============================================================================
#include "house.h"
#include "main.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TEX	(5)				//読みこむテクスチャの最大数
#define MAX_HOUSE	(100)		//背景の最大数

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureHouse[MAX_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHouse = NULL;		//頂点バッファへのポインタ
House					g_House[MAX_HOUSE];				//情報設定
int						g_Move;							//移動した量
int						g_HouseNum;						//ハウスの番号

//=============================================================================
// スタートボタン初期化処理
//=============================================================================
void InitHouse(void)
{
	//変数宣言
	char	HouseName[MAX_TEX][48];		//ファイル名を格納する
	int		nCntTex;
	int     nCntHouse;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数の初期化
	for (nCntHouse = 0; nCntHouse < MAX_HOUSE; nCntHouse++)
	{
		g_House[nCntHouse].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//中心座標
		g_House[nCntHouse].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//色
		g_House[nCntHouse].fHight = 0.0f;								//高さ
		g_House[nCntHouse].fWidth = 0.0f;								//幅
		g_House[nCntHouse].nTexNum = 0;									//テクスチャの番号
		g_House[nCntHouse].Num = 0;										//番号
		g_House[nCntHouse].fHalfWidth = 0.0f;
		g_House[nCntHouse].fHalfHeght = 0.0f;
		g_House[nCntHouse].bUse = false;				//使用していない状態にする
	}
	g_Move = 0;		//移動量
	g_HouseNum = 0;	//家の番号

	//テクスチャファイル名を格納する
	wsprintf(&HouseName[0][0], "data\\TEXTURE\\house000.png");			//ハウス0
	wsprintf(&HouseName[1][0], "data\\TEXTURE\\house001.png");			//ハウス1
	wsprintf(&HouseName[2][0], "data\\TEXTURE\\house002.png");			//ハウス2
	wsprintf(&HouseName[3][0], "data\\TEXTURE\\house003.png");			//ハウス3
	wsprintf(&HouseName[4][0], "data\\TEXTURE\\tree.png");					//木

	//テクスチャの読み込み
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &HouseName[nCntTex][0],
								  &g_pTextureHouse[nCntTex]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HOUSE,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffHouse,
								NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffHouse->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTex = 0; nCntTex < MAX_HOUSE; nCntTex++)
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
	g_pVtxBuffHouse->Unlock();
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitHouse(void)
{
	//変数宣言
	int nCntTex;

	//テクスチャの破棄
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureHouse[nCntTex] != NULL)
		{
			g_pTextureHouse[nCntTex]->Release();
			g_pTextureHouse[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffHouse != NULL)
	{
		g_pVtxBuffHouse->Release();
		g_pVtxBuffHouse = NULL;
	}
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateHouse(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	int nCntHouse;
	float fScroll = -3.0f;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffHouse->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHouse = 0; nCntHouse < MAX_HOUSE; nCntHouse++)
	{
		if (g_House[nCntHouse].bUse == true)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_House[nCntHouse].pos.x - g_House[nCntHouse].fHalfWidth, g_House[nCntHouse].pos.y - g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_House[nCntHouse].pos.x + g_House[nCntHouse].fHalfWidth, g_House[nCntHouse].pos.y - g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_House[nCntHouse].pos.x - g_House[nCntHouse].fHalfWidth, g_House[nCntHouse].pos.y + g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_House[nCntHouse].pos.x + g_House[nCntHouse].fHalfWidth, g_House[nCntHouse].pos.y + g_House[nCntHouse].fHalfHeght, 0.0f);

			//位置更新
			g_House[nCntHouse].pos.x += fScroll;

			if (g_House[nCntHouse].Num == 28)
			{
				if (g_House[nCntHouse].pos.x == 500.0f)
				{
					SetGameState(GAMESTATE_END_CLIA);
				}
			}
		}

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffHouse->Unlock();
}

//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawHouse(void)
{
	//変数宣言
	int nCntHouse;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHouse, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntHouse = 0; nCntHouse < MAX_HOUSE; nCntHouse++)
	{
		if (g_House[nCntHouse].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureHouse[g_House[nCntHouse].nTexNum]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
								   nCntHouse * 4,			//開始する頂点のインデックス
								   2);								//プリミティブの数
		}
	}
}

//=============================================================================
// 情報設定
//=============================================================================
void SetHouse(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHight)
{
	//変数宣言
	int nCntHouse;

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffHouse->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntHouse = 0; nCntHouse < MAX_HOUSE; nCntHouse++)
	{
		if (g_House[nCntHouse].bUse == false)
		{
			//カウンターを加算
			g_HouseNum++;

			//家に番号付け
			g_House[nCntHouse].Num = g_HouseNum;

			g_House[nCntHouse].pos = pos;				//中心座標
			g_House[nCntHouse].fHight = fHight;		//高さ
			g_House[nCntHouse].fWidth = fWidth;		//幅
			g_House[nCntHouse].col = col;					//色

			//幅と高さを設定する
			g_House[nCntHouse].fHalfWidth = g_House[nCntHouse].fWidth * 0.5f;
			g_House[nCntHouse].fHalfHeght = g_House[nCntHouse].fHight * 0.5f;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos.x - g_House[nCntHouse].fHalfWidth, pos.y - g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + g_House[nCntHouse].fHalfWidth, pos.y - g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - g_House[nCntHouse].fHalfWidth, pos.y + g_House[nCntHouse].fHalfHeght, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + g_House[nCntHouse].fHalfWidth, pos.y + g_House[nCntHouse].fHalfHeght, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_House[nCntHouse].nTexNum = nTexNum;		//テクスチャの番号
			g_House[nCntHouse].bUse = true;					//使用している状態にする
			break;
		}

		//該当の位置まで進める
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffHouse->Unlock();
}

//=============================================================================
// 背景を消す
//=============================================================================
void DeleteHouse()
{
	//変数宣言
	int nCntHouse;

	for (nCntHouse = 0; nCntHouse < MAX_HOUSE; nCntHouse++)
	{
		if (g_House[nCntHouse].bUse == true)
		{
			g_House[nCntHouse].bUse = false;		//使用していない状態にする
		}
	}
}