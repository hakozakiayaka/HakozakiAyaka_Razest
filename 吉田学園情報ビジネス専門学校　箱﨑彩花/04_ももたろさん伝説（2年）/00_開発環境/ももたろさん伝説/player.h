//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _PLAYER_H_		//二重インクルード防止
#define _PLAYER_H_

#include	"main.h"			//メイン

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBullet;				//弾

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE									(80)														//ポリゴンの中心点からのサイズ
#define PLAYER_SPEED					(1.0f)													//プレイヤーのスピード
#define PLAYER_FIELD_RANGE		(500.0f)												//地面の範囲
#define GRAVITY								(0.5)														//重力加算
#define PLAYER_JUMP					(10)														//ジャンプ
#define PLAYER_INERTIA_SPEED	(0.2f)													//慣性のスピード

//テクスチャ名
#define PLAYER_NAME		"data/TEXTURE/momotarou.png"		//（プレイヤー）

//*****************************************************************************
// プレイヤークラス
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	CPlayer(int nPriority = 4);														//コンストラクタ
	~CPlayer();																				//デストラクタ
	HRESULT Init();																		//初期化処理
	void Uninit(void);																		//終了処理
	void Update(void);																	//更新処理
	void Draw(void);																		//描画処理

	//静的メンバ関数
	static CPlayer * Create(D3DXVECTOR3 pos);						//プレイヤーの生成
	static HRESULT Load(void);													//テクスチャを読み込む処理
	static void Unload(void);															//テクスチャを破棄する処理

private:
	bool												m_bJump;							//ジャンプしているかしていないか
	D3DXVECTOR3							m_pos;									//位置
	D3DXVECTOR3							m_move;								//移動量

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture;							//共有テクスチャへのポインタ
};
#endif