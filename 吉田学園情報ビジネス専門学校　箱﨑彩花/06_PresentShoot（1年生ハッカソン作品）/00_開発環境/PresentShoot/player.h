//=============================================================================
//
// プレイヤー処理 [playrt.h]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYERSIZE_X	(160)
#define PLAYERSIZE_Y	(80)
#define POSCENTER_X		(PLAYERSIZE_X / 2)
#define POSCENTER_Y		(PLAYERSIZE_Y)
#define PLAYER_POS		(400)					//プレイヤーの画面の場所
#define PLAYER_LIFE		(6)						//プレイヤーのライフ

//=============================================================================
// プレイヤーの状態の種類
//=============================================================================
typedef enum
{//列挙型
	PLAYERSTATE_APPEAR = 0,	//出現状態,（0）
	PLAYERSTATE_NOMAL,		//通常状態（1）
	PLAYERSTATE_DAMAGE,		//ダメージ状態（2）
	PLAYERSTATE_DEATH,		//敵の死亡状態（3）
	PLAYERSTATE_MAX			//敵の状態の総数（4）
}PLAYERSTATE;

//=============================================================================
// 構造体の定義
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 posMove;
	D3DXVECTOR3 move;
	int nLife;				//ライフ
	PLAYERSTATE state;		//状態
	int nDirectionMove;
	int nCounterAnim;
	int nPatternAnim;
	int nCntstate;			//状態のカウンター
	bool bDisp;
}Player;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void HitPlayer(int nDamage);
Player *GetPlayer(void);
#endif