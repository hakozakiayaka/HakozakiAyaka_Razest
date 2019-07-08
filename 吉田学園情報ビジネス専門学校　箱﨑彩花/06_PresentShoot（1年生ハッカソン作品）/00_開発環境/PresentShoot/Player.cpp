//=============================================================================
//
// プレーヤー処理 [player.cpp]
// Author : 佐藤安純　Sato_Asumi
//
//=============================================================================
#include "player.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "game.h"
#include "present.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURENAME		"data\\TEXTURE\\santa.png"		//読みこむテクスチャの名前
#define PLAYER_SPEED	(1.0f)							//プレイヤーのスピード
#define PLAYER_ANIM		(20.0f)

//=============================================================================
// グローバル変数
//=============================================================================
VERTEX_2D				g_aVertex[4];				//頂点情報を格納する
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
Player					g_player;					//プレイヤーのポインタ
int						g_nCntEffect;					//時間のカウンター

//=============================================================================
//	頂点情報の設定
//=============================================================================
void InitPlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//初期化処理
	g_player.nCounterAnim = 0;							//カウンターを初期化する
	g_player.nPatternAnim = 0;							//パターンNo.を初期化する
	g_player.nLife = PLAYER_LIFE;						//プレイヤーのライフ
	g_player.pos = D3DXVECTOR3(100.0f, 200.0f, 0.0f);	//初期位置
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
	g_player.posMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期値
	g_player.nDirectionMove = 0;
	g_player.bDisp = true;
	g_nCntEffect = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
								TEXTURENAME,
								&g_pTexturePlayer);

	//頂点バッファの生成
	pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D)*4,
								  D3DUSAGE_WRITEONLY,
								  FVF_VERTEX_2D,
								  D3DPOOL_MANAGED,
								  &g_pVtxBuffPlayer,
								  NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//========================================================================================
//終了処理
//========================================================================================
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//========================================================================================
//更新処理
//========================================================================================
void UpdatePlayer(void)
{
	//変数宣言
	g_player.nCounterAnim++;

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	if (g_player.bDisp == true)
	{
		//前回の位置を保存
		g_player.posOld = g_player.pos;

		//時間を加算する
		g_nCntEffect++;

		//エフェクト
		SetEffect(g_player.pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 2.0f, 1);

		switch (g_player.state)
		{
		case PLAYERSTATE_APPEAR:
			g_player.nCntstate--;
			if (g_player.nCntstate <= 0)
			{
				g_player.state = PLAYERSTATE_NOMAL;

			}
			break;

		case PLAYERSTATE_NOMAL:

			break;

		case PLAYERSTATE_DAMAGE:
			g_player.nCntstate--;
			if (g_player.nCntstate <= 0)
			{
				g_player.state = PLAYERSTATE_APPEAR;
				//頂点をロックして頂点データへのポインタを取得
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

																//頂点バッファのアンロック
				g_pVtxBuffPlayer->Unlock();
			}

			break;

		case PLAYERSTATE_DEATH:
			if (g_player.nCntstate <= 0)
			{
				g_player.posMove.y += 0.3f;
				g_player.pos.y += g_player.posMove.y;

				g_player.state = PLAYERSTATE_APPEAR;
				//頂点をロックして頂点データへのポインタを取得
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y, 0.0f);

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//一つ目の頂点の色指定（右回り）
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//二つ目の頂点の色指定（右回り）
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//三つ目の頂点の色指定（右回り）

																//頂点バッファのアンロック
				g_pVtxBuffPlayer->Unlock();
			}
			break;
		}

		//アニメーションの処理
		if ((g_player.nCounterAnim % 30) == 0)
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}

		//移動処理
		if (GetKeyboardPress(DIK_D) == true)
		{//右に進む
			g_player.nDirectionMove = 0;

			g_player.move.x += sinf(D3DX_PI * 0.5) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.5) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{//左に進む
			g_player.nDirectionMove = 1;

			g_player.move.x += sinf(D3DX_PI * -0.5) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * -0.5) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//下に進む
			g_player.move.x += sinf(0.0f) * PLAYER_SPEED;
			g_player.move.y += cosf(0.0f) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//上に進む
			g_player.move.x += sinf(D3DX_PI) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI) * PLAYER_SPEED;
		}

		//プレゼントを落とす
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetPresent(rand() % 4, g_player.pos);
		}

		//移動範囲処理
		if (g_player.pos.x + POSCENTER_X > SCREEN_WIDTH)
		{
			g_player.pos.x = SCREEN_WIDTH - POSCENTER_X;
		}
		else if (g_player.pos.x - POSCENTER_X < 0.0f)
		{
			g_player.pos.x = 0.0f + POSCENTER_X;
		}

		if (g_player.pos.y - POSCENTER_Y < 0.0f)
		{
			g_player.pos.y = 0.0f + POSCENTER_Y;
		}
		else if (g_player.pos.y + POSCENTER_Y > 400)
		{
			g_player.pos.y = 400 - POSCENTER_Y;
		}

		//位置更新
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		//減速
		g_player.move.x += (0.0f - g_player.move.x) * 0.2f;
		g_player.move.y += (0.0f - g_player.move.y) * 0.2f;

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y, 0.0f);

		//テクスチャ座標の設定
		if (g_player.nDirectionMove == 0)
		{//右向きの時
			pVtx[1].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[0].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 1.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 1.0f);
		}
		if (g_player.nDirectionMove == 1)
		{//左に向いているとき
			pVtx[0].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 1.0f);
		}
	
		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();
	}
}

//========================================================================================
//描画処理
//========================================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

		//デバイスの取得
		pDevice = GetDevice();

		//頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		if (g_player.bDisp == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
}

//========================================================================================
//プレイヤーの情報
//========================================================================================
Player *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// プレイヤーのダメージ処理
//=============================================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;
	SetLife(g_player.nLife);

	VERTEX_2D *pVtx;// 頂点情報の作成
					//頂点バッファをロック
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.nLife <= 0)
	{
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCntstate = 60;
		g_player.bDisp = false;
		SetGameState(GAMESTATE_END_OVER);

	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;

		g_player.nCntstate = 5;

		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//一つ目の頂点の色指定（右回り）
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//二つ目の頂点の色指定（右回り）
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//三つ目の頂点の色指定（右回り）
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

}