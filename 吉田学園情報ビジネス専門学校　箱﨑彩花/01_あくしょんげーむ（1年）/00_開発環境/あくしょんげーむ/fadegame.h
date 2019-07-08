//=============================================================================
//
// フェード処理 [fadegame.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _FADEGAME_H_
#define _FADEGAME_H_

#include "main.h"
#include "game.h"

//*************************************
// フェードの状態
//*************************************
typedef enum
{
	FADEGAME_NONE = 0,		// 何もしていない状態
	FADEGAME_IN,						// フェードイン状態
	FADEGAME_OUT,					// フェードアウト状態
	FADEGAME_MAX
} FADEGAME;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitFadeGame(void);
void UninitFadeGame(void);
void UpdateFadeGame(void);
void DrawFadeGame(void);

void SetFadeGame(GAMESTAGE modeNext);
FADEGAME GetFadeGame(void);

#endif
