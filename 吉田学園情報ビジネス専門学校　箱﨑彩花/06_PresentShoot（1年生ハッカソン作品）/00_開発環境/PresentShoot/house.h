//=============================================================================
//
// ハウス処理 [house.h]
// Author : 箱崎綾香
//
//=============================================================================
#ifndef _HOUSE_H_
#define _HOUSE_H_

#include "main.h"

//=============================================================================
// 構造体の定義
//=============================================================================
typedef struct 
{
	D3DXVECTOR3		pos;		//中心座標
	D3DXCOLOR		col;		//色
	float			fWidth;		//幅
	float			fHight;		//高さ
	int				nTexNum;	//テクスチャの番号
	int				Num;		//番号
	int fHalfWidth;				//横の半分
	int fHalfHeght;				//縦の半分
	bool			bUse;		//使用しているかどうか
} House;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitHouse(void);
void UninitHouse(void);
void UpdateHouse(void);
void DrawHouse(void);

void SetHouse(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHight);
void DeleteHouse();
#endif