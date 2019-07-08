//=============================================================================
//
// プレイヤー処理 [titleplayrt.h]
// Author : 高橋美優
//
//=============================================================================
#ifndef _TITLEPLAYER_H_
#define _TITLEPLAYER_H_

#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TITLEPLAYERSIZE_X	(160)
#define TITLEPLAYERSIZE_Y	(80)
#define POSCENTER_X		(TITLEPLAYERSIZE_X / 2)
#define POSCENTER_Y		(TITLEPLAYERSIZE_Y)
#define TITLEPLAYER_POS		(400)					//プレイヤーの画面の場所
#define TITLEPLAYER_LIFE	(1)						//プレイヤーのライフ

//=============================================================================
// プレイヤーの状態の種類
//=============================================================================

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
	int nDirectionMove;
	int nCounterAnim;
	int nPatternAnim;
	bool bDisp;
}TitlePlayer;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void InitTitlePlayer(void);
void UninitTitlePlayer(void);
void UpdateTitlePlayer(void);
void DrawTitlePlayer(void);

TitlePlayer *GetTitlePlayer(void);
#endif