//===============================================================================
//
// プレイヤー生成の処理 [player.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include"player.h"
#include"input.h"
#include"bullet.h"
#include "explosion.h"
#include "game.h"
#include "sound.h"
#include "life.h"

//===============================================================================
//マクロ定義
//===============================================================================
#define PLAYER_TEXTURE_NAME "data/TEXTURE/player001.png"				//使用するテクスチャ
#define PLAYER_POS_X							(200)													//背景の左上X座標
#define PLAYER_POS_Y							(500)													//背景の左上Y座標
#define PLAYER_SPEED							(3.0f)													//プレイヤーのスピード
#define PLAYER_TEX_PATTAERN			(10)														//プレイヤーのパターン数
#define DAMAGE_STATE						(7)														//ダメージ状態	
#define PLAYER_LIFE								(3)														//	プレイヤーのライフ

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;					//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//頂点バッファへのポインタ
int g_nCounterAnim;																	//アニメーションカウンター
int g_nPatternAnim;																	//アニメーションNo.
Player g_player;

//===============================================================================
//プレイヤー生成初期化処理
//===============================================================================
void InitPlayer(void)
{
	//変数宣言
	VERTEX_2D * pVtx;							//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスを取得
	pDevice = GetDevice();

	g_nCounterAnim = 0;	//カウンターを初期化する
	g_nPatternAnim = 0;	//パターンNo.を初期化する

	g_player.pos = D3DXVECTOR3(640, 695, 0.0f);		//ポリゴンの位置
	g_player.move = D3DXVECTOR3(0,0,0.0f);																	//ポリゴンの移動量
	g_player.bDisp = true;
	g_player.nCounterState = 0;
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nLife = PLAYER_LIFE;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE_NAME, &g_pTexturePlayer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの座標設定
	pVtx[0].pos = D3DXVECTOR3(610.0f, 665.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(660.0f, 665.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(610.0f, 715.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(660.0f, 715.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//ポリゴンの色設定
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//===============================================================================
//プレイヤー生成終了処理
//===============================================================================
void UninitPlayer(void)
{
	//テクスチャの開放
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//===============================================================================
//プレイヤー生成更新処理
//===============================================================================
void UpdatePlayer(void)
{
	//変数宣言
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMADE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			//頂点バッファをロックし、頂点データへのポインタを取得
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//ポリゴンの色設定
			pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
			pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

			//頂点バッファをアンロックする
			g_pVtxBuffPlayer->Unlock();

			g_player.state = PLAYERSTATE_NORMAL;
		}
		break;

	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		
		return;
		break;
	}

	//g_nCounterAnim++;		
	
	//カウンター加算
	//if ((g_nCounterAnim % 5) == 0)
	//{	//ポリゴンの速さ
	//	g_nPatternAnim = (g_nPatternAnim + 1) % PLAYER_TEX_PATTAERN;		//パターンNo.更新
	//}

	//位置の更新
	/*g_posPolygon += g_movePolygon;
	g_posPolygon -= g_movePolygon;*/

	if (GetKeyboardPress(DIK_A) == true)
	{	//任意のキー（Aキー）が押されたとき、左
		g_player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_SPEED;

		if (GetKeyboardPress(DIK_W) == true)
		{	//左上移動
			g_player.move.x += sinf(D3DX_PI * -0.75f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * -0.75f) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{	//左下移動
			g_player.move.x += sinf(D3DX_PI * -0.25f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * -0.25f) * PLAYER_SPEED;
		}
		else
		{	//左移動
			g_player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{	//任意のキー（Dキー）が押されたとき、右
		g_player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;

		if (GetKeyboardPress(DIK_W) == true)
		{	//右上移動
			g_player.move.x += sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.75f) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{	//右下移動
			g_player.move.x += sinf(D3DX_PI * 0.25f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;
		}
		else
		{	//右移動
			g_player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{	//任意のキー（Wキー）が押されたとき、上
		g_player.move.x += sinf(D3DX_PI) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI) * PLAYER_SPEED;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{	//任意のキー（Sキー）が押されたとき、下
		g_player.move.x += sinf(0.0f) * PLAYER_SPEED;
		g_player.move.y += cosf(0.0f) * PLAYER_SPEED;
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{	//任意のキー（SPACEキー）が押されたとき、上
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(D3DX_PI) * PLAYER_SPEED, cosf(D3DX_PI) * 10.0f, 0.0f),BULLETTYPE_PLAYER);	//直線
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(2.0f) * PLAYER_SPEED, cosf(2.0f) * 20.0f, 0.0f), BULLETTYPE_PLAYER);					//右上
		SetBullet(g_player.pos, D3DXVECTOR3(sinf(- 2.0f) * PLAYER_SPEED, cosf(- 2.0f) * 20.0f, 0.0f), BULLETTYPE_PLAYER);				//左上
		//PlaySound(SOUND_LABEL_SE_SHOT);
	}

	//位置情報の更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//移動範囲の判定
	if (g_player.pos.x <= 20)
	{
		g_player.pos.x = 20;
	}
	else if (g_player.pos.x + 20 > SCREEN_WIDTH)
	{
		g_player.pos.x = SCREEN_WIDTH - 20;
	}

	if (g_player.pos.y <= 20)
	{
		g_player.pos.y = 20;
	}
	else if (g_player.pos.y + 20 > SCREEN_HEIGHT)
	{
		g_player.pos.y = SCREEN_HEIGHT - 20;
	}

	//減速のスピード
	g_player.move.x += (0.0f - g_player.move.x) * 0.3f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.3f;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの座標設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 20, g_player.pos.y - 20, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 20, g_player.pos.y - 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 20, g_player.pos.y + 20, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 20, g_player.pos.y + 20, 0.0f);

	//ダメ―ジの色設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの座標設定
	//pVtx[0].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f, 0.5f * (g_nPatternAnim / 5));
	//pVtx[1].tex = D3DXVECTOR2((g_nPatternAnim % 5)* 0.2f + 0.2f, 0.5f * (g_nPatternAnim / 5));
	//pVtx[2].tex = D3DXVECTOR2((g_nPatternAnim % 5)* 0.2f, 0.5f * (g_nPatternAnim / 5) + 0.5f);
	//pVtx[3].tex = D3DXVECTOR2((g_nPatternAnim % 5) * 0.2f + 0.2f, 0.5f * (g_nPatternAnim / 5) + 0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//===============================================================================
//プレイヤー生成描画処理
//===============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスを取得する
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//頂点バッファをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice ->SetFVF(FVF_VERTEX_2D);	

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);
	
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
}

//=============================================================================
// プレイヤーのダメージ状態
//=============================================================================
void HitPlayer(int nDamage)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	g_player.nLife -= nDamage;
	SetLife(g_player.nLife);

	if (g_player.nLife <= 0)
	{	//ライフが0になったら
		SetExplosion(g_player.pos, D3DXCOLOR(0.5f, 0.4f, 0.9f, 1.0f));
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCounterState = 5;
		SetGameState(GAMESTATE_OVER);
	}
	else
	{	//ライフが残ってたら
		g_player.state = PLAYERSTATE_DAMADE;
		g_player.nCounterState = DAMAGE_STATE;		//ダメージ状態の時間

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//ダメ―ジの色設定
			pVtx[0].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();
	}
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}