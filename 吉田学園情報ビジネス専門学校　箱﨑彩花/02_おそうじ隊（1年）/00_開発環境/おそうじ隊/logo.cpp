//===============================================================================
//
// ロゴ画面 [logo.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include "fade.h"
#include "input.h"
#include "logo.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define LOGO_TEX	"data/TEXTURE/mio.jpg"	//読み込むテクスチャ

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureLogo = NULL;					//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLogo = NULL;		//頂点バッファへのポインタ
Logo g_Logo;

//===============================================================================
//ロゴ画面初期化処理
//===============================================================================
void InitLogo(void)
{
	//変数宣言
	VERTEX_2D * pVtx;							//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//構造体の初期化
	g_Logo.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	g_Logo.state = LOGOSTATE_NONE;						//ロゴ
	g_Logo.bUse = false;

	//デバイスを取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, LOGO_TEX, &g_pTextureLogo);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLogo,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLogo->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Logo.state == LOGOSTATE_LOGO)
	{
		//背景の座標設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 400.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(500.0f, 400.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//背景色設定
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//背景テクスチャの設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffLogo->Unlock();
}

//===============================================================================
//ロゴ画面終了処理
//===============================================================================
void UninitLogo(void)
{
	//テクスチャの破棄
	if (g_pTextureLogo != NULL)
	{
		g_pTextureLogo->Release();
		g_pTextureLogo = NULL;
	}
	
	//頂点バッファの破棄
	if (g_pVtxBuffLogo != NULL)
	{
		g_pVtxBuffLogo->Release();
		g_pVtxBuffLogo = NULL;
	}
}

//===============================================================================
//ロゴ画面更新処理
//===============================================================================
void UpdateLogo(void)
{
}

//===============================================================================
//ロゴ画面描画処理
//===============================================================================
void DrawLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureLogo);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===============================================================================
//ロゴの設定
//===============================================================================
void SetLogo(D3DXVECTOR3 pos, int nTexType, LogoState state)
{
	g_Logo.pos = pos;
	g_Logo.nTexType = nTexType;
	g_Logo.state = LOGOSTATE_LOGO;
	g_Logo.bUse = true;
}