//===============================================================================
//
// プレイヤー生成の処理 [player.cpp]
// Author : 箱﨑彩花
//
//===============================================================================
#include "main.h"
#include"player.h"
#include "input.h"
#include "block.h"
#include "item.h"
#include "game.h"
#include"sound.h"

//===============================================================================
//マクロ定義
//===============================================================================
#define PLAYER_TEXTURE "data/TEXTURE/player002.png"				//使用するテクスチャ
#define PLAYER_POS_X							(200)													//背景の左上X座標
#define PLAYER_POS_Y							(500)													//背景の左上Y座標
#define PLAYER_SPEED							(0.5f)													//プレイヤーのスピード
#define PATTERN									(4)														//パターン数
#define JUMP											(20)													//ジャンプの高さ
#define GRAVITY										(1.0)														//重力
#define PLAYER_WIDTH							(30)														//プレイヤーの幅
#define PLAYER_HEIGHT						(70)														//プレイヤーの高さ
#define GROUND									(800)													//地面

//===============================================================================
//グローバル変数宣言
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;					//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//頂点バッファへのポインタ
Player g_player;
int g_nNumPlayer;

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

	//構造体の初期化
	g_player.pos = D3DXVECTOR3(640, 100, 0.0f);		//ポリゴンの位置
	g_player.posOld = D3DXVECTOR3(0, 0, 0.0f);
	g_player.move = D3DXVECTOR3(0, 0, 0.0f);			//ポリゴンの移動量
	g_player.bDisp = true;
	g_player.bJump = true;
	g_player.bUse = true;
	g_player.nPatternAnim = 0;
	g_player.nCntAnim = 0;
	g_player.DirectionMove = 0;
	g_player.nWidth = PLAYER_WIDTH;
	g_player.nHeight = PLAYER_HEIGHT;
	g_player.state = PLAYERSTATE_NORMAL;

	g_nNumPlayer = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURE, &g_pTexturePlayer);

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
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT,0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

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

	//前回の位置を保存
	g_player.posOld = g_player.pos;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
		case PLAYERSTATE_NORMAL:
			//ポリゴンの座標設定
			pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y, 0.0f);
			break;

		case PLAYERSTATE_SIZEUP:
			//ポリゴンの座標設定
			pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH * 1.5f, g_player.pos.y - PLAYER_HEIGHT * 1.5f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH * 1.5f, g_player.pos.y - PLAYER_HEIGHT * 1.5f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH * 1.5f, g_player.pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH * 1.5f, g_player.pos.y, 0.0f);
			break;

		case PLAYERSTATE_SIZEDOWN:
			//ポリゴンの座標設定
			pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y - PLAYER_HEIGHT / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH / 2, g_player.pos.y, 0.0f);
			break;
	}

	if (GetKeyboardPress(DIK_A) == true)
	{	//任意のキー（Aキー）が押されたとき、左
		g_player.move.x += sinf(D3DX_PI * -0.5f) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI * -0.5f) * PLAYER_SPEED;
		g_player.DirectionMove = 1;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{	//任意のキー（Dキー）が押されたとき、右
		g_player.move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		g_player.DirectionMove = 0;
	}

	//	移動のアニメーション
	if (g_player.bJump == true)
	{
		if (g_player.nPatternAnim % 1 == 0)
		{
			g_player.nCntAnim++;
			if ((g_player.nCntAnim % 7) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PATTERN;
			}
		}
	}
	else if (g_player.move.x > 1 || g_player.move.x < -1)
	{	//キー押してないとき止まる
		g_player.nCntAnim++;
		if ((g_player.nCntAnim % 7) == 0)
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PATTERN;
		}
	}
	else
	{
		if (g_player.nPatternAnim == 0 || g_player.nPatternAnim == 2)
		{	//止まったら足戻す
			g_player.nCntAnim++;
			if ((g_player.nCntAnim % 7) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PATTERN;
			}
		}
	}

	if (g_player.bJump == false)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{	//任意のキー（SPACEキー）が押されたとき、上
			g_player.move.y = -JUMP;		//ジャンプ力
			g_player.bJump = true;
			PlaySound(SOUND_LABEL_SE_JUMP);
		}
	}

	////地面の処理
	//if (g_player.pos.y >= SCREEN_HEIGHT)
	//{
	//	g_player.bJump = false;
	//	g_player.pos.y = SCREEN_HEIGHT;
	//	g_player.move.y = 0.0f;
	//}

	//重力加算
	g_player.move.y += GRAVITY;

	g_player.pos.x += g_player.move.x;	//横移動
	g_player.pos.y += g_player.move.y;	//落下

	//画面外に出た時
	if (g_player.pos.x < 10)
	{ //右側に出たら
		g_player.pos.x = SCREEN_WIDTH + 10;
	}
	if (g_player.pos.x > SCREEN_WIDTH + 10)
	{ //左側に出たら
		g_player.pos.x = 10;
	}

	//位置情報の更新
	g_player.pos.x += g_player.move.x;

	//減速のスピード
	g_player.move.x += (0.0f - g_player.move.x) * 0.2f;
	//g_player.move.y += (0.0f - g_player.move.y) * 0.2f;

	//ブロックとの当たり判定
	if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, PLAYER_WIDTH, PLAYER_HEIGHT) == true)
	{	//プレイヤー通常状態
		g_player.bJump = false;
	}
	else
	{
		if (g_player.bJump == false)
		{
			g_player.bJump = true;
		}
	}

	//アイテムの当たり判定
	CollisionItem(0);
	CollisionItem(1);
	CollisionItem(2);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f * (g_player.nPatternAnim + 1), 0.5f * g_player.DirectionMove);
	pVtx[1].tex = D3DXVECTOR2(0.25f + 0.25f * (g_player.nPatternAnim + 1), 0.5f * g_player.DirectionMove);
	pVtx[2].tex = D3DXVECTOR2(0.0f + 0.25f * (g_player.nPatternAnim + 1), 0.5f * g_player.DirectionMove + 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f * (g_player.nPatternAnim + 1), 0.5f * g_player.DirectionMove + 0.5f);

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
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//===============================================================================
//プレイヤーを取得
//===============================================================================
Player * GetPlayer(void)
{
	return &g_player;
}