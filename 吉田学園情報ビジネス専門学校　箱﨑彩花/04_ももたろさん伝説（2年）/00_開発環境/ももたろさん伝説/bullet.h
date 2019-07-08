//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _BULLET_H_	//二重インクルード防止
#define _BULLET_H_

#include	"main.h"		//メイン

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BULLETTEX						(5)			//テクスチャの最大数
#define SIZE											(80)			//ポリゴンの中心点からのサイズ
#define BULLET_SPEED							(10.0f)		//弾のスピード
#define MONKEY_BULLET_SPEED		(5.0f)		//サル：弾のスピード
#define REDONI_BULLET_SPEED			(5.0f)		//赤鬼：弾のスピード
#define BULEONI_BULLET_SPEED		(10.0f)		//青鬼：弾のスピード
#define YELLOWONI_BULLET_SPEED	(5.0f)		//黄鬼：弾のスピード
#define MAX_BULLET							(256)		//弾の最大数
#define BULLET_LIFE								(100)		//弾の寿命
#define RANGE										(40)			//当たり判定の範囲
#define BULLET_PRIORITY					(4)			//弾の優先順位
#define BULLET_ANIMAPEED				(10)			//弾のアニメーションスピード

//テクスチャの名前
#define BULLET_DOG			"data/TEXTURE/dog_born.png"
#define BULLET_MONKEY		"data/TEXTURE/banana.png"
#define BULLET_KIJI				"data/TEXTURE/kinomi.png"
#define BULLET_ONI				"data/TEXTURE/dango.png"
#define BULLET_BOSS			"data/TEXTURE/momo.png"

//*****************************************************************************
// 弾クラス
//*****************************************************************************
class CBullet : public CScene2D
{
public:
	typedef enum
	{	//弾の種類
		BULLETTYPE_NONE = 0,					//初期値
		BULLETTYPE_PLAYER,						//プレイヤー
		BULLETTYPE_DOG,							//イヌ
		BULLETTYPE_MONKEY,					//サル
		BULLETTYPE_KIJI,								//キジ
		BULLETTYPE_ENEMY,						//エネミー
		BULLETTYPE_REDONI,						//赤鬼
		BULLETTYPE_BULEONI,					//青鬼
		BULLETTYPE_YELLOWONI,				//黄鬼
		BULLETTYPE_BOSS,							//ボス鬼
		BULLETTYPE_MAX							//種類の最大値
	} BULLETTYPE;

	CBullet(int nPriority);																																		//コンストラクタ
	~CBullet();																																						//デストラクタ
	HRESULT Init(void);																																		//初期化処理
	void Uninit(void);																																				//終了処理
	void Update(void);																																			//更新処理
	void Draw(void);																																				//描画処理
	void SetBullet(BULLETTYPE bulletType, D3DXVECTOR3 pos);
	BULLETTYPE GetBulletType(void) { return m_bulletType; }

	//静的メンバ関数
	static CBullet * Create(D3DXVECTOR3 pos, float	moveDir, BULLETTYPE bulletType);								//オブジェクトの生成
	static HRESULT Load(void);																															//テクスチャを読み込む処理
	static void Unload(void);																																	//テクスチャを破棄する処理

private:
	int								m_nLife;																														//弾の長さ（寿命）
	int								m_nCntAnim;																												//カウンターアニメーション
	int								m_nPatternAnim;																											//アニメーションのパターン数
	int								m_nCntMove;																												//移動のカウンター（イヌ）
	int								m_nChangeMove;																										//弾の移動量（イヌ）
	BULLETTYPE				m_bulletType;																												//弾の種類
	D3DXVECTOR3			m_move;																														//移動量
	bool								m_bUse;																														//イヌ：飛んでいるかどうか
	float								m_fKeepAnimal;																											//イヌ：発射位置を固定する

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BULLETTEX];																	//共有テクスチャへのポインタ
};
#endif