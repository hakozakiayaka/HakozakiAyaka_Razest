#pragma once
//===============================================================================
//
// タイトル画面 [title.h]
// Author : 箱﨑彩花
//
//===============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//===============================================================================
//構造体の定義
//===============================================================================
typedef enum
{
	TITLESTATE_NONE = 0,
	TITLESTATE_NORMAL,
	TITLESTATE_RANKING,
	TITLESTATE_MAX
} TitleState;

typedef struct
{
	TitleState state;			//タイトルの状態
	D3DXVECTOR3 pos;	//位置
	int nCnt;
	float fFlash;
	D3DXCOLOR col;
	bool bUse;					//使用しているかどうか
} Title;

//===============================================================================
//プロトタイプ宣言
//===============================================================================
void InitTitle(void);			//タイトル画面初期化処理
void UninitTitle(void);		//タイトル画面終了処理
void UpdateTitle(void);	//タイトル画面更新処理
void DrawTitle(void);		//タイトル画面描画処理

#endif