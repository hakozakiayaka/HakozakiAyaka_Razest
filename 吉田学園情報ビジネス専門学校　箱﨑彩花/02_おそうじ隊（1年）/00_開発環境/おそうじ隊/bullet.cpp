//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "bullet.h"
#include "shadow.h"
#include "explosion.h"
#include "meshField.h"
#include "effect.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_TEX "data/TEXTURE/bullet002.png"		//テクスチャの読み込み
#define MAX_BULLET			(300)										//弾の最大数
#define BULLET_SIZE				(10.0f)										//弾の大きさ
#define POLYGON_RANGE		(20.0f)										//ポリゴンの大きさ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;				//テクスチャへのポインタ
Bullet g_aBullet[MAX_BULLET];

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].vecA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].vecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}

	// 頂点情報の作成
	MakeVertexBullet(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	//テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	//メッシュフィールドの取得
	MESHFIELD * pMeshField = GetMeshField();
	Player * pPlayer = GetPlayer();
	D3DXVECTOR3 aPos[4];										//外積（フィールドのpos）
	float fAnswer;														//ベクトルの計算結果

	//フィールドの位置
	aPos[0] = D3DXVECTOR3(-105.0f, 0.0f, 105.0f);
	aPos[1] = D3DXVECTOR3(895.0f, 0.0f, 105.0f);
	aPos[2] = D3DXVECTOR3(895.0f, 0.0f, -895.0f);
	aPos[3] = D3DXVECTOR3(-105.0f, 0.0f, -895.0f);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;

			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{	//敵の弾
				if (pPlayer->state == PLAYERSTATE_NORMAL)
				{
					if (g_aBullet[nCntBullet].pos.x + POLYGON_RANGE > pPlayer->pos.x
						&& g_aBullet[nCntBullet].pos.x - POLYGON_RANGE < pPlayer->pos.x
						&& g_aBullet[nCntBullet].pos.z + POLYGON_RANGE > pPlayer->pos.z
						&& g_aBullet[nCntBullet].pos.z - POLYGON_RANGE < pPlayer->pos.z)
					{	//当たり判定
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE_HIT000);
						DeleteShadow(g_aBullet[nCntBullet].nIdxBulletShadow);
						g_aBullet[nCntBullet].bUse = false;																		//使用していない状態にする
					}
				}
			}

			for (int nCnt = 0; nCnt < 4; nCnt++)
			{	//右以外の判定
				g_aBullet[nCntBullet].vecA = aPos[nCnt] - aPos[nCnt + 1];
				g_aBullet[nCntBullet].vecC = g_aBullet[nCntBullet].pos - aPos[nCnt];

				//影の位置設定
				SetPositionShadow(g_aBullet[nCntBullet].nIdxBulletShadow, g_aBullet[nCntBullet].pos);

				if (nCnt == 4 - 1)
				{	//右の判定
					g_aBullet[nCntBullet].vecA = aPos[nCnt] - aPos[0];
				}

				fAnswer = ((g_aBullet[nCntBullet].vecA.z * g_aBullet[nCntBullet].vecC.x) - (g_aBullet[nCntBullet].vecA.x * g_aBullet[nCntBullet].vecC.z));

				if (fAnswer >= 0)
				{
					SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.3f, 0.5f, 1.0f));		//爆発の設定
					g_aBullet[nCntBullet].bUse = false;
					DeleteShadow(g_aBullet[nCntBullet].nIdxBulletShadow);
				}
			}

#if 0
			//奥の判定------------------------------------------------------------------------------------------------------------------------------------------------
			g_aBullet[nCntBullet].vecA = aPos[0] - aPos[1];
			g_aBullet[nCntBullet].vecC = g_aBullet[nCntBullet].pos - aPos[0];

			fAnswer0 = ((g_aBullet[nCntBullet].vecA.z * g_aBullet[nCntBullet].vecC.x) - (g_aBullet[nCntBullet].vecA.x * g_aBullet[nCntBullet].vecC.z));

			if (fAnswer0 >= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//爆発の設定
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxBulletShadow);
			}

			//左の判定-------------------------------------------------------------------------------------------------------------------------------------------------
			g_aBullet[nCntBullet].vecA = aPos[1] - aPos[2];
			g_aBullet[nCntBullet].vecC = g_aBullet[nCntBullet].pos - aPos[1];

			fAnswer1 = ((g_aBullet[nCntBullet].vecA.z * g_aBullet[nCntBullet].vecC.x) - (g_aBullet[nCntBullet].vecA.x * g_aBullet[nCntBullet].vecC.z));

			if (fAnswer1 >= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//爆発の設定
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxBulletShadow);
			}

			//右の判定--------------------------------------------------------------------------------------------------------------------------------------------------
			//g_aBullet[nCntBullet].vecA = aPos[3] - aPos[0];
			//g_aBullet[nCntBullet].vecC = g_aBullet[nCntBullet].pos - aPos[3];

			//if (g_aBullet[nCntBullet].pos.x > 895.0f
			//	|| g_aBullet[nCntBullet].pos.x < -105.0f
			//	|| g_aBullet[nCntBullet].pos.z > 105.0f
			//	|| g_aBullet[nCntBullet].pos.z < -895.0f)
			//{	//当たり判定
			//	SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.7f, 0.2f, 0.8f, 1.0f));		//爆発の設定
			//	DeleteShadow(g_aBullet[nCntBullet].nIdxBulletShadow);
			//	g_aBullet[nCntBullet].bUse = false;	//使用していない状態にする
			//}
#endif
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			//計算用マトリックス
	int nCntBullet;

	//レンダーステートの設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorldBullet);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//逆行列の設定
			g_aBullet[nCntBullet].mtxWorldBullet._11 = mtxView._11;
			g_aBullet[nCntBullet].mtxWorldBullet._12 = mtxView._21;
			g_aBullet[nCntBullet].mtxWorldBullet._13 = mtxView._31;
			g_aBullet[nCntBullet].mtxWorldBullet._21 = mtxView._12;
			g_aBullet[nCntBullet].mtxWorldBullet._22 = mtxView._22;
			g_aBullet[nCntBullet].mtxWorldBullet._23 = mtxView._32;
			g_aBullet[nCntBullet].mtxWorldBullet._31 = mtxView._13;
			g_aBullet[nCntBullet].mtxWorldBullet._32 = mtxView._23;
			g_aBullet[nCntBullet].mtxWorldBullet._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorldBullet, &g_aBullet[nCntBullet].mtxWorldBullet, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorldBullet);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//レンダーステートの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//頂点情報のポインタ
	int nCntBullet;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, BULLET_TEX, &g_pTextureBullet);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//弾の色設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// 弾の設定
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].bUse = true;

			//影の初期設定
			g_aBullet[nCntBullet].nIdxBulletShadow = SetShadow(g_aBullet[g_aBullet[nCntBullet].nIdxBulletShadow].pos, g_aBullet[g_aBullet[nCntBullet].nIdxBulletShadow].move, 10.0f, 10.0f);

			break;
		}
	}
}