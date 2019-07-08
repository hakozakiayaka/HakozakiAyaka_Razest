//=============================================================================
//
// メッシュシリンダー処理 [meshCylinder.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;									//位置
	D3DXVECTOR3 move;									//移動量
	D3DXVECTOR3 rot;										//向き
	D3DXMATRIX mtxWorldMeshCylinder;			//ワールドマトリックス
} MESHCYLINDER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);

#endif
