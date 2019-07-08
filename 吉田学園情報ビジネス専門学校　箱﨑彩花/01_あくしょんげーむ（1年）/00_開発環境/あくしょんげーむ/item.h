//=============================================================================
//
// アイテム処理 [item.h]
// Author :箱﨑彩花
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "game.h"

//=============================================================================
// 構造体定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;				//色
	int nCounterAnim;			//アニメーションカウンター
	int nPatternAnim;			//アニメーションNo.
	int nType;							//アイテムの種類
	bool bUse;						//使用しているかどうか
} Item;

//=============================================================================
// アイテム情報の構造体定義
//=============================================================================
typedef struct
{	//選択画面
	D3DXVECTOR3 pos;		//アイテムの位置
	float fWidth;						//アイテムの幅
	float fHeight;					//アイテムの高さ
	int nType;							//アイテムの種類
} ItemInfoStageSelect;

typedef struct
{	//おにぎり　ステージ1
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
} ItemInfoStage1;

typedef struct
{	//ピーマン　ステージ2
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
} ItemInfoStage2;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeught, int nType);		//表示位置、幅、高さ、アイテムの種類
void CollisionItem(int nType);																				//アイテムの当たり判定
void DeleteItem(int nCntItem);																			//アイテムを消す処理
#endif