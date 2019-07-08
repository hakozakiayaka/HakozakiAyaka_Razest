//=============================================================================
//
// モデル処理 [player.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _PLAYERL_H_
#define _PLAYERL_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_LIFE				(5)									//ライフ

//===============================================================================
//構造体の定義
//===============================================================================
typedef enum
{
	PLAYERSATATE_APPEAR = 0,	//出現状態
	PLAYERSTATE_NORMAL,			//通常状態
	PLAYERSTATE_DAMADE,			//ダメージ状態
	PLAYERSTATE_DEATH,				//死亡状態
	PLAYERSTATE_MAX					//プレイヤーの種類の総数
} PLAYERSATATE;

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMeshModel = NULL;			//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatModel = NULL;	//マテリアルの情報へのポインタ
	DWORD nNumMatModel = 0;						//マテリアルの情報数
	D3DXMATRIX mtxWorldModel;						//ワールドマトリックス
	D3DXVECTOR3 posModel;								//位置
	D3DXVECTOR3 rotModel;								//向き
	int nIdxModelParent = 0;								//親モデルのインデックス　-1が親
} Model2;

typedef struct
{
	D3DXMATRIX mtxWorldPlayer;							//ワールドマトリックス
	LPD3DXMESH pMeshPlayer = NULL;				//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatPlayer = NULL;		//マテリアルの情報へのポインタ
	DWORD nNumMatPlayer = 0;							//マテリアルの情報数
	D3DXVECTOR3 posOld;										//過去の位置
	D3DXVECTOR3 pos;											//位置
	D3DXVECTOR3 move;											//移動
	D3DXVECTOR3 rot;												//向き
	Model2 aModel[13];											//[〇]ここにはパーツ数が入る
	D3DXVECTOR3 vtxMaxPlayer;							//プレイヤーのパーツの最大数
	D3DXVECTOR3 vtxMinPlayer;							//プレイヤーのパーツの最小値
	PLAYERSATATE state;										//プレイヤーのステート
	D3DXCOLOR col;													//カラー
	int nLife;																//プレイヤーのライフ
	int nCntState;														//状態管理のカウンター
	bool bDisp;															//表示するかしないか
}Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);					//プレイヤーの当たり判定処理
Player *GetPlayer(void);

#endif