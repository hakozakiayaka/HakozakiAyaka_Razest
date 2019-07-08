//=============================================================================
//
// プレゼントの処理 [present.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "present.h"
#include "main.h"
#include "chimney.h"
#include "score.h"
#include "effect.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_TEX			(4)			//読みこむテクスチャの最大数
#define MAX_PRESENT		(100)		//背景の最大数
#define PRESENTSIE_L	(33)		//プレゼントのLサイズ
#define PRESENTSIE_M	(25)		//プレゼントのMサイズ
#define PRESENTSIE_S	(20)		//プレゼントのSサイズ
#define GRAVITY			(0.3f)		//重力
	
//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePresent[MAX_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPresent = NULL;		//頂点バッファへのポインタ
Present					g_Present[MAX_PRESENT];				//情報設定

//=============================================================================
// スタートボタン初期化処理
//=============================================================================
void InitPresent(void)
{
	//変数宣言
	char	PresentName[MAX_TEX][48];		//ファイル名を格納する
	int		nCntTex;
	int     nCntPresent;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//変数の初期化
	for (nCntPresent = 0; nCntPresent < MAX_PRESENT; nCntPresent++)
	{
		g_Present[nCntPresent].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//中心座標
		g_Present[nCntPresent].OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前回の位置
		g_Present[nCntPresent].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
		g_Present[nCntPresent].nTexNum = 0;									//テクスチャの番号
		g_Present[nCntPresent].fGravity = 0.0f;								//重力
		g_Present[nCntPresent].Type = PRESENTTYPE_MAX;						//プレゼントの種類
		g_Present[nCntPresent].bUse = false;								//使用していない状態にする
	}

	//テクスチャファイル名を格納する
	wsprintf(&PresentName[0][0], "data\\TEXTURE\\present_bag.png");		//袋
	wsprintf(&PresentName[1][0], "data\\TEXTURE\\present_L.png");		//Lサイズ
	wsprintf(&PresentName[2][0], "data\\TEXTURE\\present_M.png");		//Mサイズ
	wsprintf(&PresentName[3][0], "data\\TEXTURE\\present_S.png");		//Sサイズ

	//テクスチャの読み込み
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &PresentName[nCntTex][0],
								  &g_pTexturePresent[nCntTex]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PRESENT,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffPresent,
								NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPresent->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTex = 0; nCntTex < MAX_PRESENT; nCntTex++)
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
	g_pVtxBuffPresent->Unlock();
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitPresent(void)
{
	//変数宣言
	int nCntTex;

	//テクスチャの破棄
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTexturePresent[nCntTex] != NULL)
		{
			g_pTexturePresent[nCntTex]->Release();
			g_pTexturePresent[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPresent != NULL)
	{
		g_pVtxBuffPresent->Release();
		g_pVtxBuffPresent = NULL;
	}
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdatePresent(void)
{
	//変数宣言
	int nCntPresent;

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPresent->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPresent = 0; nCntPresent < MAX_PRESENT; nCntPresent++)
	{
		if (g_Present[nCntPresent].bUse == true)
		{
			//前回の位置を保存する
			g_Present[nCntPresent].OldPos = g_Present[nCntPresent].pos;

			//重力加算
			g_Present[nCntPresent].fGravity += GRAVITY;
			g_Present[nCntPresent].move.y = g_Present[nCntPresent].fGravity;

			//位置更新
			g_Present[nCntPresent].pos.y += g_Present[nCntPresent].move.y;

			//当たり判定
			if (g_Present[nCntPresent].Type == PRESENTTYPE_BAG)
			{
				if (CollisionChimney(&g_Present[nCntPresent].pos, &g_Present[nCntPresent].OldPos, PRESENTSIE_M, PRESENTSIE_M) == true)
				{//プレゼントを消す
					DeletePresent(nCntPresent, g_Present[nCntPresent].Type);
				}
			}
			else if (g_Present[nCntPresent].Type == PRESENTTYPE_L)
			{
				if (CollisionChimney(&g_Present[nCntPresent].pos, &g_Present[nCntPresent].OldPos, PRESENTSIE_L, PRESENTSIE_L) == true)
				{//プレゼントを消す
					DeletePresent(nCntPresent, g_Present[nCntPresent].Type);
				}
			}
			else if (g_Present[nCntPresent].Type == PRESENTTYPE_M)
			{
				if (CollisionChimney(&g_Present[nCntPresent].pos, &g_Present[nCntPresent].OldPos, PRESENTSIE_M, PRESENTSIE_M) == true)
				{//プレゼントを消す
					DeletePresent(nCntPresent, g_Present[nCntPresent].Type);
				}
			}
			else if (g_Present[nCntPresent].Type == PRESENTTYPE_S)
			{
				if (CollisionChimney(&g_Present[nCntPresent].pos, &g_Present[nCntPresent].OldPos, PRESENTSIE_S, PRESENTSIE_S) == true)
				{//プレゼントを消す
					DeletePresent(nCntPresent, g_Present[nCntPresent].Type);
				}
			}

			//画面外に出たら
			if (g_Present[nCntPresent].pos.y > SCREEN_HEIGHT + 100)
			{
				g_Present[nCntPresent].bUse = false;
			}
			
			if (g_Present[nCntPresent].nTexNum == 1)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_L, g_Present[nCntPresent].pos.y - PRESENTSIE_L, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_L, g_Present[nCntPresent].pos.y - PRESENTSIE_L, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_L, g_Present[nCntPresent].pos.y + PRESENTSIE_L, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_L, g_Present[nCntPresent].pos.y + PRESENTSIE_L, 0.0f);
			}
			else if (g_Present[nCntPresent].nTexNum == 3)
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_S, g_Present[nCntPresent].pos.y - PRESENTSIE_S, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_S, g_Present[nCntPresent].pos.y - PRESENTSIE_S, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_S, g_Present[nCntPresent].pos.y + PRESENTSIE_S, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_S, g_Present[nCntPresent].pos.y + PRESENTSIE_S, 0.0f);
			}
			else
			{
				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_M, g_Present[nCntPresent].pos.y - PRESENTSIE_M, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_M, g_Present[nCntPresent].pos.y - PRESENTSIE_M, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x - PRESENTSIE_M, g_Present[nCntPresent].pos.y + PRESENTSIE_M, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_Present[nCntPresent].pos.x + PRESENTSIE_M, g_Present[nCntPresent].pos.y + PRESENTSIE_M, 0.0f);
			}
		}

		//該当の位置まで進める
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPresent->Unlock();
}

