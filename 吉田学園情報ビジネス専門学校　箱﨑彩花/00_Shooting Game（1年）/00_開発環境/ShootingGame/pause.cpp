//===============================================================================
//
// ポーズ処理 [pause.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include"pausemenu.h"
#include "continu.h"
#include "retry.h"
#include "quit.h"
#include "pause.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"

//===============================================================================
//グローバル変数宣言
//===============================================================================
PAUSEATATE g_Pause;		//ポーズの状態
int g_nSelect;						//選択項目

//===============================================================================
//ポーズ初期化処理
//===============================================================================
void InitPause(void)
{
	//初期化
	g_nSelect = 0;

	InitPauseMenu();
	InitContinu();
	InitRetry();
	InitQuit();
}

//===============================================================================
//ポーズ終了処理
//===============================================================================
void UninitPause(void)
{
	UninitPauseMenu();
	UninitContinu();
	UninitRetry();
	UninitQuit();
}

//===============================================================================
//ポーズ更新処理
//===============================================================================
void UpdatePause(void)
{
	if (GetKeyboardTrigger(DIK_S) == true)
	{	//下（S）キーが押された
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelect = (g_nSelect + 1) % 3;
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{	//上（W）が押された
		PlaySound(SOUND_LABEL_SE_SELECT);
		g_nSelect = (g_nSelect + 2) % 3;
	}

	if (g_nSelect == 0)
	{
		SetContinue(CONTUNUESTATE_SELECT);
		SetRetry(RETRYSTATE_NONE);
		SetQuit(QUITSTATE_NONE);

		//決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_Pause = PAUSESTATE_CONTINU;
		}
	}
	if (g_nSelect == 1)
	{
		SetContinue(CONTINUESTATE_NONE);
		SetRetry(RETRYSTATE_SELECT);
		SetQuit(QUITSTATE_NONE);

		//決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_Pause = PAUSESTATE_RETRY;
		}
	}
	if (g_nSelect == 2)
	{
		SetContinue(CONTINUESTATE_NONE);
		SetRetry(RETRYSTATE_NONE);
		SetQuit(QUITSTATE_SELECT);

		//決定キーが押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_Pause = PAUSESTATE_QUIT;
		}
	}

	switch (g_Pause)
	{
	case PAUSESTATE_CONTINU:
		g_Pause = PAUSESTATE_NONE;
		SetPause(false);
		break;

	case PAUSESTATE_RETRY:
		g_Pause = PAUSESTATE_NONE;
		SetFade(MODE_GAME);
		break;

	case PAUSESTATE_QUIT:
		g_Pause = PAUSESTATE_NONE;
		SetFade(MODE_TITLE);
		break;
	}

	UpdatePauseMenu();
	UpdateContinu();
	UpdateRetry();
	UpdateQuit();
}

//===============================================================================
//ポーズ描画処理
//===============================================================================
void DrawPause(void)
{
	DrawPauseMenu();
	DrawContinu();
	DrawRetry();
	DrawQuit();
}