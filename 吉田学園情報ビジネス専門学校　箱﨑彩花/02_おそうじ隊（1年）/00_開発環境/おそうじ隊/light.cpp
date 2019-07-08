//=============================================================================
//
// ライト処理 [light.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIGHT (3)		//ライトの最大数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_light[MAX_LIGHT];	//ライトの種類

//=============================================================================
// ライトの初期化処理
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXVECTOR3 vecDir;											//設定用方向のベクトル
	int nCntLight;

	// ライトをクリアする
	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));
	}
	
	// ライトの種類を設定
	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;
	}

	// ライトの拡散光を設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	g_light[2].Diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

	// ライト1の方向の設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//正規化する
	g_light[0].Direction = vecDir;

	// ライト2の方向の設定
	vecDir = D3DXVECTOR3(-1.0f, 0.8f, -0.6f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//正規化する
	g_light[1].Direction = vecDir;

	// ライト3の方向の設定
	vecDir = D3DXVECTOR3(0.8f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//正規化する
	g_light[2].Direction = vecDir;

	// ライトを設定する
	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);
	}

	// ライトを有効にする
	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{
}