//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawPresent(void)
{
	//変数宣言
	int nCntPresent;

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPresent, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPresent = 0; nCntPresent < MAX_PRESENT; nCntPresent++)
	{
		if (g_Present[nCntPresent].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePresent[g_Present[nCntPresent].nTexNum]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
								   nCntPresent * 4,			//開始する頂点のインデックス
								   2);						//プリミティブの数
		}
	}
}

//=============================================================================
// 情報設定
//=============================================================================
void SetPresent(int nTexNum, D3DXVECTOR3 pos)
{
	//変数宣言
	int nCntPresent;
	
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPresent->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPresent = 0; nCntPresent < MAX_PRESENT; nCntPresent++)
	{
		if (g_Present[nCntPresent].bUse == false)
		{
			g_Present[nCntPresent].pos = pos;				//中心座標
			g_Present[nCntPresent].nTexNum = nTexNum;		//テクスチャの番号

			if (g_Present[nCntPresent].nTexNum == 0)
			{
				//タイプの設定
				g_Present[nCntPresent].Type = PRESENTTYPE_BAG;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(pos.x - PRESENTSIE_M, pos.y - PRESENTSIE_M, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pos.x + PRESENTSIE_M, pos.y - PRESENTSIE_M, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pos.x - PRESENTSIE_M, pos.y + PRESENTSIE_M, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pos.x + PRESENTSIE_M, pos.y + PRESENTSIE_M, 0.0f);
			}
			else if (g_Present[nCntPresent].nTexNum == 1)
			{
				//タイプの設定
				g_Present[nCntPresent].Type = PRESENTTYPE_L;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(pos.x - PRESENTSIE_L, pos.y - PRESENTSIE_L, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pos.x + PRESENTSIE_L, pos.y - PRESENTSIE_L, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pos.x - PRESENTSIE_L, pos.y + PRESENTSIE_L, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pos.x + PRESENTSIE_L, pos.y + PRESENTSIE_L, 0.0f);
			}
			else if (g_Present[nCntPresent].nTexNum == 2)
			{
				//タイプの設定
				g_Present[nCntPresent].Type = PRESENTTYPE_M;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(pos.x - PRESENTSIE_M, pos.y - PRESENTSIE_M, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pos.x + PRESENTSIE_M, pos.y - PRESENTSIE_M, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pos.x - PRESENTSIE_M, pos.y + PRESENTSIE_M, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pos.x + PRESENTSIE_M, pos.y + PRESENTSIE_M, 0.0f);
			}
			else if (g_Present[nCntPresent].nTexNum == 3)
			{
				//タイプの設定
				g_Present[nCntPresent].Type = PRESENTTYPE_S;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(pos.x - PRESENTSIE_S, pos.y - PRESENTSIE_S, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pos.x + PRESENTSIE_S, pos.y - PRESENTSIE_S, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pos.x - PRESENTSIE_S, pos.y + PRESENTSIE_S, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pos.x + PRESENTSIE_S, pos.y + PRESENTSIE_S, 0.0f);
			}
			
			g_Present[nCntPresent].fGravity = 0.0f;		//重力
			g_Present[nCntPresent].bUse = true;			//使用している状態にする
			break;
		}

		//該当の位置まで進める
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPresent->Unlock();
}

//=============================================================================
// 情報設定
//=============================================================================
void DeletePresent(int nCntPresent, PRESENTTYPE type)
{
	if (g_Present[nCntPresent].bUse == true)
	{
		PlaySound(SOUND_LABEL_SE_ITEM);

		if (type == PRESENTTYPE_BAG)
		{
			AddScore(250);
		}
		else if (type == PRESENTTYPE_L)
		{
			AddScore(500);
		}
		else if (type == PRESENTTYPE_M)
		{
			AddScore(200);
		}
		else if (type == PRESENTTYPE_S)
		{
			AddScore(100);
		}

		g_Present[nCntPresent].bUse = false;
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 5.0f, 1);
		SetEffect(g_Present[nCntPresent].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 5.0f, 1);
	}
}