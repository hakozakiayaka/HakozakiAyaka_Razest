//=============================================================================
//
// スコア処理 [score.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//
//
//
typedef struct
{
	int nScore;
	int aScoreData;
} Score;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nValue);
int GetScore(void);
#endif
