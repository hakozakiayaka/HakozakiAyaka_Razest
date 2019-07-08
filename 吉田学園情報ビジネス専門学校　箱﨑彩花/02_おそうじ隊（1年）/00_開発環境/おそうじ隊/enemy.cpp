//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "enemy.h"
#include "shadow.h"
#include "fade.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "model.h"
#include "sound.h"			//サウンド

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_TEX	 "data/TEXTURE/enemy.png"				//テクスチャの読み込み
#define ENEMY_TEX1 "data/TEXTURE/enemy1.png"			//テクスチャの読み込み

#define MAX_TEX						(2)										//テクスチャの最大数
#define ENEMY_SIZE					(20.0f)									//エネミーのサイズ
#define BULLET_SPEED			(1.0f)									//弾のスピード

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;	//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureEnemy[MAX_TEX] = {};				//テクスチャへのポインタ
Enemy g_Enemy[MAX_ENEMY];
int g_nNumEnemy;
int g_nPosZ = rand() % 600;

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_Enemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].nCntAnim = 0;
		g_Enemy[nCntEnemy].nPatternAnim = 0;
		g_Enemy[nCntEnemy].bUse = false;
	}
	g_nNumEnemy = 0;		//ビルボードの枚数を初期化

	// 頂点情報の作成
	MakeVertexEnemy(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	//テクスチャの開放
	for (int nCntEnemy = 0; nCntEnemy < MAX_TEX; nCntEnemy++)
	{
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();
			g_pTextureEnemy[nCntEnemy] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	VERTEX_3D * pVtx;								//頂点情報のポインタ
	FADE g_fade = GetFade();					//フェードを取得
	Player * pPlayer = GetPlayer();			//プレイヤーを取得
	float fMoveX = 0;								//角度を求めるX
	float fMoveZ = 0;								//角度を求めるZ
	float fMoveX2 = 0;								//Xの移動量
	float fMoveZ2 = 0;								//Zの移動量
	float fAngle = 0;									//角度を求める

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//敵が弾発射
			if ((rand() % 100 == 0))		//数字が大きいほど、弾の数が減る
			{
				//敵の弾がプレイヤーに向かって撃ってくる
				fMoveX = pPlayer->pos.x - g_Enemy[nCntEnemy].pos.x;		//角度のXを求める
				fMoveZ = pPlayer->pos.z - g_Enemy[nCntEnemy].pos.z;		//角度のYを求める
				fAngle = atan2f(fMoveX, fMoveZ);											//角度求める

				fMoveX2 = sinf(fAngle) * BULLET_SPEED;
				fMoveZ2 = cosf(fAngle) * BULLET_SPEED;

				PlaySound(SOUND_LABEL_SE_SHOT000);
				SetBullet(g_Enemy[nCntEnemy].pos, D3DXVECTOR3(fMoveX2, 0.0f, fMoveZ2), BULLETTYPE_ENEMY);
			}

			if (g_Enemy[nCntEnemy].pos.x + 20 > pPlayer->pos.x
				&& g_Enemy[nCntEnemy].pos.x - 20 < pPlayer->pos.x
				&& g_Enemy[nCntEnemy].pos.z + 20 > pPlayer->pos.z
				&& g_Enemy[nCntEnemy].pos.z - 20 < pPlayer->pos.z)
			{	//当たり判定（敵がプレイヤーに当たった時の処理）
				AddScore(2000);
				PlaySound(SOUND_LABEL_SE_HIT000);
				SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y + 10, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
				DeleteEnemy(nCntEnemy);
				g_nPosZ = rand() % 600;
				SetEnemy(D3DXVECTOR3(rand() % 600, g_Enemy[nCntEnemy].pos.y, -g_nPosZ), g_Enemy[nCntEnemy].rot, rand() % 2);
			}

			//敵のアニメーション
			g_Enemy[nCntEnemy].nCntAnim++;
			if ((g_Enemy[nCntEnemy].nCntAnim % 10) == 0)
			{
				g_Enemy[nCntEnemy].nPatternAnim = (g_Enemy[nCntEnemy].nPatternAnim + 1) % 2;
			}

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2((g_Enemy[nCntEnemy].nPatternAnim * 0.5f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_Enemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_Enemy[nCntEnemy].nPatternAnim * 0.5f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_Enemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, 1.0f);

			//影の位置設定
			SetPositionShadow(g_Enemy[nCntEnemy].nIdxEnemyShadow, g_Enemy[nCntEnemy].pos);
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			//計算用マトリックス
	int nCntEnemy;

	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorldEnemy);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//逆行列の設定
			g_Enemy[nCntEnemy].mtxWorldEnemy._11 = mtxView._11;
			g_Enemy[nCntEnemy].mtxWorldEnemy._12 = mtxView._21;
			g_Enemy[nCntEnemy].mtxWorldEnemy._13 = mtxView._31;
			g_Enemy[nCntEnemy].mtxWorldEnemy._21 = mtxView._12;
			g_Enemy[nCntEnemy].mtxWorldEnemy._22 = mtxView._22;
			g_Enemy[nCntEnemy].mtxWorldEnemy._23 = mtxView._32;
			g_Enemy[nCntEnemy].mtxWorldEnemy._31 = mtxView._13;
			g_Enemy[nCntEnemy].mtxWorldEnemy._32 = mtxView._23;
			g_Enemy[nCntEnemy].mtxWorldEnemy._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntEnemy].mtxWorldEnemy, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorldEnemy);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEnemy[g_Enemy[nCntEnemy].nTexType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}

	//レンダーステートの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ
	int nCntEnemy;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX, &g_pTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX1, &g_pTextureEnemy[1]);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE, ENEMY_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(ENEMY_SIZE, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// 敵の設定
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTexType)
{
	//モデルの取得
	Model * pModel = GetModel();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == false)
		{
			g_Enemy[nCntEnemy].pos = pos;
			if (pModel->pos.x + pModel->vtxMaxModel.x >= g_Enemy[nCntEnemy].pos.x 
				&& pModel->pos.x + pModel->vtxMinModel.x <= g_Enemy[nCntEnemy].pos.x
				&& pModel->pos.z + pModel->vtxMaxModel.z >= g_Enemy[nCntEnemy].pos.z
				&& pModel->pos.z + pModel->vtxMinModel.z <= g_Enemy[nCntEnemy].pos.z)
			{
				SetEnemy(D3DXVECTOR3(rand() % 600, g_Enemy[nCntEnemy].pos.y, -g_nPosZ), g_Enemy[nCntEnemy].rot, rand() % 2);
				break;
			}
			g_Enemy[nCntEnemy].rot = rot;
			g_Enemy[nCntEnemy].nTexType = nTexType;
			g_Enemy[nCntEnemy].bUse = true;

			g_nNumEnemy++;		//敵の総数を加算する

			//影の初期設定
			g_Enemy[nCntEnemy].nIdxEnemyShadow = SetShadow(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].rot, 10.0f, 10.0f);
			break;
		}
	}
}

//=============================================================================
// 敵の取得
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_Enemy[0];
}

//=============================================================================
// エネミーを消す処理
//=============================================================================
void DeleteEnemy(int nCntEnemy)
{
	g_nNumEnemy--;
	DeleteShadow(g_Enemy[nCntEnemy].nIdxEnemyShadow);
	g_Enemy[nCntEnemy].bUse = false;
}