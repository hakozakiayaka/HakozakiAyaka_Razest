//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "player.h"			//プレイヤー
#include "input.h"			//キーボード
#include "camera.h"		//カメラ
#include "shadow.h"		//影
#include "bullet.h"			//弾
#include "score.h"			//スコア
#include "meshField.h"	//メッシュフィールド
#include "model.h"			//モデル
#include "life.h"				//ライフ
#include "explosion.h"		//爆発
#include "game.h"			//ゲーム

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME			"data\\MODEL\\j_body.x"			//読み込むテクスチャファイル
#define MODEL_NAME2			"data\\MODEL\\j_head.x"			//読み込むテクスチャファイル
#define MODEL_NAME3			"data\\MODEL\\j_arm_Right.x"			//読み込むテクスチャファイル
#define MODEL_NAME4			"data\\MODEL\\j_hand_Right.x"			//読み込むテクスチャファイル
#define MODEL_NAME5			"data\\MODEL\\j_arm_Left.x"			//読み込むテクスチャファイル
#define MODEL_NAME6			"data\\MODEL\\j_hand_Left.x"			//読み込むテクスチャファイル
#define MODEL_NAME7			"data\\MODEL\\j_thigh_Right.x"			//読み込むテクスチャファイル
#define MODEL_NAME8			"data\\MODEL\\j_shin_Right.x"			//読み込むテクスチャファイル
#define MODEL_NAME9			"data\\MODEL\\j_foot_Right.x"			//読み込むテクスチャファイル
#define MODEL_NAME10		"data\\MODEL\\j_thigh_Left.x"			//読み込むテクスチャファイル
#define MODEL_NAME11		"data\\MODEL\\j_shin_Left.x"			//読み込むテクスチャファイル
#define MODEL_NAME12		"data\\MODEL\\j_foot_Left.x"			//読み込むテクスチャファイル
#define MODEL_NAME13		"data\\MODEL\\zoukin.x"			//読み込むテクスチャファイル

