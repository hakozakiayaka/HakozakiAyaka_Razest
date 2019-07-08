//=============================================================================
//
// ­ [explosion.h]
// Author : ú±ÊÔ
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//=============================================================================
// \¢Ìè`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;							//Êu
	D3DXCOLOR col;									//F
	int nCounterAnim;								//Aj[VJE^[
	int nPatternAnim;								//Aj[VNo.
	D3DXMATRIX mtxWorldBullet;			//[h}gbNX
	int nIdxShadow;
	bool bUse;											//gpµÄ¢é©Ç¤©
} Explosion;

//=============================================================================
// vg^Cvé¾
//=============================================================================
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos,D3DXCOLOR col);	//\¦ÊuAF

#endif