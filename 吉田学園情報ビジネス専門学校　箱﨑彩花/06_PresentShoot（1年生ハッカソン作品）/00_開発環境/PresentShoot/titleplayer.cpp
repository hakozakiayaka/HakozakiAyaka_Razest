//=============================================================================
//
// プレーヤー処理 [titleplayer.cpp]
// Author : 高橋美優
//
//=============================================================================
#include "titleplayer.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "game.h"
#include "effect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURENAME		"data\\TEXTURE\\santa.png"		//読みこむテクスチャの名前
#define TITLEPLAYER_ANIM		(20.0f)

//=============================================================================
// グローバル変数
//=============================================================================
//VERTEX_2D				g_aVertex[4];				//頂点情報を格納する
LPDIRECT3DTEXTURE9		g_pTextureTitlePlayer = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitlePlayer = NULL;	//頂点バッファへのポインタ
TitlePlayer				g_player;					//プレイヤーのポインタ

//=============================================================================
//	頂点情報の設定
//=============================================================================
void InitTitlePlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//初期化処理
	g_player.nCounterAnim = 0;							//カウンターを初期化する
	g_player.nPatternAnim = 0;							//パターンNo.を初期化する
	g_player.pos = D3DXVECTOR3(640.0f, 500.0f, 0.0f);	//初期位置
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
	g_player.posMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期値
	g_player.nDirectionMove = 0;
	g_player.bDisp = true;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
								TEXTURENAME,
								&g_pTextureTitlePlayer);

	//頂点バッファの生成
	pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D)*4,
								  D3DUSAGE_WRITEONLY,
								  FVF_VERTEX_2D,
								  D3DPOOL_MANAGED,
								  &g_pVtxBuffTitlePlayer,
								  NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitlePlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitlePlayer->Unlock();
}

//========================================================================================
//終了処理
//========================================================================================
void UninitTitlePlayer(void)
{
	//テクスチャの破棄
	if (g_pTextureTitlePlayer != NULL)
	{
		g_pTextureTitlePlayer->Release();
		g_pTextureTitlePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitlePlayer != NULL)
	{
		g_pVtxBuffTitlePlayer->Release();
		g_pVtxBuffTitlePlayer = NULL;
	}
}

//========================================================================================
//更新処理
//========================================================================================
void UpdateTitlePlayer(void)
{
	//変数宣言
	g_player.nCounterAnim++;

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	if (g_player.bDisp == true)
	{
		//前回の位置を保存
		g_player.posOld = g_player.pos;

		//エフェクト
		SetEffect(g_player.pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 2.0f, 1);

		g_player.nDirectionMove = 0;

		//アニメーションの処理
		if ((g_player.nCounterAnim % 30) == 0)
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffTitlePlayer->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の設定
		if (g_player.nDirectionMove == 0)
		{//右向きの時
			pVtx[1].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[0].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 1.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 1.0f);
		}
		if (g_player.nDirectionMove == 1)
		{//左に向いているとき
			pVtx[0].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 1.0f);
		}
	
		//頂点バッファをアンロックする
		g_pVtxBuffTitlePlayer->Unlock();
	}
}

//========================================================================================
//描画処理
//========================================================================================
void DrawTitlePlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

		//デバイスの取得
		pDevice = GetDevice();

		//頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffTitlePlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitlePlayer);

		if (g_player.bDisp == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
}

//========================================================================================
//プレイヤーの情報
//========================================================================================
TitlePlayer *GetTitlePlayer(void)
{
	return &g_player;
}