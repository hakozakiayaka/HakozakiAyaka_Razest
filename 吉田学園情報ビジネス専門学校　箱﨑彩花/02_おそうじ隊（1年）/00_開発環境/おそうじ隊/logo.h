#pragma once
//===============================================================================
//
// ロゴ設定 [logo.h]
// Author : 箱﨑彩花
//
//===============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"

//===============================================================================
//構造体の定義
//===============================================================================
typedef enum
{
	LOGOSTATE_NONE = 0,
	LOGOSTATE_LOGO,			//タイトル、クリア、ゲームオーバーのロゴ
	LOGOSTATE_ENTER,				//プレスエンター
	LOGOSTATE_RANKING,			//ランキングのロゴ
	LOGOSTATE_MAX
} LogoState;

typedef struct
{
	D3DXVECTOR3 pos;
	int nTexType;
	LogoState state;
	bool bUse;
} Logo;

//===============================================================================
//プロトタイプ宣言
//===============================================================================
void InitLogo(void);			//ロゴ初期化処理
void UninitLogo(void);		//ロゴ画面終了処理
void UpdateLogo(void);	//ロゴ画面更新処理
void DrawLogo(void);		//ロゴ画面描画処理
void SetLogo(D3DXVECTOR3 pos, int nTexType, LogoState state);		//ロゴを設定
#endif