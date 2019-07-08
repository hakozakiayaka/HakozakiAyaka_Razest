//=============================================================================
//
// ポーズ画面 [pause.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "pause.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "game.h"
#include "fade.h"
#include "pausefade.h"
#include "pausestand.h"
#include "pausecontinue.h"
#include "pauseretry.h"
#include "pausequit.h"
#include "BG.h"

//=============================================================================
// グローバル変数
//=============================================================================
PAUSESTATE g_PauseMode;		//ポーズの状態
int g_SelectMode;
int g_PauseMax;				//ポーズ状態の最大数
bool g_bPauseDecide;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPause(void)
{
	//変数の初期化
	g_PauseMode = PAUSESTATE_NONE;
	g_SelectMode = PAUSESTATE_CONTINUE;
	g_PauseMax = PAUSESTATE_MAX;
	g_bPauseDecide = true;

	InitPauseFade();		//画面を黒くする
	InitPauseStand();		//台紙
	InitPauseContinue();	//コンティニュー
	InitPauseRetry();		//リトライ
	InitPauseQuit();		//クワイエット
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPause(void)
{
	UninitPauseFade();		//画面を黒くする
	UninitPauseStand();		//台紙
	UninitPauseContinue();	//コンティニュー
	UninitPauseRetry();		//リトライ
	UninitPauseQuit();		//クワイエット
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePause(void)
{
	UpdatePauseFade();		//画面を黒くする
	UpdatePauseStand();		//台紙
	UpdatePauseContinue();	//コンティニュー
	UpdatePauseRetry();		//リトライ
	UpdatePauseQuit();		//クワイエット

	if (GetKeyboardTrigger(DIK_W) == true)
	{
		PlaySound(SOUND_LABEL_SE_KARSOL);
		g_SelectMode = (g_SelectMode + (3 - 1)) % 3;
	}
	if (GetKeyboardTrigger(DIK_S) == true)
	{
		PlaySound(SOUND_LABEL_SE_KARSOL);
		g_SelectMode = (g_SelectMode + 1) % 3;
	}

	if (g_SelectMode == 0)
	{
		SetPauseContinue(CONTINUESTATE_SELECT);
		SetPauseRetry(RETRYSTATE_NORMAL);
		SetPauseQuit(QUITSTATE_NORMAL);

		//決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_ENTER);
			g_PauseMode = PAUSESTATE_CONTINUE;
		}
	}
	else if (g_SelectMode == 1)
	{
		SetPauseContinue(CONTINUESTATE_NORMAL);
		SetPauseRetry(RETRYSTATE_SELECT);
		SetPauseQuit(QUITSTATE_NORMAL);

		//決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_ENTER);
			g_PauseMode = PAUSESTATE_RETRY;
		}
	}
	else if(g_SelectMode == 2)
	{
		SetPauseContinue(CONTINUESTATE_NORMAL);
		SetPauseRetry(RETRYSTATE_NORMAL);
		SetPauseQuit(QUITSTATE_SELECT);

		//決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_ENTER);
			g_PauseMode = PAUSESTATE_QUIT;
		}
	}

	//フェード情報を取得する
	FADE fade;
	fade = GetFade();

	switch (g_PauseMode)
	{
	case PAUSESTATE_CONTINUE:
		g_PauseMode = PAUSESTATE_NONE;
		SetPause(false);
		break;

	case PAUSESTATE_RETRY:
		g_PauseMode = PAUSESTATE_NONE;

		if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
		{
			//フェードモード設定
			SetFade(MODE_GAME);
		}
		break;

	case PAUSESTATE_QUIT:
		g_PauseMode = PAUSESTATE_NONE;

		if (fade != FADE_OUT)		//フェードアウトが実行されていないなら
		{
			//フェードモード設定
			SetFade(MODE_TITLE);
		}
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPause(void)
{
	DrawPauseFade();		//画面を黒くする
	DrawPauseStand();		//台紙
	DrawPauseContinue();	//コンティニュー
	DrawPauseRetry();		//リトライ
	DrawPauseQuit();		//クワイエット
}