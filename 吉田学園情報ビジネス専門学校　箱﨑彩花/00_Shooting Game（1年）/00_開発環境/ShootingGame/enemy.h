//=============================================================================
//
// 敵処理 [enemy.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define	MAX_ENEMY	(256)	// 敵の最大数

//=============================================================================
// 構造体定義
//=============================================================================
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMADE,
	ENEMYSTATE_MAX				//敵の種類の総数
} ENEMYSATATE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	int nType;							//種類
	int nLife;							//体力
	bool bUse;						//使用しているかどうか
	ENEMYSATATE state;		//敵の状態
	int nCounterState;			//状態管理のカウンター
	int nCntAnim;					//アニメーションカウンター
	int nPatternAnim;			//アニメーションのパターン数
	int nCntMove;					//敵の移動カウンター
	int nChangeMove;			//敵の移動量
} Enemy;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType, int ChangeMove);
Enemy * GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif