//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_SPEED	(0.6f)					//カメラのスピード
#define VIEW_Y					(90.0f)				//視点のY座標
#define VIEW_Z					(210.0f)				//視点のZ座標

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_camera;	//カメラの情報

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	//構造体の初期化
	g_camera.posV = D3DXVECTOR3(0.0f, VIEW_Y, -VIEW_Z);		//視点
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//注視点
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//上方向ベクトル
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//向き
	g_camera.distance = VIEW_Z;													//距離
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	float fDestAngle = 0;
	float fMoveAngle = 0;

	//モデルの取得
	Player * pPlayer = GetPlayer();

	//モデルにカメラが追従する
	g_camera.posV.x = pPlayer->pos.x;
	g_camera.posV.z = pPlayer->pos.z - g_camera.distance;

	g_camera.posR.x = g_camera.posV.x + sinf(0.0f + g_camera.rot.y) * g_camera.distance;
	g_camera.posR.z = g_camera.posV.z + cosf(0.0f + g_camera.rot.y) * g_camera.distance;

#if 0
	//カメラ移動 (W,S,A,D)
	if (GetKeyboardPress(DIK_W) == true)
	{	//Wキーが押された
		g_camera.posV.x += sinf(0.0f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posV.z += cosf(0.0f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posR.x = g_camera.posV.x + sinf(0.0f + g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(0.0f + g_camera.rot.y) * g_camera.distance;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{	//Sキーが押された
		g_camera.posV.x += sinf(D3DX_PI + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posV.z += cosf(D3DX_PI + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posR.x = g_camera.posV.x + sinf(0.0f + g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(0.0f + g_camera.rot.y) * g_camera.distance;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{	//Aキーが押された
		g_camera.posV.x += sinf(D3DX_PI * -0.5f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posV.z += cosf(D3DX_PI * -0.5f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posR.x = g_camera.posV.x + sinf(0.0f + g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(0.0f + g_camera.rot.y) * g_camera.distance;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{	//Dキーが押された
		g_camera.posV.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posV.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posR.x = g_camera.posV.x + sinf(0.0f + g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(0.0f + g_camera.rot.y) * g_camera.distance;
	}
#endif

	//視点操作 (Y,N)
	if (GetKeyboardPress(DIK_Y) == true)
	{	//Yキーが押された
		g_camera.posV.x += sinf(0.0f) * CAMERA_SPEED;
		g_camera.posV.y += cosf(0.0f) * CAMERA_SPEED;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{	//Nキーが押された
		g_camera.posV.x += sinf(D3DX_PI) * CAMERA_SPEED;
		g_camera.posV.y += cosf(D3DX_PI) * CAMERA_SPEED;
	}

	//注視点操作 (T,B)
	if (GetKeyboardPress(DIK_T) == true)
	{	//Tキーが押された
		g_camera.posR.x += sinf(0.0f) * CAMERA_SPEED;
		g_camera.posR.y += cosf(0.0f) * CAMERA_SPEED;
	}
	if (GetKeyboardPress(DIK_B) == true)
	{	//Bキーが押された
		g_camera.posR.x += sinf(D3DX_PI) * CAMERA_SPEED;
		g_camera.posR.y += cosf(D3DX_PI) * CAMERA_SPEED;
	}

	////視点旋回 (Z,C)
	//if (GetKeyboardPress(DIK_Z) == true)
	//{	//Zキーが押された
	//	g_camera.rot.y += 0.02f;		//回転の速さ
	//	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y - D3DX_PI) * g_camera.distance;
	//	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y - D3DX_PI) * g_camera.distance;
	//}
	//if (GetKeyboardPress(DIK_C) == true)
	//{	//Cキーが押された
	//	g_camera.rot.y -= 0.02f;
	//	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y - D3DX_PI) * g_camera.distance;
	//	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y - D3DX_PI) * g_camera.distance;
	//}

	//注視点旋回
	if (GetKeyboardPress(DIK_Q) == true)
	{	//Qキーが押された
		g_camera.rot.y -= 0.02f;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.distance;
	}
	if (GetKeyboardPress(DIK_E) == true)
	{	//Eキーが押された
		g_camera.rot.y += 0.02f;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.distance;
	}


	////角度の修正
	//g_camera.rot.y = fDestAngle - fMoveAngle;
	//if (g_camera.rot.y > D3DX_PI)
	//{
	//	g_camera.rot.y -= D3DX_PI * 2.0f;
	//}
	//if (g_camera.rot.y < D3DX_PI)
	//{
	//	g_camera.rot.y += D3DX_PI * 2.0f;
	//}
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f,10000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//=============================================================================
// カメラの取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}