#define MAX_PARTS				(13)
#define MODEL_SPEED			(1.0f)								//プレイヤースピード
#define DAMAGE_STATE		(7)									//ダメージ状態

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player g_Player;						//プレイヤー
int g_nIdxPlayerShadow;			//どの影を使っているか
int g_nCount1;							//モーションカウント

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;															//頂点数
	DWORD sizeFVF;													//頂点フォーマットのサイズ
	BYTE * pVtxBuff;														//頂点バッファへのポインタ

	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[0].pBuffMatModel,
		NULL,
		&g_Player.aModel[0].nNumMatModel,
		&g_Player.aModel[0].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[1].pBuffMatModel,
		NULL,
		&g_Player.aModel[1].nNumMatModel,
		&g_Player.aModel[1].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[2].pBuffMatModel,
		NULL,
		&g_Player.aModel[2].nNumMatModel,
		&g_Player.aModel[2].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME4,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[3].pBuffMatModel,
		NULL,
		&g_Player.aModel[3].nNumMatModel,
		&g_Player.aModel[3].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME5,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[4].pBuffMatModel,
		NULL,
		&g_Player.aModel[4].nNumMatModel,
		&g_Player.aModel[4].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME6,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[5].pBuffMatModel,
		NULL,
		&g_Player.aModel[5].nNumMatModel,
		&g_Player.aModel[5].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME7,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[6].pBuffMatModel,
		NULL,
		&g_Player.aModel[6].nNumMatModel,
		&g_Player.aModel[6].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME8,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[7].pBuffMatModel,
		NULL,
		&g_Player.aModel[7].nNumMatModel,
		&g_Player.aModel[7].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME9,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[8].pBuffMatModel,
		NULL,
		&g_Player.aModel[8].nNumMatModel,
		&g_Player.aModel[8].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME10,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[9].pBuffMatModel,
		NULL,
		&g_Player.aModel[9].nNumMatModel,
		&g_Player.aModel[9].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME11,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[10].pBuffMatModel,
		NULL,
		&g_Player.aModel[10].nNumMatModel,
		&g_Player.aModel[10].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME12,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[11].pBuffMatModel,
		NULL,
		&g_Player.aModel[11].nNumMatModel,
		&g_Player.aModel[11].pMeshModel
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		MODEL_NAME13,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[12].pBuffMatModel,
		NULL,
		&g_Player.aModel[12].nNumMatModel,
		&g_Player.aModel[12].pMeshModel
	);

	// 位置・向きの初期設定
	g_Player.pos = D3DXVECTOR3(100, 25, -500);
	g_Player.rot = D3DXVECTOR3(0, 0, 0);
	g_Player.move = D3DXVECTOR3(0, 0, 0);
	g_nCount1 = 0;
	g_Player.vtxMinPlayer = D3DXVECTOR3(10000, 10000, 10000);
	g_Player.vtxMaxPlayer = D3DXVECTOR3(-10000, -10000, -10000);
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.bDisp = true;
	g_Player.nCntState = 0;
	g_Player.nLife = PLAYER_LIFE;
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//親の番号
	g_Player.aModel[0].nIdxModelParent = -1;					//体
	g_Player.aModel[1].nIdxModelParent =  0;					//頭
	g_Player.aModel[2].nIdxModelParent =  0;					//右腕
	g_Player.aModel[3].nIdxModelParent =  2;					//右手
	g_Player.aModel[4].nIdxModelParent =  0;					//左腕
	g_Player.aModel[5].nIdxModelParent =  4;					//左手
	g_Player.aModel[6].nIdxModelParent =  0;					//右もも
	g_Player.aModel[7].nIdxModelParent = 6;						//右すね
	g_Player.aModel[8].nIdxModelParent =  7;					//右足
	g_Player.aModel[9].nIdxModelParent =  0;					//左もも
	g_Player.aModel[10].nIdxModelParent = 9;					//左すね
	g_Player.aModel[11].nIdxModelParent =  10;				//左足
	g_Player.aModel[12].nIdxModelParent = 3;					//雑巾				右手につける

	//モデル親とコモドのposの位置
	g_Player.aModel[0].posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//体
	g_Player.aModel[1].posModel = D3DXVECTOR3(0.0f, 28.0f, 0.0f);			//頭
	g_Player.aModel[2].posModel = D3DXVECTOR3(-8.0f, 21.0f, 0.0f);			//右腕
	g_Player.aModel[3].posModel = D3DXVECTOR3(-20.0f, 0.0f, 0.0f);			//右手
	g_Player.aModel[4].posModel = D3DXVECTOR3(8.0f, 21.0f, 0.0f); 			//左腕
	g_Player.aModel[5].posModel = D3DXVECTOR3(20.0f, 0.0f, 0.0f);			//左手
	g_Player.aModel[6].posModel = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);			//右もも
	g_Player.aModel[7].posModel = D3DXVECTOR3(-0.5f, -15.0f, 0.0f);		//右すね
	g_Player.aModel[8].posModel = D3DXVECTOR3(0.0f, -12.0f, 0.0f);			//右足
	g_Player.aModel[9].posModel = D3DXVECTOR3(4.0f, 0.0f, 0.0f);				//左もも
	g_Player.aModel[10].posModel = D3DXVECTOR3(0.5f, -15.0f, 0.0f);		//左すね
	g_Player.aModel[11].posModel = D3DXVECTOR3(0.0f, -12.0f, 0.0f);		//左足
	g_Player.aModel[12].posModel = D3DXVECTOR3(1.5f, -12.0f, 0.0f);		//雑巾

	//モデル親とコモドのrotの位置
	g_Player.aModel[0].rotModel = D3DXVECTOR3(-1.94f, -0.19f, 0.0f);			//体
	g_Player.aModel[1].rotModel = D3DXVECTOR3(0.81f, -0.16f, 0.0f);				//頭
	g_Player.aModel[2].rotModel = D3DXVECTOR3(2.7f, -0.0f, 1.25f);			//右腕
	g_Player.aModel[3].rotModel = D3DXVECTOR3(0.0f, -0.12f, 0.0f);				//右手
	g_Player.aModel[4].rotModel = D3DXVECTOR3(2.7f, 0.0f, -1.56f); 			//左腕
	g_Player.aModel[5].rotModel = D3DXVECTOR3(0.0f, 0.02f, 0.0f);				//左手
	g_Player.aModel[6].rotModel = D3DXVECTOR3(0.89f, 0.0f, -0.03f);				//右もも
	g_Player.aModel[7].rotModel = D3DXVECTOR3(-0.28f, 0.0f, 0.0f);				//右すね
	g_Player.aModel[8].rotModel = D3DXVECTOR3(0.28f, 0.0f, 0.0f);				//右足
	g_Player.aModel[9].rotModel = D3DXVECTOR3(2.14f, 0.0f, 0.0f);				//左もも
	g_Player.aModel[10].rotModel = D3DXVECTOR3(2.04f, -1.29f, 1.45f);			//左すね
	g_Player.aModel[11].rotModel = D3DXVECTOR3(0.13f, -2.67f, -0.09f);		//左足
	g_Player.aModel[12].rotModel = D3DXVECTOR3(0.0f, -2.1f, 1.5f);				//雑巾

	//頂点数を取得
	nNumVtx = g_Player.aModel[0].pMeshModel->GetNumVertices();

	//頂点フォーマットのサイズ
	sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[0].pMeshModel->GetFVF());

	//頂点フォーマットをロック
	g_Player.aModel[0].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{	//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

		//最小値
		if (vtx.x < g_Player.vtxMinPlayer.x)
		{
			g_Player.vtxMinPlayer.x = vtx.x;
		}
		if (vtx.z < g_Player.vtxMinPlayer.z)
		{
			g_Player.vtxMinPlayer.z = vtx.z;
		}

		//最大値
		if (vtx.x > g_Player.vtxMaxPlayer.x)
		{
			g_Player.vtxMaxPlayer.x = vtx.x;
		}
		if (vtx.z > g_Player.vtxMaxPlayer.z)
		{
			g_Player.vtxMaxPlayer.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	g_Player.aModel[0].pMeshModel->UnlockVertexBuffer();

	g_nIdxPlayerShadow = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30, 30);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// メッシュの開放
		if (g_Player.aModel[nCount].pMeshModel != NULL)
		{
			g_Player.aModel[nCount].pMeshModel->Release();
			g_Player.aModel[nCount].pMeshModel = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// マテリアルの開放
		if (g_Player.aModel[nCount].pBuffMatModel != NULL)
		{
			g_Player.aModel[nCount].pBuffMatModel->Release();
			g_Player.aModel[nCount].pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//カメラの情報
	Camera *pCamera = GetCamera();
	MESHFIELD * pMeshField = GetMeshField();

	//前回の位置を保存
	g_Player.posOld = g_Player.pos;

	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMADE:
		g_Player.nCntState--;
		if (g_Player.nCntState <= 0)
		{
			g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		break;

	case PLAYERSTATE_DEATH:
		g_Player.nCntState--;
		return;
		break;
	}

	float nSpeed = 5.0f;	//速度
	//float fDifrot.y;

	//移動範囲の判定
	if (g_Player.pos.z > pMeshField->pos.z + 95)			//プレイヤーのposから壁の距離を入れる
	{	//奥
		g_Player.pos.z = pMeshField->pos.z + 95;
	}
	if (g_Player.pos.z < pMeshField->pos.z - 895)
	{	//手前
		g_Player.pos.z = pMeshField->pos.z - 895;
	}
	if (g_Player.pos.x > pMeshField->pos.x + 895)
	{	//右
		g_Player.pos.x = pMeshField->pos.x + 895;
	}
	if (g_Player.pos.x < pMeshField->pos.x - 95)
	{	//左
		g_Player.pos.x = pMeshField->pos.x - 95;
	}

	//fDifrot.y = (pCamera->rot.y + D3DX_PI) - g_Player.rot.y;
	//if (fDifrot.y > D3DX_PI)
	//{
	//	fDifrot.y -= D3DX_PI * 2.0;
	//}
	//else if (fDifrot.y < -D3DX_PI)
	//{
	//	fDifrot.y += D3DX_PI * 2.0;
	//}

	//g_Player.rot.y += fDifrot.y * 0.4f;

	//if (g_Player.rot.y > D3DX_PI)
	//{
	//	fDifrot.y -= D3DX_PI * 2.0;
	//}
	//else if (g_Player.rot.y < -D3DX_PI)
	//{
	//	fDifrot.y += D3DX_PI * 2.0;
	//}

	//移動処理
	if (GetKeyboardPress(DIK_UP) == true)
	{//矢印の上							↓上移動
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * -0.75f) + pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * 0.75f) + pCamera->rot.y);
		}
		else
		{
			g_Player.move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * -1.0f) + pCamera->rot.y);
		}
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//矢印の下							 ↓上移動
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * -0.25f) + pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * 0.25f) + pCamera->rot.y);
		}
		else
		{
			g_Player.move.x += sinf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * 0.0f) + pCamera->rot.y);
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//矢印の右							↓ 右移動
		g_Player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* MODEL_SPEED;
		//その方向に向く
		g_Player.rot.y = ((D3DX_PI * -0.5f) + pCamera->rot.y);
	}
	else if (GetKeyboardPress(DIK_LEFT) == true)
	{//矢印の左							 ↓ 左移動
		g_Player.move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player.move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		//その方向に向く
		g_Player.rot.y = ((D3DX_PI * 0.5f) + pCamera->rot.y);
	}
	if (GetKeyboardPress(DIK_T) == true)
	{//上移動			
		g_Player.pos.y += 0.3f;
	}
	if (GetKeyboardPress(DIK_G) == true)
	{//下移動						
		g_Player.pos.y -= 0.3f;
	}
	//位置を移動に代入
	g_Player.pos += g_Player.move;

	//慣性をつける
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.2f;

	////弾発射
	//if (GetKeyboardTrigger(DIK_SPACE) == true)
	//{
	//	SetBullet(g_Player.pos, g_Player.rot, BULLETTYPE_PLAYER);
	//}

	//あたり判定
	CollisionModel(&g_Player.pos, &g_Player.posOld);

	//影の位置設定
	SetPositionShadow(g_nIdxPlayerShadow, g_Player.pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;						//

	if (g_Player.bDisp == true)
	{
		{//プレイヤー
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player.mtxWorldPlayer);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
			D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
			D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorldPlayer);
		}

		for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
		{
			if (g_Player.aModel[nCntParts].nIdxModelParent < 0)
			{//親モデル
				mtxParent = g_Player.mtxWorldPlayer;
			}
			else
			{//子モデル
				mtxParent = g_Player.aModel[g_Player.aModel[nCntParts].nIdxModelParent].mtxWorldModel;
			}
			{//親モデル
				// ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorldModel);
				// 回転を反映
				D3DXMatrixRotationYawPitchRoll
				(
					&mtxRot,
					g_Player.aModel[nCntParts].rotModel.y,
					g_Player.aModel[nCntParts].rotModel.x,
					g_Player.aModel[nCntParts].rotModel.z
				);
				D3DXMatrixMultiply
				(
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&mtxRot
				);
				// 位置を反映
				D3DXMatrixTranslation
				(
					&mtxTrans,
					g_Player.aModel[nCntParts].posModel.x,
					g_Player.aModel[nCntParts].posModel.y,
					g_Player.aModel[nCntParts].posModel.z
				);
				D3DXMatrixMultiply
				(
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&mtxTrans
				);

				D3DXMatrixMultiply
				(
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&mtxParent
				);
				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorldModel);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMatModel->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMatModel; nCntMat++)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャをNULLにする
					pDevice->SetTexture(0, NULL);

					//pDevice->SetTexture(0, g_Player.nNumMatPlayer);

					// プレイヤー(パーツ)の描画
					g_Player.aModel[nCntParts].pMeshModel->DrawSubset(nCntMat);
				}
				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=============================================================================
// プレイヤーのダメージ状態
//=============================================================================
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;
	SetLife(g_Player.nLife);

	if (g_Player.nLife <= 0)
	{	//ライフが0になったら
		SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_Player.state = PLAYERSTATE_DEATH;
		g_Player.nCntState = 5;
		SetGameState(GAMESTATE_OVER);
	}
	else
	{	//ライフが残ってたら
		g_Player.state = PLAYERSTATE_DAMADE;
		g_Player.nCntState = DAMAGE_STATE;					//ダメージ状態の時間
		g_Player.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
}

//=========================================================================================================================
// プレイヤーの取得処理
//=========================================================================================================================
Player * GetPlayer(void)
{
	return &g_Player;
}
