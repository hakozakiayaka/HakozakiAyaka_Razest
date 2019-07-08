//===============================================================================
//
// タイトル画面 [title.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include"tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define TITLE_TEXTURE_NAME	"data/TEXTURE/title003.png"	//読み込むテクスチャ
#define TITLE_TEXTURE_NAME1	"data/TEXTURE/title_logo000.png"	//読み込むテクスチャ

#define TITLE_POS_X						(0)													//背景の左上X座標
#define TITLE_POS_Y						(0)													//背景の左上Y座標
#define TITLE_WIDTH					(SCREEN_WIDTH)							//背景の幅
#define TITLE_HEIGHT					(SCREEN_HEIGHT)							//背景の高さ
#define MAX_TEXTURE					(2)
//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEXTURE] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ
int g_nCntAnim;
int g_nCntPatternAnim;

//===============================================================================
//タイトル画面初期化処理
//===============================================================================
void InitTitle(void)
{
	//変数宣言
	VERTEX_2D * pVtx;							//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスを取得
	pDevice = GetDevice();

	//初期化
	g_nCntAnim = 0;
	g_nCntPatternAnim = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME1, &g_pTextureTitle[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

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

	//=============================================================================
	//ロゴ背景の座標設定
	pVtx[4].pos = D3DXVECTOR3(290, 310, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(990, 310, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(290, 410, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(990, 410, 0.0f);
	//rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//ロゴ背景色設定
	pVtx[4].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[5].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[6].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[7].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//ロゴ背景テクスチャの設定
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//===============================================================================
//タイトル画面終了処理
//===============================================================================
void UninitTitle(void)
{
	int nCntTitle;

	for (nCntTitle = 0; nCntTitle < MAX_TEXTURE; nCntTitle++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
	
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//===============================================================================
//タイトル画面更新処理
//===============================================================================
void UpdateTitle(void)
{
	FADE g_fade;

	g_fade = GetFade();

	//決定キーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);
		if (g_fade != FADE_OUT)
		{	//フェードアウト中にEnterキーを押せなくする
			//モード設定
			SetFade(MODE_TUTORIAL);
		}
	}
}

//===============================================================================
//タイトル画面描画処理
//===============================================================================
void DrawTitle(void)
{
	int nCntTitle;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTitle = 0; nCntTitle < MAX_TEXTURE; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTitle, 2);
	}
}