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
#include "title.h"

//===============================================================================
//マクロ定義
//===============================================================================
#define TITLE_BG					"data/TEXTURE/title2.jpg"				//読み込むテクスチャ
#define TITLE_LOGO		"data/TEXTURE/title_logo1.png"	//読み込むテクスチャ
#define PUSH_ENTER	"data/TEXTURE/pushenter.png"	//読み込むテクスチャ
#define TITLE_GIRL		"data/TEXTURE/girl1.png"				//読み込むテクスチャ
#define MAX_TEXTURE					(5)									//テクスチャの枚数

#define TITLE_POS_X						(0)													//背景の左上X座標
#define TITLE_POS_Y						(0)													//背景の左上Y座標
#define TITLE_WIDTH					(SCREEN_WIDTH)							//背景の幅
#define TITLE_HEIGHT					(SCREEN_HEIGHT)							//背景の高さ

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEXTURE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;					//頂点バッファへのポインタ
TITLE g_nTitle;

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

	//構造体の初期化
	g_nTitle.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_nTitle.Flash = 0.05f;
	g_nTitle.nCnt = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TITLE_BG, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_LOGO, &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, PUSH_ENTER, &g_pTextureTitle[2]);
	D3DXCreateTextureFromFile(pDevice, TITLE_GIRL, &g_pTextureTitle[3]);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//=============================================================================
	//ロゴ背景の座標設定
	pVtx[0].pos = D3DXVECTOR3(120, 130, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(680, 130, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(120, 400, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(680, 400, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//ロゴ背景色設定
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//ロゴ背景テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//=============================================================================
	//プッシュエンターの座標設定
	pVtx[0].pos = D3DXVECTOR3(150, 500, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(680, 500, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(150, 550, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(680, 550, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//プッシュエンターの色設定
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//プッシュエンターのテクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//=============================================================================
	//キャラの座標設定
	pVtx[0].pos = D3DXVECTOR3(900, 350, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1240, 350, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(900, 700, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1240, 700, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//キャラの色設定
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//キャラのテクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//===============================================================================
//タイトル画面終了処理
//===============================================================================
void UninitTitle(void)
{
	int nCnt;

	//テクスチャの破棄
	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
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
	VERTEX_2D * pVtx;							//頂点情報へのポインタ

	//フェードを取得
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

	//プッシュエンターの点滅
	if (g_nTitle.nCnt >= 50)
	{
		g_nTitle.Flash *= -1;
		g_nTitle.nCnt = 0;
	}

	g_nTitle.nCnt++;
	g_nTitle.col.a += g_nTitle.Flash;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//プッシュエンターの色設定
	pVtx[8].col = D3DXCOLOR(1.0, 1.0, 1.0, g_nTitle.col.a);
	pVtx[9].col = D3DXCOLOR(1.0, 1.0, 1.0, g_nTitle.col.a);
	pVtx[10].col = D3DXCOLOR(1.0, 1.0, 1.0, g_nTitle.col.a);
	pVtx[11].col = D3DXCOLOR(1.0, 1.0, 1.0, g_nTitle.col.a);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

}

//===============================================================================
//タイトル画面描画処理
//============================================================ n===================
void DrawTitle(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスを取得する
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}