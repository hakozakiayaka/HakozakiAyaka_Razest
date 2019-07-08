//=============================================================================
//
// 影の処理 [shadow.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// 影の構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	bool bUse;							//影が使われているかどうか
	int nIdxShadow;					//影のインデックス
	float fWidth;							//影の幅
	float fHeight;						//影の高さ
	float fLength;						//対角線の長さ
	D3DXVECTOR3 OtherPos;	//4頂点の座標
} Shadow;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);	//影の番号、位置
void DeleteShadow(int nIdxShadow);
#endif
