//===============================================================================
//
// ポーズメニュー処理 [pausemenu.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include"pausemenu.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define PAUSEMENU_TEXTURE	 "data/TEXTURE/pause100.png"		//読み込むテクスチャ
#define PAUSEMENU_POS_X						(0)													//背景の左上X座標
#define PAUSEMENU_POS_Y						(0)													//背景の左上Y座標
#define PAUSEMENU_WIDTH						(SCREEN_WIDTH)							//背景の幅
#define PAUSEMENU_HEIGHT					(SCREEN_HEIGHT)							//背景の高さ

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePauseMenu = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL;	//頂点バッファへのポインタ

//===============================================================================
//ポーズメニュー初期化処理
//===============================================================================
void InitPauseMenu(void)
{
	//変数宣言
	VERTEX_2D * pVtx;						//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスを取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PAUSEMENU_TEXTURE, &g_pTexturePauseMenu);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMenu,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	//背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(PAUSEMENU_POS_X, PAUSEMENU_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSEMENU_WIDTH, PAUSEMENU_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSEMENU_POS_X, PAUSEMENU_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSEMENU_WIDTH, PAUSEMENU_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//背景色設定
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);

	//背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//===============================================================================
	//ポーズメニュー背景の座標設定
	pVtx[4].pos = D3DXVECTOR3(430, 200, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(790, 200, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(430, 560, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(790, 560, 0.0f);

	//rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//ポーズメニューの色設定
	pVtx[4].col = D3DXCOLOR(0.3f, 0.2f, 0.3f, 0.7f);
	pVtx[5].col = D3DXCOLOR(0.3f, 0.2f, 0.3f, 0.7f);
	pVtx[6].col = D3DXCOLOR(0.3f, 0.2f, 0.3f, 0.7f);
	pVtx[7].col = D3DXCOLOR(0.3f, 0.2f, 0.3f, 0.7f);

	//ポーズメニュー背景テクスチャの設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//頂点バッファをアンロックする
	g_pVtxBuffPauseMenu->Unlock();
}

//===============================================================================
//ポーズメニュー終了処理
//===============================================================================
void UninitPauseMenu(void)
{
	//テクスチャの破棄
	if (g_pTexturePauseMenu != NULL)
	{
		g_pTexturePauseMenu->Release();
		g_pTexturePauseMenu = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();
		g_pVtxBuffPauseMenu = NULL;
	}
}

//===============================================================================
//ポーズメニュー更新処理
//===============================================================================
void UpdatePauseMenu(void)
{

}

//===============================================================================
//ポーズメニュー描画処理
//===============================================================================
void DrawPauseMenu(void)
{
	int nCntPauseMenu;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseMenu);

	for (nCntPauseMenu = 0; nCntPauseMenu < 2; nCntPauseMenu++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPauseMenu * 4, 2);
	}
}