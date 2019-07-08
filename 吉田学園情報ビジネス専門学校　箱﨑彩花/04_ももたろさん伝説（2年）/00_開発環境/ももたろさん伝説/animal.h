//=============================================================================
//
// おとも処理 [animal.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _ANIMAL_H_	//二重インクルード防止
#define _ANIMAL_H_

#include	"main.h"		//メイン
#include	"life.h"			//ライフ
#include "bullet.h"		//弾

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ANIMALTEX					(3)														//テクスチャの最大数
#define PATTERN_ANIM						(0.25f)													//分割数
#define SIZE										(80)														//ポリゴンの中心点からのサイズ
#define ANIMAL_SPEED						(1.0f)													//おとものスピード
#define ANIMAL_FIELD_RANGE		(500.0f)												//地面の範囲
#define ANIMAL_GRAVITY					(0.5)														//重力加算
#define ANIMAL_JUMP						(7)														//ジャンプ
#define LEFT_WIDTH							(70)														//左端行った時の画面の距離
#define ANIMAL_INERTIA_SPEED		(0.15f)													//慣性のスピード
#define ANIMAL_ANIMSPEED			(20)														//おとものアニメーションのスピード
#define ANIMAL_LIFE							(3)														//おとものライフ

//テクスチャ名
#define ANIMAL_DOG				"data/TEXTURE/dog.png"						//（イヌ）
#define ANIMAL_MONKEY			"data/TEXTURE/monkey.png"				//（サル）
#define ANIMAL_KIJI					"data/TEXTURE/kiji.png"						//（キジ）

//*****************************************************************************
// おともクラス
//*****************************************************************************
class CAnimal : public CScene2D
{
public:
	typedef enum
	{	//おともの状態管理
		ANIMALSTATE_NONE = 0,																//通常状態
		ANIMALSTATE_DAMAGE,																//ダメージ状態
		ANIMALSTATE_DEATH,																	//死んだ状態
		ANIMALSTATE_MAX																		//状態管理の最大数
	} ANIMALSTATE;

	typedef enum
	{	//おとものタイプ分け
		ANIMALTYPE_DOG = 0,																	//イヌ
		ANIMALTYPE_MONKEY,																//サル
		ANIMALTYPE_KIJI,																			//キジ
		ANIMALTYPE_MAX																			//おともの最大数
	} ANIMALTYPE;

	CAnimal(int nPriority = 4);																	//コンストラクタ
	~CAnimal();																							//デストラクタ
	HRESULT Init();																					//初期化処理
	void Uninit(void);																					//終了処理
	void Update(void);																				//更新処理
	void Draw(void);																					//描画処理
	void HitAnimal(int nDamage);																//ダメージ処理

	//静的メンバ関数
	static CAnimal * Create(D3DXVECTOR3 pos, ANIMALTYPE animalType);					//おともの生成
	static HRESULT Load(void);																//テクスチャを読み込む処理
	static void Unload(void);																		//テクスチャを破棄する処理
	static ANIMALTYPE GetAnimal(void) { return m_animalType; }		//おとものタイプ取得処理

	int GetLife(void) { return m_nLife; }

private:
	ANIMALSTATE							m_animalState;								//おともの状態管理の変数
	D3DXVECTOR3							m_pos;												//位置
	D3DXVECTOR3							m_move;											//移動量
	bool												m_bJump;										//ジャンプしているかしていないか
	int												m_nCntAnim;									//カウンターアニメーション
	int												m_nPatternAnim;								//パターンアニメーション
	int												m_nLife;											//ライフ
	int												m_nCntState;									//状態管理のカウンター
	int												m_nSelect;										//おとも切り替え
	CBullet::BULLETTYPE				m_BulletType;									//弾のタイプの管理

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_ANIMALTEX];		//共有テクスチャへのポインタ
	static ANIMALTYPE					m_animalType;								//おともを使い分ける変数
	static CLife * m_pLife[ANIMAL_LIFE];												//ライフクラスの取得

};
#endif