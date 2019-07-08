#pragma once
//===============================================================================
//
// ゲーム画面 [game .h]
// Author : 箱﨑彩花
//
//===============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//===============================================================================
//ゲームの状態
//===============================================================================
typedef enum
{
	GAMESTATE_NONE = 0,		//何もしていない状態
	GAMESTATE_NORMAL,			//通常状態
	GAMESTATE_CLEAR,				//クリア状態
	GAMESTATE_OVER,				//ゲームオーバー状態
	GAMESTATE_MAX
} GAMESTATE;

typedef enum
{
	GAMESTAGE_SELECT = 0,
	GAMESTAGE1,
	GAMESTAGE2,
	GAMESTAGE_MAX
} GAMESTAGE;

//===============================================================================
//プロトタイプ宣言
//===============================================================================
void InitGame(void);									//ゲーム画面初期化処理
void UninitGame(void);								//ゲーム画面終了処理
void UpdateGame(void);								//ゲーム画面更新処理
void DrawGame(void);								//ゲーム画面描画処理

void SetGameState(GAMESTATE state);	//ゲームの状態設定
GAMESTATE GetGameState(void);			//ゲームの状態を取得
void SetGameStage(GAMESTAGE stage);	//ステージの設定
GAMESTAGE GetGameStage(void);			//ステージの取得

void SetPause(bool bPause);						//ポーズの設定
#endif