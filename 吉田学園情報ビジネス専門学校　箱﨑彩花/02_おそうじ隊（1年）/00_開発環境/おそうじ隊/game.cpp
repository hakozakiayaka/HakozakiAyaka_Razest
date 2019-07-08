//===============================================================================
//
// Q[ζΚ [game.cpp]
// Author :  ϊ±ΚΤ
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
//O[oΟιΎ
//===============================================================================
GAMESTATE g_gameState;	//Q[ΜσΤ
int g_nCounterGameState;											//σΤΗΜJE^[
bool g_bPause;															//|[Y©Η€©

//===============================================================================
//Q[ζΚϊ»
//===============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NONE;	//ΚνσΤΙέθ
	g_nCounterGameState = 0;
	g_bPause = false;

	//JΜϊ»
	InitCamera();
	//bVtB[hΜϊ»
	InitMeshField();
	//bVEH[Μϊ»
	InitMeshWall();
	//bVV_[Μϊ»
	//InitMeshCylinder();
	//eΜϊ»
	InitShadow();
	//r{[hΜϊ»
	//InitBillboard();
	//Gl~[Μϊ»
	InitEnemy();
	SetEnemy(D3DXVECTOR3(300.0f, 10.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(450.0f, 10.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(700.0f, 10.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(500.0f, 10.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

	//CgΜϊ»
	InitLight();
	//eΜϊ»
	InitBullet();
	//­Μϊ»
	InitExplosion();
	//	vC[Ά¬ϊ»
	InitPlayer();
	//fΜϊ»
	InitModel();
	SetModel(D3DXVECTOR3(50.0f, 0.0f, -10.0f), D3DXVECTOR3 (0.0f, 0.0f, 0.0f), 0, 60.0f, 20.0f);
	SetModel(D3DXVECTOR3(300.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 30.0f, 30.0f);
	SetModel(D3DXVECTOR3(5.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, -90.0f, 0.0f), 2, 30.0f, 30.0f);

	//XRAΜϊ»
	InitScore();
	//^CΜϊ»
	InitTime();
	//GtFNgΜϊ»
	InitEffect();
	//CtΜϊ»
	InitLife();
	//|[YΜϊ»
	InitPausemenu();
}

//===============================================================================
//Q[ζΚIΉ
//===============================================================================
void UninitGame(void)
{
	//JΜIΉ
	UninitCamera();
	//bVtB[hΜIΉ
	UninitMeshField();
	//bVEH[ΜIΉ
	UninitMeshWall();
	//bVV_[ΜIΉ
	//UninitMeshCylinder();
	//eΜIΉ
	UninitShadow();
	//r{[hΜIΉ
	//UninitBillboard();
	//Gl~[ΜIΉ
	UninitEnemy();
	//CgΜIΉ
	UninitLight();
	//eΜIΉ
	UninitBullet();
	//­ΜIΉ
	UninitExplosion();
	//vC[Ά¬IΉ
	UninitPlayer();
	//fΜIΉ
	UninitModel();
	//XRAΜIΉ
	UninitScore();
	//^CΜIΉ
	UninitTime();
	//GtFNgΜIΉ
	UninitEffect();
	//CtΜIΉ
	UninitLife();
	//|[YΜIΉ
	UninitPausemenu();
}

//===============================================================================
//Q[ζΚXV
//===============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{	//	|[YΜ
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
				//ζΚ([h)Μέθ
				SetFade(MODE_RESULT);
			}
			break;

		case GAMESTATE_OVER:
			g_nCounterGameState++;
			if (g_nCounterGameState <= 60)
			{
				//ζΚ([h)Μέθ
				SetFade(MODE_RESULT);
			}
			break;
		}

		////tF[hΜζΎ
		//FADE g_fade = GetFade();

		////θL[ͺ³κ½©Η€©
		//if (GetKeyboardTrigger(DIK_RETURN) == true)
		//{
		//	if (g_fade != FADE_OUT)
		//	{	//tF[hAEgΙEnterL[πΉΘ­·ι
		//		//[hέθ
		//		SetFade(MODE_RESULT);
		//	}
		//}

			//JΜXV
		UpdateCamera();
		//bVtB[hΜXV
		UpdateMeshField();
		//bVEH[ΜXV
		UpdateMeshWall();
		//bVV_[ΜXV
		//UpdateMeshCylinder();
		//eΜXV
		UpdateShadow();
		//r{[hΜXV
		//UpdateBillboard();
		//Gl~[ΜXV
		UpdateEnemy();
		//CgΜXV
		UpdateLight();
		//eΜXV
		UpdateBullet();
		//­ΜXV
		UpdateExplosion();
		//vC[Ά¬XV
		UpdatePlayer();
		//fΜXV
		UpdateModel();
		//XRAΜXV
		UpdateScore();
		//^CΜXV
		UpdateTime();
		//GtFNgΜXV
		UpdateEffect();
		//CtΜXV
		UpdateLife();
	}
	else
	{
		//|[YΜXV
		UpdatePausemenu();
	}
}

//===============================================================================
//Q[ζΚ`ζ
//===============================================================================
void DrawGame(void)
{
	//JΜέθ
	SetCamera();
	//bVtB[hΜ`ζ
	DrawMeshField();
	//bVEH[Μ`ζ
	DrawMeshWall();
	//bVV_[Μ`ζ
	//DrawMeshCylinder();
	//eΜ`ζ
	DrawShadow();
	//r{[hΜ`ζ
	//DrawBillboard();
	//Gl~[Μ`ζ
	DrawEnemy();
	//eΜ`ζ
	DrawBullet();
	//­Μ`ζ
	DrawExplosion();
	//vC[Μ`ζ
	DrawPlayer();
	//fΜ`ζ
	DrawModel();
	//XRAΜ`ζ
	DrawScore();
	//^CΜ`ζ
	DrawTime();
	//GtFNgΜ`ζ
	DrawEffect();
	//CtΜ`ζ
	DrawLife();

	if (g_bPause == true)
	{
		//|[YΜ`ζ
		DrawPausemenu();
	}
}

//===============================================================================
//Q[ΜσΤέθ
//===============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//===============================================================================
//Q[σΤΜζΎ
//===============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//===============================================================================
//|[YσΤΜζΎ
//===============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}