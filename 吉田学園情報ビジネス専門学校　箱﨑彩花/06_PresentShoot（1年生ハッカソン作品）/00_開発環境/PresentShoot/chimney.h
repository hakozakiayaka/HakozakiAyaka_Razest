//=============================================================================
//
// 煙突の処理 [chimney.h]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#ifndef _CHIMNEY_H_
#define _CHIMNEY_H_

#include "main.h"

//=============================================================================
// 構造体の定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	float		fWidth;			//幅
	float		fHight;			//高さ
	int			nCounterMove;	//移動量のカウンター
	bool	    bIn;			//入っているかどうか
	bool		bUse;			//使用しているかどうか
}Chimney;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitChimney(void);
void UninitChimney(void);
void UpdateChimney(void);
void DrawChimney(void);

void SetChimney(D3DXVECTOR3 pos, float fWidth, float fHight);
bool CollisionChimney(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fWhidth, float fHeight);
Chimney *GetChimney(void);
#endif