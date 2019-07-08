//=============================================================================
//
// e [bullet.h]
// Author :  ú±ÊÔ
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// eÌr{[hÌ\¢Ì
//*****************************************************************************
typedef enum
{
	BULLETTYPE_ENEMY = 0,			//GÌe
	BULLETTYPE_MAX
} BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;							//Êu
	D3DXVECTOR3 move;							//Ú®Ê
	D3DXMATRIX mtxWorldBullet;			//[h}gbNX
	int nIdxBulletShadow;							//e
	bool bUse;											//r{[hªgíêÄ¢é©Ç¤©
	D3DXVECTOR3 vecA;							//Ç
	D3DXVECTOR3 vecC;							//aPos©çBullet.posÜÅÌ£
	BULLETTYPE type;								//eÌíÞ
} Bullet;

//*****************************************************************************
// vg^Cvé¾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type);

#endif