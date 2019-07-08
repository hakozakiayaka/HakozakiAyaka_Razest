//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// サウンドファイル
//*************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// タイトル
	SOUND_LABEL_BGM001,			// ゲーム
	SOUND_LABEL_BGM002,			// リザルト
	SOUND_LABEL_BGM003,			// ゲームオーバー
	SOUND_LABEL_SE_ITEM,		// アイテム
	SOUND_LABEL_SE_KARSOL,		// カーソル
	SOUND_LABEL_SE_ENTER,		// 決定音
	SOUND_LABEL_SE_PAUSE,		// 決定音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
