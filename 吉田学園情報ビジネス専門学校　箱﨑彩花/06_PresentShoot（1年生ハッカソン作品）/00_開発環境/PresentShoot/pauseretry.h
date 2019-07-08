//=============================================================================
//
// ポーズリトライ処理 [pauseretry.h]
// Author : 佐藤安純　Sato_Aumi
//
//=============================================================================
#ifndef _PAUSERETRY_H_
#define _PAUSERETRY_H_

#include "main.h"

//=============================================================================
// リトライの状態の種類
//=============================================================================
typedef enum
{
	RETRYSTATE_NORMAL = 0,
	RETRYSTATE_SELECT,
	RETRYSTATE_MAX,
}RETRYSTATE;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitPauseRetry(void);
void UninitPauseRetry(void);
void UpdatePauseRetry(void);
void DrawPauseRetry(void);

void SetPauseRetry(RETRYSTATE state);
#endif
