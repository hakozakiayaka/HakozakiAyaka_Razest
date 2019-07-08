//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "pause.h"
#include "BG.h"
#include "StarBG.h"
#include "player.h"
#include "present.h"
#include "chimney.h"
#include "score.h"
#include "enemy.h"
#include "life.h"
#include "house.h"
#include "effect.h"
#include "sound.h"

//=============================================================================
// グローバル変数
//=============================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;		//ゲームの状態
int g_nCounterGameState;					//状態管理カウンター
int g_nCounterGame;							//エネミー出現のカウンター
bool g_bPause;								//ポーズを使用しているかどうか

//=============================================================================
// 初期化処理
//=============================================================================
void InitGame(void)
{
	//変数の初期化
	g_gameState = GAMESTATE_NORMAL;		//ゲームの状態
	g_nCounterGameState = 0;			//状態管理カウンター
	g_nCounterGame = 0;					//カウンター
	g_bPause = false;					//ポーズかどうか

	//関数呼び出し
	InitPause();					//ポーズ処理

	//背景のセット
	SetBG(6);

	InitStarBG();					//星空
	InitPresent();					//プレゼント
	InitEnemy();					//敵
	InitPlayer();					//プレイヤー
	InitChimney();					//煙突
	InitHouse();					//ハウス
	InitEffect();					//エフェクト
	InitScore();					//スコア
	InitLife();						//ライフ

	//敵のセット
	SetEnemy(D3DXVECTOR3(900, 300, 0.0f));
	SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, 200, 0.0f));
	SetEnemy(D3DXVECTOR3(2000, 300, 0.0f));
	SetEnemy(D3DXVECTOR3(2500, 150, 0.0f));
	SetEnemy(D3DXVECTOR3(3500, 200, 0.0f));
	SetEnemy(D3DXVECTOR3(4300, 150, 0.0f));
	SetEnemy(D3DXVECTOR3(5000, 100, 0.0f));
	SetEnemy(D3DXVECTOR3(5800, 300, 0.0f));
	SetEnemy(D3DXVECTOR3(6500, 150, 0.0f));
	SetEnemy(D3DXVECTOR3(7100, 200, 0.0f));
	SetEnemy(D3DXVECTOR3(8000, 300, 0.0f));

	//煙突のセット
	SetChimney(D3DXVECTOR3(540.0f, 430.0f, 0.0f), 40, 50);	//1
	SetChimney(D3DXVECTOR3(790.0f, 475.0f, 0.0f), 40, 60);	//2
	SetChimney(D3DXVECTOR3(1100.0f, 480.0f, 0.0f), 40, 90);	//3
	SetChimney(D3DXVECTOR3(1390.0f, 540.0f, 0.0f), 40, 70);	//4
	SetChimney(D3DXVECTOR3(1790.0f, 475.0f, 0.0f), 40, 60);	//5
	SetChimney(D3DXVECTOR3(2100.0f, 480.0f, 0.0f), 40, 90);	//6
	SetChimney(D3DXVECTOR3(2810.0f, 480.0f, 0.0f), 40, 90);	//8
	SetChimney(D3DXVECTOR3(3090.0f, 540.0f, 0.0f), 40, 70);	//9
	SetChimney(D3DXVECTOR3(3450.0f, 430.0f, 0.0f), 40, 50);	//10
	SetChimney(D3DXVECTOR3(4030.0f, 540.0f, 0.0f), 40, 70);	//13
	SetChimney(D3DXVECTOR3(4380.0f, 475.0f, 0.0f), 40, 60);	//14
	SetChimney(D3DXVECTOR3(4840.0f, 480.0f, 0.0f), 40, 90);	//15
	SetChimney(D3DXVECTOR3(5485.0f, 430.0f, 0.0f), 40, 50);	//18
	SetChimney(D3DXVECTOR3(5785.0f, 475.0f, 0.0f), 40, 60);	//19
	SetChimney(D3DXVECTOR3(6095.0f, 480.0f, 0.0f), 40, 90);	//20
	SetChimney(D3DXVECTOR3(6535.0f, 430.0f, 0.0f), 40, 50);	//21
	SetChimney(D3DXVECTOR3(7045.0f, 540.0f, 0.0f), 40, 70);	//23
	SetChimney(D3DXVECTOR3(7345.0f, 475.0f, 0.0f), 40, 60);	//24
	SetChimney(D3DXVECTOR3(8035.0f, 480.0f, 0.0f), 40, 90);	//27
	SetChimney(D3DXVECTOR3(8325.0f, 475.0f, 0.0f), 40, 60);	//28

	//家のセット
	SetHouse(1, D3DXVECTOR3(500.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 350);		//1つ目
	SetHouse(2, D3DXVECTOR3(750.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//2つ目
	SetHouse(0, D3DXVECTOR3(1050.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//3つ目
	SetHouse(3, D3DXVECTOR3(1350.0f, 640.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 200);		//4つ目
	SetHouse(2, D3DXVECTOR3(1750.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//5つ目
	SetHouse(0, D3DXVECTOR3(2050.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//6つ目
	SetHouse(4, D3DXVECTOR3(2355.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//7つ目 木
	SetHouse(0, D3DXVECTOR3(2760.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//8つ目 
	SetHouse(3, D3DXVECTOR3(3050.0f, 640.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//9つ目
	SetHouse(1, D3DXVECTOR3(3410.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 350);		//10つ目
	SetHouse(4, D3DXVECTOR3(3665.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//11つ目　木
	SetHouse(4, D3DXVECTOR3(3735.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//12つ目　木
	SetHouse(3, D3DXVECTOR3(3990.0f, 640.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 200);		//13つ目
	SetHouse(2, D3DXVECTOR3(4340.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//14つ目
	SetHouse(0, D3DXVECTOR3(4790.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//15つ目
	SetHouse(4, D3DXVECTOR3(5054.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//16つ目 木
	SetHouse(4, D3DXVECTOR3(5165.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//17つ目 木
	SetHouse(1, D3DXVECTOR3(5445.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 350);		//18つ目 
	SetHouse(2, D3DXVECTOR3(5745.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//19つ目
	SetHouse(0, D3DXVECTOR3(6045.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//20つ目 
	SetHouse(1, D3DXVECTOR3(6495.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 350);		//21つ目
	SetHouse(4, D3DXVECTOR3(6725.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//22つ目 木
	SetHouse(3, D3DXVECTOR3(7005.0f, 640.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 200);		//23つ目
	SetHouse(2, D3DXVECTOR3(7305.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//24つ目
	SetHouse(4, D3DXVECTOR3(7585.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//25つ目 木
	SetHouse(4, D3DXVECTOR3(7705.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//26つ目 木
	SetHouse(0, D3DXVECTOR3(7985.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//27つ目
	SetHouse(2, D3DXVECTOR3(8285.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 350);		//28つ目
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	//関数呼び出し
	UninitPause();		//ポーズ処理
	UninitStarBG();		//星空
	UninitPresent();	//プレゼント
	UninitEnemy();		//敵
	UninitPlayer();		//プレイヤー
	UninitHouse();		//家
	UninitChimney();	//煙突
	UninitEffect();		//エフェクト
	UninitScore();		//スコア
	UninitLife();		//ライフ
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{//ポーズON/OFF
		PlaySound(SOUND_LABEL_SE_PAUSE);
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		UpdateStarBG();		//星空
		UpdatePresent();	//プレゼント
		UpdateEnemy();		//敵
		UpdatePlayer();		//プレイヤー
		UpdateHouse();		//家
		UpdateChimney();	//煙突
		UpdateEffect();		//エフェクト
		UpdateScore();		//スコア
		UpdateLife();		//ライフ
	}
	else
	{
		UpdatePause();					//ポーズ処理
	}

	//フェード情報を取得する
	FADE fade;
	fade = GetFade();
	
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_END_CLIA:
		g_nCounterGameState++;	//状態管理カウンターを加算

		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			//フェードモード設定
			if (fade != FADE_OUT)
			{
				SetFade(MODE_RESULT);
			}
		}
		break;

	case GAMESTATE_END_OVER:
		g_nCounterGameState++;	//状態管理カウンターを加算

		if (g_nCounterGameState > 60)
		{
			g_gameState = GAMESTATE_NONE;

			//フェードモード設定
			if (fade != FADE_OUT)
			{
				SetFade(MODE_RESULTOVER);
			}
		}
		break;
	}

	if (GetKeyboardTrigger(DIK_F1) == true)
	{
		g_gameState = GAMESTATE_END_CLIA;
	}
	if (GetKeyboardTrigger(DIK_F2) == true)
	{
		g_gameState = GAMESTATE_END_OVER;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	DrawStarBG();		//星空
	DrawPresent();		//プレゼント
	DrawEnemy();		//敵
	DrawPlayer();		//プレイヤー
	DrawChimney();		//煙突
	DrawHouse();		//家
	DrawEffect();		//エフェクト
	DrawScore();		//スコア
	DrawLife();			//ライフ

	if (g_bPause == true)
	{
		DrawPause();	//ポーズ処理
	}
}

//=============================================================================
// ゲーム状態の設定
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=============================================================================
// ゲーム状態の取得
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=============================================================================
// ポーズ状態の取得
//=============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}