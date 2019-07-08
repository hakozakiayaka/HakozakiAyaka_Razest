//=============================================================================
//
// リザルト[ クリア ]画面 [result.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "result.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "start.h"
#include "BG.h"
#include "flontpolygon.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
int g_nCntTimeResult;								//ゲーム画面切り替えカウンター
int g_nCntPaperTime;										//時間カウンター

//=============================================================================
// リザルト初期化処理
//=============================================================================
void InitResult(void)
{
	g_nCntTimeResult = 0;	//カウンターの初期化

	//変数の呼び出し
	InitStart();		//エンターキー

	//背景のセット
	SetBG(2);

	//タイトルロゴのセット
	SetFlontPolygon(2, D3DXVECTOR3(640.0f, 320.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500.0f, 200.0f);

	//エンターキー
	SetEnter(D3DXVECTOR3(1090.0f, 685.0f, 0.0f), D3DXCOLOR(0.05f, 0.5f, 0.05f, 1.0f));	
}

//=============================================================================
// リザルト終了処理
//=============================================================================
void UninitResult(void)
{
	UninitStart();		//エンターキー
}

//=============================================================================
// リザルト更新処理
//=============================================================================
void UpdateResult(void)
{
	g_nCntTimeResult++;
	g_nCntPaperTime++;

	//フェード情報を取得する
	FADE g_fade;
	g_fade = GetFade();
	
	//決定キーが押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_fade != FADE_OUT)		//フェードアウトが実行されていないなら
		{

			//サウンド再生
			PlaySound(SOUND_LABEL_SE_ENTER);

			//エンターキーの状態変更
			SetPush(STARTSTRACT_ENTER);

			//フェードモード設定
			SetFade(MODE_RANK);
		}
		
	}
	if (g_nCntTimeResult == INTERVAL_TIME)
	{
		//フェードモード設定
		SetFade(MODE_RANK);
	}

	UpdateStart();		//エンターキー
}

//=============================================================================
// リザルト描画処理
//=============================================================================
void DrawResult(void)
{
	DrawStart();		//エンターキー
}