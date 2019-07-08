//===============================================================================
//
// タイトル画面 [title.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include "fade.h"
#include "input.h"
#include "title.h"
#include "logo.h"
#include "BG.h"
#include "sound.h"

//==============================================================================
//マクロ定義
//===============================================================================
#define TITLE_TEX1	"data/TEXTURE/title_logo.png"	//読み込むテクスチャ
#define TITLE_TEX2	"data/TEXTURE/enter_logo.png"	//読み込むテクスチャ

#define TIMERIMIT							(60 * 3)											//制限時間
#define MAX_TEX							(2)													//テクスチャの最大数

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ
int g_nCntTimeTitle = 0;															//タイトル画面からランキング画面への切り替わりのカウンター
Title g_Title;																			//構造体の変数

//===============================================================================
//タイトル画面初期化処理
//===============================================================================
void InitTitle(void)
{
	//変数宣言
	VERTEX_2D * pVtx;							//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	InitBG();
	SetBG(3);

	//構造体の初期化
	g_Title.state = TITLESTATE_NORMAL;
	g_Title.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Title.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Title.fFlash = 0.05f;
	g_Title.nCnt = 0;
	g_Title.bUse = false;

	//デバイスを取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TITLE_TEX1, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEX2, &g_pTextureTitle[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//タイトルロゴ座標設定------------------------------------------------------------------------------------------------------------------
	pVtx[0].pos = D3DXVECTOR3(160.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1130.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(160.0f, 450.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1130.0f, 450.0f, 0.0f);

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

	//タイトルロゴテクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//エンター座標設定------------------------------------------------------------------------------------------------------------------
	pVtx[4].pos = D3DXVECTOR3(300.0f, 500.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(980.0f, 500.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(300.0f, 650.0f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(980.0f, 650.0f, 0.0f);

	//rhwの設定
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//背景色設定
	pVtx[4].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[5].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[6].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[7].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//タイトルロゴテクスチャの設定
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
	UninitBG();

	//テクスチャの破棄
	for (int nCntTitle = 0; nCntTitle < MAX_TEX; nCntTitle++)
	{
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
	//フェードを取得
	FADE g_fade = GetFade();
	VERTEX_2D * pVtx;							//頂点情報へのポインタ

	UpdateBG();

	//画面切り替えカウンター
	g_nCntTimeTitle++;

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
	else if (g_nCntTimeTitle % 300 == 0)
	{
		if (g_fade != FADE_OUT)
		{	//フェードアウト中にEnterキーを押せなくする
			//モード設定
			SetFade(MODE_RANKING);
		}
	}

	//プッシュエンターの点滅
	if (g_Title.nCnt >= 50)
	{
		g_Title.fFlash *= -1;
		g_Title.nCnt = 0;
	}

	g_Title.nCnt++;
	g_Title.col.a += g_Title.fFlash;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//背景色設定
	pVtx[4].col = D3DXCOLOR(1.0, 1.0, 1.0, g_Title.col.a);
	pVtx[5].col = D3DXCOLOR(1.0, 1.0, 1.0, g_Title.col.a);
	pVtx[6].col = D3DXCOLOR(1.0, 1.0, 1.0, g_Title.col.a);
	pVtx[7].col = D3DXCOLOR(1.0, 1.0, 1.0, g_Title.col.a);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//===============================================================================
//タイトル画面描画処理
//===============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	DrawBG();

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TEX; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTitle, 2);
	}
}