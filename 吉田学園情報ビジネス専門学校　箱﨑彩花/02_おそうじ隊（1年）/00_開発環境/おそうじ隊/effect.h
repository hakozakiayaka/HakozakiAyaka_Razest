//=============================================================================
//
// エフェクト処理 [	effect.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// エフェクトの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXCOLOR col;									// 色
	D3DXMATRIX mtxWorldEffect;			//ワールドマトリックス
	float fRadius;										// 半径(大きさ)
	int nLife;												// 表示時間(寿命)
	bool bUse;											//ビルボードが使われているかどうか
} Effect;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife);
void DeleteEffect(int nCntEffect);

#endif