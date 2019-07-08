//=============================================================================
//
// ビルボード処理 [	billboard.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//*****************************************************************************
// ビルボードの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 rot;								//向き
	D3DXMATRIX mtxWorldBillboard;		//ワールドマトリックス
	int nIdxBillboardShadow;					//影が使われているかどうか
	int nTexType;										//テクスチャのタイプ
	bool bUse;											//ビルボードが使われているかどうか
} Billboard;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int TexType);
void DeleteBillboard(int nCntBillboard);

#endif