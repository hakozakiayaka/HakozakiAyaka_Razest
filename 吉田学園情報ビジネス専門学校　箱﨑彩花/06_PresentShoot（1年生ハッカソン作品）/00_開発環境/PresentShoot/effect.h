//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : 佐藤安純	SatoAsumi
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//=============================================================================
// エフェクトの種類
//=============================================================================
typedef enum
{
	EFFECTTYPE_SANTA = 0, 
	EFFECTTYPE_TITLE,
	EFFECTTYPE_MAX
}EFFECTTYPE;

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR col;			// 色
	float fRadius;			// 半径(大きさ)
	float fChngeRadius;		// 半径の変化量
	float fRadiusCnt;		// 変化量カウンター
	float fGravity;			// 重力
	float fAngle;			// 角度
	int nLife;				// 表示時間(寿命)
	int nTexType;			// テクスチャのタイプ設定
	bool bAngle;			// 角度
	bool bUse;				// 使用しているかどうか
	EFFECTTYPE type;
} EFFECT;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int TexType);
#endif