//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//シーン2D
#include "manager.h"			//マネージャー
#include "input.h"				//入力
#include "player.h"				//プレイヤー
#include "enemy.h"				//敵
#include "fade.h"					//フェード
#include "score.h"				//スコア
#include "animal.h"				//おとも
#include "sound.h"				//サウンド

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[ENEMY_TEXTURE] = {};
int CEnemy::m_nNumEnemy = 0;
CEnemy::ENEMYTYPE CEnemy::m_enemyType = CEnemy::ENEMYTYPE_RED;		//最初の鬼

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy() : CScene2D(2)
{
	m_enemyState = ENEMYSTATE_NONE;						//通常状態
	m_BulletType = CBullet::BULLETTYPE_NONE;				//弾の種類
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//移動量
	m_fSpeed = 0.0f;
	m_nNumEnemy++;											//敵の総数をカウント
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{	//何も書かない
}

//=============================================================================
// 敵の生成
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, ENEMYTYPE enemyType)
{
	CEnemy * pEnemy = NULL;

	//敵クラスの動的確保
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
	}
	if(pEnemy != NULL)
	{
		pEnemy->Init();
		pEnemy->m_enemyState = ENEMYSTATE_NONE;			//敵の状態
		pEnemy->m_nCntState = 0;												//状態管理のカウンター
		pEnemy->SetPosition(pos);												//位置の設定
		pEnemy->m_pos = pos;														//取得した位置に代入
		pEnemy->m_nLife = ENEMY_LIFE;									//ライフの設定
		pEnemy->m_enemyType = enemyType;								//取得したタイプを代入
		pEnemy->m_bJump = true;

		if (m_enemyType == ENEMYTYPE_RED)
		{	//赤おに
			pEnemy->BindTexture(m_pTexture[0]);
			pEnemy->m_BulletType = CBullet::BULLETTYPE_REDONI;
		}
		if (m_enemyType == ENEMYTYPE_BLUE)
		{	//青おに
			pEnemy->BindTexture(m_pTexture[1]);
			pEnemy->m_BulletType = CBullet::BULLETTYPE_BULEONI;
		}
		if (m_enemyType == ENEMYTYPE_YELLOW)
		{	//黄おに
			pEnemy->BindTexture(m_pTexture[2]);
			pEnemy->m_BulletType = CBullet::BULLETTYPE_YELLOWONI;
		}
	}

	return pEnemy;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init()
{
	CScene2D::Init();

	//オブジェクトの設定
	CScene2D::SetObjType(CScene::OBJTYPE_ENEMY);

	//エネミーのサイズを設定
	SetSize(40.0f, 40.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	m_pos = CScene2D::GetPosition();
	int nPatternAnim = CScene2D::GetPatternAnim();
	CFade::FADE fade = CFade::GetFade();

	switch (m_enemyState)
	{
	case ENEMYSTATE_NONE:		//通常状態
		break;

	case ENEMYSTATE_DAMAGE:	//ダメージ状態
		m_nCntState--;
		if (m_nCntState <= 0)
		{	//ライフが残ってる
			m_enemyState = ENEMYSTATE_NONE;				//通常状態に戻す
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));			//光ってる状態から透明に戻す
		}
		break;

	case ENEMYSTATE_DEATH:
		m_nNumEnemy--;													//敵の総数を減らす

		//敵が全滅した処理
		if (m_nNumEnemy == 0)
		{
			if (fade != CFade::FADE_OUT)
			{
				CFade::SetFade(CManager::MODE_GAMECLEAR);
			}
		}
		break;
	}

	//float nSpeed = 10.0f;
	//m_pos.x -= nSpeed;

	////弾発射
	//if ((rand() % 180) == 0)
	//{
	//	CSound::PlaySound(CSound::SOUND_LABEL_SE_SHOT);
	//	CBullet::Create(m_pos, -BULLET_SPEED, m_BulletType);		//弾発射
	//}

	//m_move.y += ENEMY_GRAVITY;			//重力加算
	//m_pos.y += m_move.y;							//落下

	//if ((rand() % 180) == 0)
	//{
	//	if (m_bJump == false)
	//	{
	//		m_move.y = -ANIMAL_JUMP;
	//		m_bJump = true;								//ジャンプしている状態
	//	}
	//}

	//m_pos.x += m_move.x;

	//移動範囲の処理
	if (m_pos.x >= SCREEN_WIDTH)
	{	//右端行った
		m_pos.x = SCREEN_WIDTH;
	}
	if (m_pos.x <= LEFT_WIDTH)
	{	//左端に行った
		m_pos.x = LEFT_WIDTH;
	}
	if (m_pos.y <= 20)
	{	//上行った
		m_pos.y = 20;
	}
	if (m_pos.y >= ENEMY_FIELD_RANGE)
	{	//下行った
		m_pos.y = ENEMY_FIELD_RANGE;
	}

	//設定した位置を反映
	SetPosition(m_pos);

	if (m_enemyState == ENEMYSTATE_DEATH)
	{	//死んだ状態
		Uninit();		//敵の破棄
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ダメージ処理
//=============================================================================
void CEnemy::HitEnemy(int nDamage)
{
	m_nLife -= nDamage;													//ライフ減る

	if (m_nLife <= 0)
	{	//ライフが0になったら敵の破棄
		m_enemyState = ENEMYSTATE_DEATH;
		CScore::AddScore(23000);										//スコアの加算
	}
	else
	{	//ライフが残ってる
		m_enemyState = ENEMYSTATE_DAMAGE;			//ダメージ状態
		m_nCntState = 5;													//状態管理のカウンターの設定
		SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));			//赤色になる
	}
}

//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, ENEMY_NAME, &m_pTexture[0]);		//あかおに
	D3DXCreateTextureFromFile(pDevice, ENEMY_NAME1, &m_pTexture[1]);		//あおおに
	D3DXCreateTextureFromFile(pDevice, ENEMY_NAME2, &m_pTexture[2]);		//きいろおに

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CEnemy::Unload(void)
{
	if (m_pTexture[0] != NULL)
	{
		m_pTexture[0]->Release();
		m_pTexture[0] = NULL;
	}

	if (m_pTexture[1] != NULL)
	{
		m_pTexture[1]->Release();
		m_pTexture[1] = NULL;
	}

	if (m_pTexture[2] != NULL)
	{
		m_pTexture[2]->Release();
		m_pTexture[2] = NULL;
	}
}