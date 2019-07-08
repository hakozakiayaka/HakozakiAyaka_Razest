//=============================================================================
//
// 爆発の処理 [explosion.cpp]
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
#include "bullet.h"				//弾
#include "explosion.h"			//爆発

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosion::CExplosion()
{
	m_nCntAnim = 0;
	m_nPatternAnim = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{	//何も書かない
}

//=============================================================================
// ポリゴンの生成
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = NULL;

	//プレイヤークラスの動的確保
	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
	}
	if(pExplosion != NULL)
	{
		pExplosion->Init();													//初期化
		pExplosion->SetPosition(pos);								//位置の設定
		pExplosion->SetAnimation(0.125f, 0);
		pExplosion->BindTexture(m_pTexture);					//テクスチャの割り当て
	}

	return pExplosion;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CExplosion::Init(void)
{
	CScene2D::Init();

	//爆発のサイズを設定
	SetSize(30.0f, 30.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CExplosion::Update(void)
{
	D3DXVECTOR3 pos = CScene2D::GetPosition();		//CScene2Dから位置を取得
	SetPosition(pos);															//取得した位置を、CScene2Dに返す

	m_nCntAnim++;					//カウンターを加算

	if ((m_nCntAnim % EXPLOSION_SPEED) == 0)
	{
		m_nPatternAnim++;		//パターンNoを更新

		//アニメーションの設定
		SetAnimation(0.125f, m_nPatternAnim);							//フレーム数、パターンNo
	}

	//アニメーションの終了処理
	if (m_nPatternAnim >= 7)
	{	//パターン数がすぎたら
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CExplosion::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}