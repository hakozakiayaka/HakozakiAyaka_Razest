//=============================================================================
//
// ポーズ処理 [Pausemenu.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _PAUSEMENU_H_
#define _PAUSEMENU_

#include "main.h"

//*****************************************************************************
// ポーズの状態の種類
//*****************************************************************************
typedef enum
{
	PAUSESTATE_NONE = 0,
	PAUSESTATE_CONTINUE,
	PAUSESTATE_RETRY,
	PAUSESTATE_QUIT,
	PAUSESTATE_MAX,
}PAUSESTATE;

typedef enum
{
	PAUSESTATECOLOR_NONE = 0,
	PAUSESTATECOLOR_CONTINUE,
	PAUSESTATECOLOR_RETRY,
	PAUSESTATECOLOR_QUIT,
	PAUSESTATECOLOR_MAX,
}COLORSTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPausemenu(void);
void UninitPausemenu(void);
void UpdatePausemenu(void);
void DrawPausemenu(void);

#endif