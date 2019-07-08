//=============================================================================
//
// 敵ブロック処理 [enemyblock.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _ENEMYBLOCK_H_
#define _ENEMYBLOCK_H_

#include "main.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef enum
{
	ENEMYBLOCKSTATE_NORMAL = 0,
	ENEMYBLOCKSTATE_DAMADE,
	ENEMYBLOCKSTATE_MAX				//敵ブロックの種類の総数
} ENEMYBLOCKSATATE;

typedef struct
{
	D3DXVECTOR3 pos;					//位置
	bool bUse;									//使用しているかどうか
	ENEMYBLOCKSATATE state;		//敵ブロックの状態
	int nCounterState;						//状態管理のカウンター
	float fWidth;
	float fHeight;
} ENEMYBLOCK;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitEnemyBlock(void);
void UninitEnemyBlock(void);
void UpdateEnemyBlock(void);
void DrawEnemyBlock(void);
void SetEnemyBlock(D3DXVECTOR3 pos, float fWidth, float fHight);
void CollisionEnemyBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld,
	D3DXVECTOR3 * pMove, float fWidth, float fHeight);

#endif