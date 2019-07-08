//===============================================================================
//
// プレイヤーの生成処理 [player.h]
// Author : 箱﨑彩花
//
//===============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//===============================================================================
//構造体の定義
//===============================================================================
typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//プレイヤーの通常状態
	PLAYERSTATE_SIZEUP,				//キノコ取った時の状態
	PLAYERSTATE_SIZEDOWN,		//ピーマン取った時の状態
	PLAYERSTATE_MAX
} PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;	//前回の位置
	D3DXVECTOR3 move;		//移動量
	bool bDisp;						//表示するかしないか
	bool bJump;						//ジャンプしているかどうか
	bool bUse;						//使用しているかどうか
	bool bLand;						//当たり判定が使用されているかどうか
	int nCntAnim;					//アニメーションカウンター
	int nPatternAnim;			//アニメーションのパターン数
	int DirectionMove;
	int nWidth;						//幅
	int nHeight;						//	高さ
	PLAYERSTATE state;		//プレイヤーの状態
} Player;

//===============================================================================
//プロトタイプ宣言
//===============================================================================
void InitPlayer(void);								//プレイヤー生成初期化処理
void UninitPlayer(void);							//プレイヤー生成終了処理
void UpdatePlayer(void);							//プレイヤー生成更新処理
void DrawPlayer(void);							//プレイヤーの描画処理
Player * GetPlayer(void);

#endif