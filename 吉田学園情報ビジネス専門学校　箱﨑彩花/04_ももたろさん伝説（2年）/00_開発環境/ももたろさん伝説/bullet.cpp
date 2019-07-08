//=============================================================================
//
// 弾の処理 [bullet.cpp]
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
#include "animal.h"				//おとも
#include "bullet.h"				//弾
#include "explosion.h"			//爆発
#include "enemy.h"				//敵
#include "score.h"				//スコア
#include "effect.h"				//エフェクト
#include "life.h"					//ライフ
#include "game.h"				//ゲーム
#include "sound.h"				//サウンド

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_BULLETTEX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	m_nLife = 0;						//ライフ
	m_nCntAnim = 0;				//カウンターアニメーション
	m_nPatternAnim = 0;			//パターン数
	//m_nCntMove = 0;
	//m_nChangeMove = 0;
	m_bUse = false;					//イヌ：弾が使用されているか
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{	//何も書かない
}

//=============================================================================
// 弾の生成
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, float moveDir, BULLETTYPE bulletType)
{
	CBullet *pBullet = NULL;

	//弾クラスの動的確保
	if (pBullet == NULL)
	{
		pBullet = new CBullet(BULLET_PRIORITY);
	}
	if (pBullet != NULL)
	{
		pBullet->Init();																		//初期化処理
		pBullet->SetPosition(pos);														//位置の設定
		pBullet->m_fKeepAnimal = pos.x;											//イヌ：弾発射の位置固定
		pBullet->m_bulletType = bulletType;										//弾の種類
		pBullet->m_move = D3DXVECTOR3(moveDir, 0.0f, 0.0f);		//弾の飛ぶ方向
		//pBullet->SetAnimation(0.2f, 0);												//アニメーションの設定

		if (pBullet->m_bulletType == BULLETTYPE_DOG)
		{	//イヌ
			pBullet->BindTexture(m_pTexture[0]);
		}
		if (pBullet->m_bulletType == BULLETTYPE_MONKEY)
		{	//サル：斜めに飛ぶ
			pBullet->BindTexture(m_pTexture[1]);
			pBullet->m_move.x += sinf(D3DX_PI * 0.9f) * MONKEY_BULLET_SPEED;
			pBullet->m_move.y += cosf(D3DX_PI * 0.9f) * MONKEY_BULLET_SPEED;
		}
		if (pBullet->m_bulletType == BULLETTYPE_KIJI)
		{	//キジ：真下に飛ばす
			pBullet->BindTexture(m_pTexture[2]);
			pBullet->m_move = D3DXVECTOR3(0.0f, moveDir, 0.0f);
		}
		if (pBullet->m_bulletType == BULLETTYPE_REDONI)
		{	//あかおに
			pBullet->BindTexture(m_pTexture[3]);
			pBullet->m_move.x += sinf(D3DX_PI * 0.8f) * REDONI_BULLET_SPEED;
			pBullet->m_move.y += cosf(D3DX_PI * 0.8f) * REDONI_BULLET_SPEED;
		}
		if (pBullet->m_bulletType == BULLETTYPE_BULEONI)
		{	//あおおに
			pBullet->BindTexture(m_pTexture[3]);
			pBullet->m_move.x += sinf(D3DX_PI * -0.75f) * BULEONI_BULLET_SPEED;
			pBullet->m_move.y += cosf(D3DX_PI * -0.75f) * BULEONI_BULLET_SPEED;
		}
		if (pBullet->m_bulletType == BULLETTYPE_YELLOWONI)
		{	//きいろおに
			pBullet->BindTexture(m_pTexture[3]);
		}
	}

	return pBullet;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();

	//弾の初期設定
	m_nLife = BULLET_LIFE;

	//オブジェクトの設定
	CScene2D::SetObjType(CScene::OBJTYPE_BULLET);

	//弾のサイズを設定
	CScene2D::SetSize(30.0f, 30.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();							//位置の取得
	int nAnimalType = CAnimal::GetAnimal();										//おともの種類を取得
	int nEnemyType = CEnemy::GetEnemyType();								//敵の種類を取得
	CLife * pLife = NULL;

	//弾が移動する
	pos.x += m_move.x;
	pos.y += m_move.y;

	if (m_bulletType != CBullet::BULLETTYPE_DOG)
	{	//イヌ以外の弾には重力をつける
		m_move.y += 0.15f;
	}

#if 0
	if (m_bulletType == BULLETTYPE_DOG || m_bulletType == BULLETTYPE_MONKEY || m_bulletType == BULLETTYPE_KIJI)
	{
		//カウンターを加算
		m_nCntAnim++;

		//アニメーション
		if ((m_nCntAnim % BULLET_ANIMAPEED) == 0)
		{
			m_nPatternAnim++;		//パターンNoを更新
			CScene2D::SetAnimation(0.2f, m_nPatternAnim);
		}
		CScene2D::SetPosition(pos);																		//位置の設定
	}

	if (m_bulletType == BULLETTYPE_REDONI || m_bulletType == BULLETTYPE_BULEONI || m_bulletType == BULLETTYPE_YELLOWONI)
	{
		CScene2D::SetPosition(pos);																		//位置の設定
	}
#endif

	CScene2D::SetPosition(pos);
	CEffect::Create(pos, D3DXCOLOR(0.5f, 0.0f, 0.0f, 1.0f));								//エフェクト

	//弾の飛距離の設定
	m_nLife--;

	if (m_nLife <= 0 || pos.x >= SCREEN_WIDTH - 20)
	{	//弾の長さが0になった、画面右側まできた、地面
		CExplosion::Create(pos);
		Uninit();
	}

	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		for (int nCntBullet = 0; nCntBullet < MAX_DATA; nCntBullet++)
		{
			CScene * pScene = NULL;
			if (pScene == NULL)
			{
				pScene = CScene::GetScene(nCntPriority, nCntBullet);
			}
			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (this->m_bulletType == BULLETTYPE_DOG || this->m_bulletType == BULLETTYPE_MONKEY || this->m_bulletType == BULLETTYPE_KIJI)
				{	//おともの弾
					if (m_bulletType == BULLETTYPE_DOG)
					{	//イヌの弾のみ
						SetBullet(CBullet::BULLETTYPE_DOG, pos);
					}
					if (objType == OBJTYPE_ENEMY)
					{	//イヌの弾が、敵に当たった
						CEnemy * pEnemy = ((CEnemy*)pScene);								//エネミーを呼び出して、pSceneの中に強制castする
						D3DXVECTOR3 enemyPos = pEnemy->GetPosition();			//enemyPosを作って、親クラスのposの情報を持ってくる

						//当たり判定
						if (pos.x > enemyPos.x - RANGE
							&& pos.x < enemyPos.x + RANGE
							&& pos.y > enemyPos.y - RANGE
							&& pos.y < enemyPos.y + RANGE)
						{
							CSound::PlaySound(CSound::SOUND_LABEL_SE_HIT000);
							pEnemy->HitEnemy(1);													//ライフを1減らす
							CExplosion::Create(pos);												//爆発の生成
							Uninit();																			//弾の破棄
							break;
						}
					}
				}

#if 1
				if (this->m_bulletType == BULLETTYPE_REDONI || this->m_bulletType == BULLETTYPE_BULEONI || this->m_bulletType == BULLETTYPE_YELLOWONI)
				{	//エネミーの弾
					if (objType == OBJTYPE_ANIMAL)
					{	//敵の弾が、おともに当たった
						CAnimal * pAnimal = ((CAnimal*)pScene);								//プレイヤーを呼び出して、pSceneの中に強制castする
						D3DXVECTOR3 animalPos = pAnimal->GetPosition();				//animalPosを作って、親クラスのposの情報を持ってくる

						//当たり判定
						if (pos.x > animalPos.x - RANGE
							&& pos.x < animalPos.x + RANGE
							&& pos.y > animalPos.y - RANGE
							&& pos.y < animalPos.y + RANGE)
						{
							CSound::PlaySound(CSound::SOUND_LABEL_SE_HIT000);
							pLife->SetLife(1);						//ライフ減る
							pAnimal->HitAnimal(1);
							CExplosion::Create(pos);
							Uninit();
							break;
						}
					}
				}
#endif
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// おともの弾の設定
//=============================================================================
void CBullet::SetBullet(BULLETTYPE bulletType, D3DXVECTOR3 pos)
{
	m_bulletType = bulletType;

	if (m_bulletType == BULLETTYPE_DOG)
	{
		if (m_bUse == false)
		{
			if (pos.x > m_fKeepAnimal + 400)
			{
				m_bUse = true;
				m_move.x *= -1;
			}
		}
	}
}

//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BULLET_DOG, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, BULLET_MONKEY, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, BULLET_KIJI, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, BULLET_ONI, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, BULLET_BOSS, &m_pTexture[4]);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CBullet::Unload(void)
{
	// テクスチャの破棄
	for (int nCntBullet = 0; nCntBullet < MAX_BULLETTEX; nCntBullet++)
	{
		if (m_pTexture[nCntBullet] != NULL)
		{
			m_pTexture[nCntBullet]->Release();
			m_pTexture[nCntBullet] = NULL;
		}
	}
}