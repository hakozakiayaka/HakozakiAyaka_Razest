//=============================================================================
//
// ポーズコンティニュー処理 [pousecontinue.h]
// Author : 佐藤安純　Sato_Aumi
//
//=============================================================================
#ifndef _PAUSECONTINUE_H_
#define _PAUSECONTINUE_H_

#include "main.h"

//=============================================================================
// コンティニューの状態の種類
//=============================================================================
typedef enum
{
	CONTINUESTATE_NORMAL = 0,
	CONTINUESTATE_SELECT,
	CONTINUESTATE_MAX,
}CONTINUESTATE;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitPauseContinue(void);
void UninitPauseContinue(void);
void UpdatePauseContinue(void);
void DrawPauseContinue(void);

void SetPauseContinue(CONTINUESTATE state);
#endif

