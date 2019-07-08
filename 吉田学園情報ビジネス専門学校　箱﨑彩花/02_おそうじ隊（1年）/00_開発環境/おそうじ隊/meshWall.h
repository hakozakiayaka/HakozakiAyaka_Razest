//=============================================================================
//
// メッシュウォール処理 [meshWall.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 move;									//移動量
	D3DXVECTOR3 rot;										//向き
	int nWidth;													//幅
	int nHeight;													//高さ
	int nTexType;												//テクスチャのタイプ
	D3DXMATRIX mtxWorldMeshWall;			//ワールドマトリックス
	int nNumVertexMeshWall;																	//頂点数
	int nNumIndexMeshWall;																	//インデックス数
	int nNumPolygonMeshWall;																//ポリゴン数
	bool bUse;
} MESHWALL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight, int nTexType);

#endif
