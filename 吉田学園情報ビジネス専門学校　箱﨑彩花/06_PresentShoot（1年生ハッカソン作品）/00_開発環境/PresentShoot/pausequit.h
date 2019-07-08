//=============================================================================
//
// ポーズクワイエット処理 [pausequit.h]
// Author : 佐藤安純　Sato_Aumi
//
//=============================================================================
#ifndef _PAUSEQUIT_H_
#define _PAUSEQUIT_H_

#include "main.h"

//=============================================================================
// クワイエットの状態の種類
//=============================================================================
typedef enum
{
	QUITSTATE_NORMAL = 0,
	QUITSTATE_SELECT,
	QUITSTATE_MAX,
}QUITSTATE;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitPauseQuit(void);
void UninitPauseQuit(void);
void UpdatePauseQuit(void);
void DrawPauseQuit(void);

void SetPauseQuit(QUITSTATE state);
#endif
