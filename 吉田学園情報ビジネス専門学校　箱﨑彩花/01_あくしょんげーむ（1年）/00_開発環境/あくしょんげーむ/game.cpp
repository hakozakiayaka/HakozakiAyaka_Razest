//===============================================================================
//
// ゲーム画面 [game.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include"bg.h"
#include "player.h"
#include "block.h"
#include "item.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include "time.h"
#include "fade.h"
#include "pause.h"
#include "explosion.h"
#include "fadegame.h"
#include "sound.h"

//===============================================================================
//グローバル変数宣言
//===============================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲームの状態
GAMESTAGE g_gameStage;										//ゲームのステージ
int g_nCounterGameState;											//状態管理のカウンター
bool g_bPause;															//ポーズ中かどうか

//===============================================================================
//ゲーム画面初期化処理
//===============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;				//通常状態に設定
	g_gameStage = GAMESTAGE_SELECT;					//ステージ選択に設定
	g_nCounterGameState = 0;
	g_bPause = false;

	//背景の初期化処理
	InitBG();
	//プレイヤーの初期化処理
	InitPlayer();
	//スコアの初期化処理
	InitScore();
	//タイムの初期化処理
	InitTime();
	//ポーズの初期化処理
	InitPause();
	//アイテムの初期化処理
	InitItem();
	//ブロックの初期化処理
	InitBlock();
	//爆発の初期化処理
	InitExplosion();
	//ゲームフェードの初期化処理
	InitFadeGame();
}

//===============================================================================
//ゲーム画面終了処理
//===============================================================================
void UninitGame(void)
{
	//背景の終了処理
	UninitBG();
	//プレイヤーの終了処理
	UninitPlayer();
	//スコアの終了処理
	UninitScore();
	//タイムの終了処理
	UninitTime();
	//アイテムの終了処理
	UninitItem();
	//ブロックの終了処理
	UninitBlock();
	//ポーズの終了処理
	UninitPause();
	//爆発の終了処理
	UninitExplosion();
	//ゲームフェードの終了処理
	UninitFadeGame();
}

//===============================================================================
//ゲーム画面更新処理
//===============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{	//	ポーズの処理
		PlaySound(SOUND_LABEL_SE_PAUSE);
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			break;

		case GAMESTATE_CLEAR:
			g_nCounterGameState++;
			if (g_nCounterGameState <= 60)
			{
				//画面(モード)の設定
				SetFade(MODE_RESULT);
			}
			break;

		case GAMESTATE_OVER:
			g_nCounterGameState++;
			if (g_nCounterGameState <= 60)
			{
				//画面(モード)の設定
				SetFade(MODE_RESULT);
			}
			break;
		}

		//背景の更新処理
		UpdateBG();
		//プレイヤーの更新処理
		UpdatePlayer();
		//スコアの更新処理
		UpdateScore();
		//タイムの更新処理
		UpdateTime();
		//アイテムの更新処理
		UpdateItem();
		//ブロックの更新処理
		UpdateBlock();
		//爆発の更新処理
		UpdateExplosion();
		//ゲームフェード更新処理
		UpdateFadeGame();
		}
	else
	{
		//ポーズの更新処理
		UpdatePause();
	}
}

//===============================================================================
//ゲーム画面描画処理
//===============================================================================
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();
	//プレイヤーの描画処理
	DrawPlayer();
	//スコアの描画処理
	DrawScore();
	//タイムの描画処理
	DrawTime();
	//アイテムの描画処理
	DrawItem();
	//ブロックの描画処理
	DrawBlock();
	//爆発の描画処理
	DrawExplosion();
	//ゲームフェードの描画処理
	DrawFadeGame();

	if (g_bPause == true)
	{
		//ポーズの描画処理
		DrawPause();
	}
}

//===============================================================================
//ゲームの状態設定
//===============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//===============================================================================
//ゲーム状態の取得
//===============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//===============================================================================
//ステージの設定
//===============================================================================
void SetGameStage(GAMESTAGE stage)
{
	//背景の終了処理
	UninitBG();
	//ブロック終了処理
	UninitBlock();
	//アイテムの終了処理
	UninitItem();

	StopSound(SOUND_LABEL_BGM002);
	StopSound(SOUND_LABEL_BGM003);

	g_gameStage = stage;

	//背景の初期化処理
	InitBG();
	//ブロックの初期化処理
	InitBlock();
	//アイテムの初期化処理
	InitItem();

	if (stage == GAMESTAGE_SELECT)
	{	//選択画面
		PlaySound(SOUND_LABEL_BGM002);
	}
	else if (stage == GAMESTAGE1 || stage == GAMESTAGE2)
	{	//ステージ1とステージ2
		PlaySound(SOUND_LABEL_BGM003);
	}
}

//===============================================================================
//ステージの取得
//===============================================================================
GAMESTAGE GetGameStage(void)
{
	return g_gameStage;
}

//===============================================================================
//ポーズ状態の取得
//===============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}