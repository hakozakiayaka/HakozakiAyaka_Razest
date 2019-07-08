//=============================================================================
//
// ポリゴン処理 [flontpolygon.h]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#ifndef _FLONTPOLYGON_H_
#define _FLONTPOLYGON_H_

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
}FlontPolygon;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitFlontPolygon(void);
void UninitFlontPolygon(void);
void UpdateFlontPolygon(void);
void DrawFlontPolygon(void);

void SetFlontPolygon(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHight);
void DeleteFlontPolygon();
#endif