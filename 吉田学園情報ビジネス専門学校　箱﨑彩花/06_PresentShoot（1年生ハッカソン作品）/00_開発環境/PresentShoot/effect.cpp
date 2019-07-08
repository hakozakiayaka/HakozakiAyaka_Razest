//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "effect.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EFFECT00	"data/TEXTURE/effect000.jpg"	// 読み込むテクスチャファイル名
#define TEXTURE_EFFECT01	"data/TEXTURE/star000.jpg"		// 読みこむテクスチャファイル名
#define MAX_TEXTURE			(2)								// テクスチャの最大数
#define	MAX_EFFECT			(4096)							// エフェクトの最大数
#define EFFECT_LIFE			(150)							// 表示時間
#define EFFECT_LIFE2		(20)							// 表示時間 
#define EFFECT_MOVE			(-1.5f)							// 移動量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect[MAX_TEXTURE] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファへのポインタ
EFFECT					g_aEffect[MAX_EFFECT];		// エフェクトの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].fChngeRadius = 0.0f;
		g_aEffect[nCntEffect].fRadiusCnt = 0.0f;
		g_aEffect[nCntEffect].fAngle = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].nTexType = 0;
		g_aEffect[nCntEffect].fGravity = 0.0f;
		g_aEffect[nCntEffect].bAngle = false;
		g_aEffect[nCntEffect].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
							  TEXTURE_EFFECT00,
							  &g_pTextureEffect[0]);

	D3DXCreateTextureFromFile(pDevice,
							 TEXTURE_EFFECT01,
							 &g_pTextureEffect[1]);

	// 頂点情報の作成
	MakeVertexEffect(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	//変数宣言
	int nCntTex;

	//テクスチャの破棄
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (g_pTextureEffect[nCntTex] != NULL)
		{
			g_pTextureEffect[nCntTex]->Release();
			g_pTextureEffect[nCntTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	//変数宣言
	int nCntEffect;

	// 頂点バッファの情報を設定
	VERTEX_2D*pVtx;					//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)		//エフェクトが使用されている
		{
			//ライフのカウントダウン
			g_aEffect[nCntEffect].nLife--;

			//半径を大きくする
			g_aEffect[nCntEffect].fRadius += 0.3f;

			//エフェクトを消す処理
			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].col.a -= 0.1f;

				if (g_aEffect[nCntEffect].col.a <= 0.0f)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
			}

			//プレイヤーの情報を取得
			Player * pPlayer;
			pPlayer = GetPlayer();

			//移動する
			g_aEffect[nCntEffect].move.x = 2.0f;

			if (g_aEffect[nCntEffect].bAngle == false)
			{
				//角度判定をした状態に設定
				g_aEffect[nCntEffect].bAngle = true;

				//移動座標を求める
				g_aEffect[nCntEffect].fAngle = atan2f(rand() % 100, rand() % 100);

				g_aEffect[nCntEffect].move.x = sinf(g_aEffect[nCntEffect].fAngle) * 3.0f;
				g_aEffect[nCntEffect].move.y = cosf(g_aEffect[nCntEffect].fAngle) * -3.0f;
			}

			//位置の更新
			if (pPlayer->nDirectionMove == 0)
			{
				g_aEffect[nCntEffect].pos.x -= g_aEffect[nCntEffect].move.x;
				g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

				//移動する
				g_aEffect[nCntEffect].move.x = -1.5f;
			}
			else if (pPlayer->nDirectionMove == 1)
			{
				g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;
				g_aEffect[nCntEffect].pos.y += g_aEffect[nCntEffect].move.y;

				//移動する
				g_aEffect[nCntEffect].move.x = 1.5f;
			}

			//位置を更新
			g_aEffect[nCntEffect].pos.x += g_aEffect[nCntEffect].move.x;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
			pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
			pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
			pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
		}

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{
	//変数宣言
	int nCntEffect;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ポリゴンの描画
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)		//エフェクトが使用されている
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].nTexType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEffect * 4,
				2);
		}
	}

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 頂点の作成
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	int nCntEffect;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// 頂点バッファの情報を設定
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0);

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
	g_pVtxBuffEffect->Unlock();
}


//=============================================================================
// エフェクト設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int TexType)
{
	//変数宣言
	int nCntEffect;
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)		//エフェクトが使用されてない
		{
			g_aEffect[nCntEffect].pos = pos;			//座標
			g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(pos.x - g_aEffect[nCntEffect].fRadius, pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pos.x + g_aEffect[nCntEffect].fRadius, pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pos.x - g_aEffect[nCntEffect].fRadius, pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pos.x + g_aEffect[nCntEffect].fRadius, pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			g_aEffect[nCntEffect].col = col;			//色

		    //頂点カラーの設定
 			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_aEffect[nCntEffect].fRadius = fRadius;				//半径
			g_aEffect[nCntEffect].fGravity = 0.0f;					//重力
			g_aEffect[nCntEffect].fAngle = 0.0f;					//角度
			g_aEffect[nCntEffect].nTexType = TexType;				//テクスチャのタイプ
			g_aEffect[nCntEffect].nLife = 30;						//エフェクトのライフ
			
			g_aEffect[nCntEffect].bAngle = false;		//角度を判定してるかどうか
			g_aEffect[nCntEffect].bUse    = true;		//使用している状態にする
			break;
		}

		//該当の位置まで進める
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}