//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _ENEMY_H_	//二重インクルード防止
#define _ENEMY_H_

#include	"main.h"		//メイン
#include "bullet.h"		//弾

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_TEXTURE				(3)												//テクスチャの最大数
#define SIZE									(80)												//ポリゴンの中心点からのサイズ
#define ENEMY_LIFE						(2)												//敵のライフ設定
#define DAMAGE_STATE				(5)												//ダメージ受けた時の光る時間
#define ENEMY_FIELD_RANGE		(500.0f)										//地面の範囲
#define ENEMY_GRAVITY				(0.5)												//重力加算
#define ENEMY_JUMP					(7)												//ジャンプ
#define ENEMY_SPEED					(0.05f)											//スピード

//テクスチャ名
#define ENEMY_NAME				"data/TEXTURE/akaoni.png"				//（あかおに）
#define ENEMY_NAME1				"data/TEXTURE/aooni.png"				//（あおおに）
#define ENEMY_NAME2				"data/TEXTURE/kioni.png"					//（きいろおに）

//*****************************************************************************
// 敵クラス
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	typedef enum
	{	//敵の状態の種類
		ENEMYSTATE_NONE = 0,																		//通常状態
		ENEMYSTATE_DAMAGE,																		//ダメージ状態
		ENEMYSTATE_DEATH,																			//死んだ状態
		ENEMYSTATE_MAX																				//状態の種類の数
	} ENEMYSTATE;

	typedef enum
	{	//鬼のタイプ分け
		ENEMYTYPE_RED,																					//あかおに
		ENEMYTYPE_BLUE,																				//あおおに
		ENEMYTYPE_YELLOW,																			//きいろおに
		ENEMYTYPE_BOSS,																				//ボス
		ENEMYTYPE_MAX																					//鬼のタイプの最大数
	} ENEMYTYPE;

	CEnemy();																									//コンストラクタ
	~CEnemy();																									//デストラクタ
	HRESULT Init();																							//初期化処理
	void Uninit(void);																							//終了処理
	void Update(void);																						//更新処理
	void Draw(void);																							//描画処理
	void HitEnemy(int nDamage);																		//ダメージ処理
	//void SetEnemy(D3DXVECTOR3 pos, float fWidth, float fHeight);

	//静的メンバ関数
	static CEnemy * Create(D3DXVECTOR3 pos, ENEMYTYPE enemyType);//敵の生成
	static ENEMYTYPE GetEnemyType(void) { return m_enemyType; }			//敵のタイプを取得する
	static HRESULT Load(void);																		//テクスチャを読み込む処理
	static void Unload(void);																				//テクスチャを破棄する処理

	//静的メンバ変数
	static int m_nNumEnemy;																			//敵の総数

private:
	ENEMYSTATE								m_enemyState;										//敵の状態の変数
	D3DXVECTOR3							m_pos;														//位置
	D3DXVECTOR3							m_move;													//移動量
	bool												m_bJump;												//ジャンプしているかしていないか
	CBullet::BULLETTYPE				m_BulletType;											//弾のタイプの管理
	int												m_nCntState;											//状態管理のカウンター
	int												m_nLife;													//敵のライフ
	float												m_fSpeed;												//スピード

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[ENEMY_TEXTURE];			//共有テクスチャへのポインタ
	static ENEMYTYPE						m_enemyType;										//鬼のタイプ分け変数
};
#endif