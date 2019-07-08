//=============================================================================
//
// 煙突の処理 [chimney.cpp]
// Author : 佐藤安純
//
//=============================================================================
#include "chimney.h"
#include "main.h"
#include "sound.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_CHIMNEY		(120)							//ブロックの最大数
#define CHIMNEY_IMAGE	"data\\TEXTURE\\chimney.png"	//ブロックのテクスチャ

//=============================================================================
// グローバル変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureChimney = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffChimney = NULL;		// 頂点バッファへのポインタ
Chimney					g_aChimney[MAX_CHIMNEY];		// ブロックの情報
int						g_nCntItemChimney;			// アイテムブロックカウンター

//=============================================================================
// 初期化処理
//=============================================================================
void InitChimney(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	int nCntChimney;

	// デバイスの取得
	pDevice = GetDevice();

	// ブロックの情報の初期化
	for(nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		g_aChimney[nCntChimney].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
		g_aChimney[nCntChimney].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
		g_aChimney[nCntChimney].fWidth = 0.0f;							//幅
		g_aChimney[nCntChimney].fHight = 0.0f;							//高さ
		g_aChimney[nCntChimney].nCounterMove = 0;						//移動量のカウンター
		g_aChimney[nCntChimney].bIn = false;							//煙突に入っているかどうか
		g_aChimney[nCntChimney].bUse = false;							//ブロックを使用しているかどうか
	}
	g_nCntItemChimney = 0;											//アイテムブロックカウンター

	D3DXCreateTextureFromFile(pDevice,
							  CHIMNEY_IMAGE,
							  &g_pTextureChimney);

	// 頂点情報の作成
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_CHIMNEY,
						 D3DUSAGE_WRITEONLY,
						 FVF_VERTEX_2D,
						 D3DPOOL_MANAGED,
						 &g_pVtxBuffChimney,
						 NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffChimney->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

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

		pVtx += 4;		//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffChimney->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitChimney(void)
{
	// テクスチャの開放
	if (g_pTextureChimney != NULL)
	{
		g_pTextureChimney->Release();
		g_pTextureChimney = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffChimney != NULL)
	{
		g_pVtxBuffChimney->Release();
		g_pVtxBuffChimney = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateChimney(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	int nCntChimney;
	float fScroll = -3.0f;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffChimney->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		if (g_aChimney[nCntChimney].bUse == true)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aChimney[nCntChimney].pos.x - g_aChimney[nCntChimney].fWidth, g_aChimney[nCntChimney].pos.y - g_aChimney[nCntChimney].fHight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aChimney[nCntChimney].pos.x + g_aChimney[nCntChimney].fWidth, g_aChimney[nCntChimney].pos.y - g_aChimney[nCntChimney].fHight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aChimney[nCntChimney].pos.x - g_aChimney[nCntChimney].fWidth, g_aChimney[nCntChimney].pos.y + g_aChimney[nCntChimney].fHight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aChimney[nCntChimney].pos.x + g_aChimney[nCntChimney].fWidth, g_aChimney[nCntChimney].pos.y + g_aChimney[nCntChimney].fHight, 0.0f);

			//位置更新
			g_aChimney[nCntChimney].pos.x += fScroll;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffChimney->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawChimney(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	int nCntChimney;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffChimney, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		if (g_aChimney[nCntChimney].bUse == true)		//ブロックが使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureChimney);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
								   nCntChimney * 4,
								   2);
		}
	}
}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void SetChimney(D3DXVECTOR3 pos, float fWidth, float fHight)
{
	//変数宣言
	int nCntChimney;
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffChimney->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		if (g_aChimney[nCntChimney].bUse == false)		//ブロックが使用されてない
		{
			g_aChimney[nCntChimney].pos = pos;			//座標
			g_aChimney[nCntChimney].fWidth = fWidth;	//幅
			g_aChimney[nCntChimney].fHight = fHight;	//高さ

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHight, 0.0f);

			g_aChimney[nCntChimney].bUse = true;				//使用している状態にする
			break;
		}

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffChimney->Unlock();
}

//=============================================================================
// ブロックの当たり判定
//=============================================================================
bool CollisionChimney(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fWhidth, float fHeight)
{
	bool bLand = false;		//着地しているかどうか
	int nCntChimney;

	for (nCntChimney = 0; nCntChimney < MAX_CHIMNEY; nCntChimney++)
	{
		if (g_aChimney[nCntChimney].bUse == true)
		{
			g_aChimney[nCntChimney].bIn = false;	//着地していない状態にする

			if (pPos->x > g_aChimney[nCntChimney].pos.x - g_aChimney[nCntChimney].fWidth&&
				pPos->x < g_aChimney[nCntChimney].pos.x + g_aChimney[nCntChimney].fWidth)
			{//プレイヤーがブロックの幅に入っているかどうか

				//上の判定
				if (pPosOld->y <= g_aChimney[nCntChimney].pos.y && pPos->y >= g_aChimney[nCntChimney].pos.y)
				{//前回の位置が地面より上にある

					bLand = true;								//着地した状態にする
					g_aChimney[nCntChimney].bIn = true;			//着地した状態にする
				}

			}
		}
	}
	return bLand;
}

//=============================================================================
// ブロック情報の取得
//=============================================================================
Chimney *GetChimney(void)
{
	return &g_aChimney[0];
}