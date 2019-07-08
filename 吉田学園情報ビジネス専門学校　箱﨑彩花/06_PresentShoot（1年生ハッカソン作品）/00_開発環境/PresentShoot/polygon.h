//=============================================================================
//
// 背景処理 [polygon.h]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

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
	bool			bUse;		//使用しているかどうか
}Polygon;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);

void SetPolygon(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHight);
void DeletePolygon();
#endif