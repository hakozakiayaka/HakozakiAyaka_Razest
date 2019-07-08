//=============================================================================
//
// ブロック処理 [block.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//=============================================================================
// 構造体の定義
//=============================================================================
typedef enum
{
	BLOCKTYPE_NORMAL = 0,		//ブロックの通常状態
	BLOCKTYPE_WIDTH,					//ブロックが動く（左右）
	BLOCKTYPE_MAX						//ブロックの種類の総数
} BLOCKTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fWidth;						//幅
	float fHeight;					//高さ
	BLOCKTYPE nType;		//ブロックの種類
	int nCntType;					//ブロックの種類のカウンター
	int nTexType;					//ブロックテクスチャの種類
	bool bLand;						//当たり判定が使用されているかどうか
	bool bUse;						//使用しているかどうか
} Block;

//=============================================================================
// ブロック状態の構造体の定義
//=============================================================================
typedef struct
{	//選択画面
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nTexType;
} BlockInfoSelect;

typedef struct
{	//おにぎり　ステージ1
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nTexType;
} BlockInfoStage1;

typedef struct
{	//ピーマン　ステージ2
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nTexType;
} BlockInfoStage2;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nTexType);
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, 
	D3DXVECTOR3 * pMove,float fWidth,float fHeight);		//現在の位置、前回の位置、移動量

#endif