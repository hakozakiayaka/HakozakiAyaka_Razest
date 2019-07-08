//=============================================================================
//
// タイトル画面 [title.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "start.h"
#include "fade.h"
#include "BG.h"
#include "flontpolygon.h"
#include "StarBG.h"
#include "titleplayer.h"
#include "effect.h"
#include "StarBG.h"

//=============================================================================
// マクロ定義
//=============================================================================


//=============================================================================
// グローバル変数
//=============================================================================
int g_nCntTime;												//エフェクトのカウンター
int g_nCntTimeTitle;										//タイトル時間のカウンター

//=============================================================================
// タイトル初期化処理
//=============================================================================
void InitTitle(void)
{
	//変数宣言
	g_nCntTime = 0;
	g_nCntTimeTitle = 0;

	//関数呼び出し
	InitStarBG();		//星空
	InitStart();		//スタートボタン
	InitEffect();		//エフェクト
	InitTitlePlayer();	//タイトルプレイヤー

	//背景のセット
	SetBG(6);			

	//タイトルロゴのセット
	SetFlontPolygon(0, D3DXVECTOR3(640.0f, 200.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 800.0f, 300.0f);

	//ボタンのセット
	SetEnter(D3DXVECTOR3(630.0f, 650.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

//=============================================================================
// タイトル終了処理
//=============================================================================
void UninitTitle(void)
{
	//関数呼び出し
	UninitStarBG();			//星空
	UninitStart();			//スタートボタン
	UninitEffect();			//エフェクト
	UninitTitlePlayer();	//タイトルプレイヤー
}

//=============================================================================
// タイトル更新処理
//=============================================================================
void UpdateTitle(void)
{
	//時間を加算する
	g_nCntTime++;
	g_nCntTimeTitle++;

	//フェード情報を取得する
	FADE fade;
	fade = GetFade();

	//関数呼び出し
	UpdateStarBG();			//星空
	UpdateStart();			//スタートボタン
	UpdateEffect();			//エフェクト
	UpdateTitlePlayer();	//タイトルプレイヤー
	
	//決定キーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
		{
			//スタートボタンの設定
			SetPush(STARTSTRACT_ENTER);

			//フェードモード設定
			SetFade(MODE_TUTORIAL);
			PlaySound(SOUND_LABEL_SE_ENTER);	//決定音
		}
	}
	if (g_nCntTimeTitle == INTERVAL_TIME)
	{
		//フェードモード設定
		SetFade(MODE_TUTORIAL);
	}
}

//=============================================================================
// タイトル描画処理
//=============================================================================
void DrawTitle(void)
{
	//関数呼び出し
	DrawStarBG();		//星空
	DrawStart();		//スタートボタン
	DrawEffect();		//エフェクト
	DrawTitlePlayer();	//タイトルプレイヤー
}