//=============================================================================
//
// プレゼントの処理 [present.h]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#ifndef _PRESENT_H_
#define _PRESENT_H_

#include "main.h"

//=============================================================================
// 種類の設定
//=============================================================================
typedef enum
{
	PRESENTTYPE_BAG = 0,
	PRESENTTYPE_L,
	PRESENTTYPE_M,
	PRESENTTYPE_S,
	PRESENTTYPE_MAX
}PRESENTTYPE;

//=============================================================================
// 構造体の定義
//=============================================================================
typedef struct 
{
	D3DXVECTOR3		pos;		//中心座標
	D3DXVECTOR3		OldPos;		//前回の位置
	D3DXVECTOR3		move;		//移動量
	float			fGravity;	//重力
	int				nTexNum;	//テクスチャの番号
	PRESENTTYPE		Type;		//タイプの設定
	bool			bUse;		//使用しているかどうか
}Present;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitPresent(void);
void UninitPresent(void);
void UpdatePresent(void);
void DrawPresent(void);

void SetPresent(int nTexNum, D3DXVECTOR3 pos);
void DeletePresent(int nCntPresent, PRESENTTYPE type);
#endif