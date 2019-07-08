//=============================================================================
//
// ライフ処理 [life.cpp]
// Author : 箱�ｱ彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "scene2D.h"			//シーン2D
#include "renderer.h"			//レンダリング
#include "manager.h"			//マネージャー
#include "life.h"					//ライフ
#include "animal.h"				//おとも
#include "game.h"				//ゲーム

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;
int CLife::m_nLife = ANIMAL_LIFE;

//=============================================================================
// コンストラクタ
//=============================================================================
CLife::CLife()
{
	m_nLife = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLife::~CLife()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CLife * CLife::Create(D3DXVECTOR3 pos, int nCntLife)
{
	CLife * pLife = NULL;

	if (pLife == NULL)
	{	//ライフの動的確保
		pLife = new CLife;
	}
	if (pLife != NULL)
	{
		pLife->Init();							//ライフの初期化
		pLife->SetPosition(pos);		//位置の設定
		pLife->m_pos = pos;
		pLife->BindTexture(m_pTexture);
	}

	return pLife;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLife::Init(void)
{
	CScene2D::Init();

	//オブジェクトの設定
	CScene2D::SetObjType(CScene::OBJTYPE_LIFE);

	CScene2D::SetSize(30.0f, 30.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLife::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLife::Update(void)
{
	CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CLife::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ライフの設定処理
//=============================================================================
void CLife::SetLife(int nLifeDown)
{
	//int nLostLife;

	m_nLife = ANIMAL_LIFE - nLifeDown;
}

//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CLife::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, LIFE_TEX,  &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CLife::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}