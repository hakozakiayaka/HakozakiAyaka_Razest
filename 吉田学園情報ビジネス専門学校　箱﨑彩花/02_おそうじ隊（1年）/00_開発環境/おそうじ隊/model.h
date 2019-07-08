//=============================================================================
//
// モデル処理 [model.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMeshModel = NULL;			//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatModel = NULL;	//マテリアルの情報へのポインタ
	DWORD nNumMatModel = NULL;					//マテリアルの情報数
	D3DXVECTOR3 pos;										//位置
	D3DXVECTOR3 rot;											//向き
	D3DXMATRIX mtxWorld;									//ワールドマトリックス
	D3DXVECTOR3 vtxMinModel;						//モデルの最小値
	D3DXVECTOR3 vtxMaxModel;						//モデルの最大値
	int nIdxModelShadow;										//影の番号
	float fShadowWidth;										//影の幅
	float fShadowHeight;										//影の高さ

	bool bUse;														//モデルが使用されているかどうか
} Model;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model * GetModel(void);
void CollisionModel(D3DXVECTOR3 * pPos, D3DXVECTOR3  * pPosOld);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCntModel, float fShadowWidth, float fShadowHeight);
#endif
