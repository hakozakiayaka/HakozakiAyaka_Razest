//===============================================================================
//
// ゲーム画面 [game.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include"bg.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "game.h"
#include "score.h"
#include "effect.h"
#include "fade.h"
#include "input.h"
#include "pause.h"
#include "time.h"
#include "life.h"
#include "sound.h"

//===============================================================================
//グローバル変数宣言
//===============================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;	//ゲームの状態
int g_nCounterGameState;											//状態管理のカウンター
bool g_bPause;															//ポーズ中かどうか

//===============================================================================
//ゲーム画面初期化処理
//===============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;	//通常状態に設定
	g_nCounterGameState = 0;
	g_bPause = false;

	//背景初期化処理
	InitBG();
	//	プレイヤー生成初期化処理
	InitPlayer();
	//弾の発射の初期化処理
	InitBullet();
	//爆発の発射の初期化処理
	InitExplosion();
	//スコアの初期化処理
	InitScore();
	//エフェクトの初期化処理
	InitEffect();
	//ポーズの初期化処理
	InitPause();
	//タイムの初期化処理
	InitTime();
	//ライフの初期化処理
	InitLife();
	//敵の初期化処理処理
	InitEnemy();
	//上から一列目
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE2, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE3, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE4, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE5, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE6, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE7, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE8, ENEMY_HEIGHT, 0.0f), 0,2);

	//二列目
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE2, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE3, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE4, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE5, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE6, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE7, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE8, ENEMY_HEIGHT2, 0.0f), 1,-1);

	//三列目
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE2, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE3, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE4, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE5, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE6, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE7, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE8, ENEMY_HEIGHT3, 0.0f), 2,1);

	//四列目
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE2, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE3, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE4, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE5, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE6, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE7, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE8, ENEMY_HEIGHT4, 0.0f), 3,-2);

}

//===============================================================================
//ゲーム画面終了処理
//===============================================================================
void UninitGame(void)
{
	//背景終了処理
	UninitBG();
	//プレイヤー生成終了処理
	UninitPlayer();
	//弾の発射処理
	UninitBullet();
	//爆発の発射処理
	UninitExplosion();
	//スコアの終了処理
	UninitScore();
	//エフェクトの終了処理
	UninitEffect();
	//敵の終了処理
	UninitEnemy();
	//ポーズの終了処理
	UninitPause();
	//タイムの終了処理
	UninitTime();
	//ライフの終了処理
	UninitLife();
}

//===============================================================================
//ゲーム画面更新処理
//===============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{	//	ポーズの処理
		PlaySound(SOUND_LABEL_SE_PAUSE);
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			break;

		case GAMESTATE_CLEAR:
			g_nCounterGameState++;
			if (g_nCounterGameState <= 60)
			{
				//画面(モード)の設定
				SetFade(MODE_RESULT);
			}
			break;

		case GAMESTATE_OVER:
			g_nCounterGameState++;
			if (g_nCounterGameState <= 60)
			{
				//画面(モード)の設定
				SetFade(MODE_RESULT);
			}
			break;
		}

		//背景更新処理
		UpdateBG();
		//プレイヤー生成更新処理
		UpdatePlayer();
		//弾の発射処理
		UpdateBullet();
		//爆発の発射処理
		UpdateExplosion();
		//スコアの更新処理
		UpdateScore();
		//エフェクトの更新処理
		UpdateEffect();
		//敵の更新処理
		UpdateEnemy();
		//タイムの更新処理
		UpdateTime();
		//ライフの更新処理
		UpdateLife();
	}
	else
	{
		//ポーズの更新処理
		UpdatePause();
	}
}

//===============================================================================
//ゲーム画面描画処理
//===============================================================================
void DrawGame(void)
{
	//背景描画処理
	DrawBG();
	//プレイヤーの描画処理
	DrawPlayer();
	//弾の発射処理
	DrawBullet();
	//爆発の発射処理
	DrawExplosion();
	//スコアの描画処理
	DrawScore();
	//エフェクトの描画処理
	DrawEffect();
	//敵の描画処理
	DrawEnemy();
	//タイムの描画処理
	DrawTime();
	//ライフの描画処理
	DrawLife();

	if (g_bPause == true)
	{
		//ポーズの描画処理
		DrawPause();
	}
}

//===============================================================================
//ゲームの状態設定
//===============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//===============================================================================
//ゲーム状態の取得
//===============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//===============================================================================
//ポーズ状態の取得
//===============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}