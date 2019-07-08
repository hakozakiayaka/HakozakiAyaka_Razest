//=============================================================================
//
// 弾処理 [bullet.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// 弾のビルボードの構造体
//*****************************************************************************
typedef enum
{
	BULLETTYPE_ENEMY = 0,			//敵の弾
	BULLETTYPE_MAX
} BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 move;							//移動量
	D3DXMATRIX mtxWorldBullet;			//ワールドマトリックス
	int nIdxBulletShadow;							//影
	bool bUse;											//ビルボードが使われているかどうか
	D3DXVECTOR3 vecA;							//壁
	D3DXVECTOR3 vecC;							//aPosからBullet.posまでの距離
	BULLETTYPE type;								//弾の種類
} Bullet;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type);

#endif