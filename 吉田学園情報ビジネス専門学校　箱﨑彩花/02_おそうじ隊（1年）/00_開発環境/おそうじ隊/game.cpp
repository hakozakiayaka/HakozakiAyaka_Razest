//===============================================================================
//
// ゲーム画面 [game.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "BG.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "fade.h"
#include "input.h"
#include "billboard.h"
#include "light.h"
#include "camera.h"
#include "meshCylinder.h"
#include "meshField.h"
#include "meshWall.h"
#include "model.h"
#include "shadow.h"
#include "result.h"
#include "score.h"
#include "time.h"
#include "enemy.h"
#include "effect.h"
#include "life.h"
#include "Pause.h"

//===============================================================================
//グローバル変数宣言
//===============================================================================
GAMESTATE g_gameState;	//ゲームの状態
int g_nCounterGameState;											//状態管理のカウンター
bool g_bPause;															//ポーズ中かどうか

//===============================================================================
//ゲーム画面初期化処理
//===============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NONE;	//通常状態に設定
	g_nCounterGameState = 0;
	g_bPause = false;

	//カメラの初期化処理
	InitCamera();
	//メッシュフィールドの初期化処理
	InitMeshField();
	//メッシュウォールの初期化処理
	InitMeshWall();
	//メッシュシリンダーの初期化処理
	//InitMeshCylinder();
	//影の初期化処理
	InitShadow();
	//ビルボードの初期化処理
	//InitBillboard();
	//エネミーの初期化処理
	InitEnemy();
	SetEnemy(D3DXVECTOR3(300.0f, 10.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(450.0f, 10.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(700.0f, 10.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(500.0f, 10.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

	//ライトの初期化処理
	InitLight();
	//弾の初期化処理
	InitBullet();
	//爆発の初期化処理
	InitExplosion();
	//	プレイヤー生成初期化処理
	InitPlayer();
	//モデルの初期化処理
	InitModel();
	SetModel(D3DXVECTOR3(50.0f, 0.0f, -10.0f), D3DXVECTOR3 (0.0f, 0.0f, 0.0f), 0, 60.0f, 20.0f);
	SetModel(D3DXVECTOR3(300.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 30.0f, 30.0f);
	SetModel(D3DXVECTOR3(5.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, -90.0f, 0.0f), 2, 30.0f, 30.0f);

	//スコアの初期化処理
	InitScore();
	//タイムの初期化処理
	InitTime();
	//エフェクトの初期化
	InitEffect();
	//ライフの初期化処理
	InitLife();
	//ポーズの初期化処理
	InitPausemenu();
}

//===============================================================================
//ゲーム画面終了処理
//===============================================================================
void UninitGame(void)
{
	//カメラの終了処理
	UninitCamera();
	//メッシュフィールドの終了処理
	UninitMeshField();
	//メッシュウォールの終了処理
	UninitMeshWall();
	//メッシュシリンダーの終了処理
	//UninitMeshCylinder();
	//影の終了処理
	UninitShadow();
	//ビルボードの終了処理
	//UninitBillboard();
	//エネミーの終了処理
	UninitEnemy();
	//ライトの終了処理
	UninitLight();
	//弾の終了処理
	UninitBullet();
	//爆発の終了処理
	UninitExplosion();
	//プレイヤー生成終了処理
	UninitPlayer();
	//モデルの終了処理
	UninitModel();
	//スコアの終了処理
	UninitScore();
	//タイムの終了処理
	UninitTime();
	//エフェクトの終了処理
	UninitEffect();
	//ライフの終了処理
	UninitLife();
	//ポーズの終了処理
	UninitPausemenu();
}

//===============================================================================
//ゲーム画面更新処理
//===============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{	//	ポーズの処理
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

		////フェードの取得
		//FADE g_fade = GetFade();

		////決定キーが押されたかどうか
		//if (GetKeyboardTrigger(DIK_RETURN) == true)
		//{
		//	if (g_fade != FADE_OUT)
		//	{	//フェードアウト中にEnterキーを押せなくする
		//		//モード設定
		//		SetFade(MODE_RESULT);
		//	}
		//}

			//カメラの更新処理
		UpdateCamera();
		//メッシュフィールドの更新処理
		UpdateMeshField();
		//メッシュウォールの更新処理
		UpdateMeshWall();
		//メッシュシリンダーの更新処理
		//UpdateMeshCylinder();
		//影の更新処理
		UpdateShadow();
		//ビルボードの更新処理
		//UpdateBillboard();
		//エネミーの更新処理
		UpdateEnemy();
		//ライトの更新処理
		UpdateLight();
		//弾の更新処理
		UpdateBullet();
		//爆発の更新処理
		UpdateExplosion();
		//プレイヤー生成更新処理
		UpdatePlayer();
		//モデルの更新処理
		UpdateModel();
		//スコアの更新処理
		UpdateScore();
		//タイムの更新処理
		UpdateTime();
		//エフェクトの更新処理
		UpdateEffect();
		//ライフの更新処理
		UpdateLife();
	}
	else
	{
		//ポーズの更新処理
		UpdatePausemenu();
	}
}

//===============================================================================
//ゲーム画面描画処理
//===============================================================================
void DrawGame(void)
{
	//カメラの設定
	SetCamera();
	//メッシュフィールドの描画処理
	DrawMeshField();
	//メッシュウォールの描画処理
	DrawMeshWall();
	//メッシュシリンダーの描画処理
	//DrawMeshCylinder();
	//影の描画処理
	DrawShadow();
	//ビルボードの描画処理
	//DrawBillboard();
	//エネミーの描画処理
	DrawEnemy();
	//弾の描画処理
	DrawBullet();
	//爆発の描画処理
	DrawExplosion();
	//プレイヤーの描画処理
	DrawPlayer();
	//モデルの描画処理
	DrawModel();
	//スコアの描画処理
	DrawScore();
	//タイムの描画処理
	DrawTime();
	//エフェクトの描画処理
	DrawEffect();
	//ライフの描画処理
	DrawLife();

	if (g_bPause == true)
	{
		//ポーズの描画処理
		DrawPausemenu();
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