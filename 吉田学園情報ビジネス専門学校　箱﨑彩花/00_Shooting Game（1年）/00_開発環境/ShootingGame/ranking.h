//=============================================================================
//
// ランキング処理 [ranking.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _RANKSCORE_H_
#define _RANKSCORE_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitRankScore(void);
void UninitRankScore(void);
void UpdateRankScore(void);
void DrawRankScore(void);
void SetRankScore(int nScore);

#endif
