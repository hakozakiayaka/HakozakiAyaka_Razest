//=============================================================================
//
// 爆発処理 [explosion.h]
// Author :箱﨑彩花
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);	//表示位置、色

#endif