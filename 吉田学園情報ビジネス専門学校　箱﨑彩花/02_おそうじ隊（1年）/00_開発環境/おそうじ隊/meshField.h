//=============================================================================
//
// メッシュフィールド処理 [meshField.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 move;									//移動量
	D3DXVECTOR3 rot;										//向き
	D3DXMATRIX mtxWorldMeshField;			//ワールドマトリックス
	int nWidth;													//幅
	int nHeight;													//高さ
	int nNumVertexMeshField;							//頂点数
	int nNumIndexMeshField;							//インデックス数
	int nNumPolygonMeshField;						//ポリゴン数
	bool bUse;													//使用しているかどうか
} MESHFIELD;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
MESHFIELD * GetMeshField(void);
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight);
#endif
