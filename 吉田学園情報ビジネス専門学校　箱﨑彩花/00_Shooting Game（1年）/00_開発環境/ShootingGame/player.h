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
//マクロ定義
//===============================================================================
#define MAXPLAYER_LIFE		(3)	//プレイヤーの体力

//===============================================================================
//構造体の定義
//===============================================================================
typedef enum
{
	PLAYERSATATE_APPEAR = 0,	//出現状態
	PLAYERSTATE_NORMAL ,			//通常状態
	PLAYERSTATE_DAMADE,			//ダメージ状態
	PLAYERSTATE_DEATH,				//死亡状態
	PLAYERSTATE_MAX					//プレイヤーの種類の総数
} PLAYERSATATE;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int nLife;
	bool bDisp;						//表示するかしないか
	PLAYERSATATE state;	//プレイヤーの状態
	int nCounterState;			//状態管理のカウンター
} Player;

//===============================================================================
//プロトタイプ宣言
//===============================================================================
void InitPlayer(void);								//プレイヤー生成初期化処理
void UninitPlayer(void);							//プレイヤー生成終了処理
void UpdatePlayer(void);							//プレイヤー生成更新処理
void DrawPlayer(void);							//プレイヤーの描画処理
void HitPlayer(int nDamage);					//プレイヤーの当たり判定処理
Player * GetPlayer(void);

#endif