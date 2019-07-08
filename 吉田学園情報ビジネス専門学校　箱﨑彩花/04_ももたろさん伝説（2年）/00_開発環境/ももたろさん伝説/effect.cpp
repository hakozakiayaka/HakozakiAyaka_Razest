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
#include "player.h"				//プレイヤー
#include "bullet.h"				//弾
#include "explosion.h"			//爆発
#include "effect.h"				//エフェクト

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EFFECT_LIFE					(20)				//エフェクトの表示時間の設定
#define EFFECT_SIZE					(20.0f)			//エフェクトのサイズ
#define EFFECT_PRIORITY		(3)				//エフェクトの優先順位

//テクスチャ名
#define EFFECT_NAME				"data/TEXTURE/effect000.jpg"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	m_nSize = EFFECT_SIZE;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{	//何も書かない
}

//=============================================================================
// ポリゴンの生成
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	CEffect *pEffect = NULL;

	//プレイヤークラスの動的確保
	if (pEffect == NULL)
	{
		pEffect = new CEffect(EFFECT_PRIORITY);
	}
	if(pEffect != NULL)
	{
		pEffect->Init();
		pEffect->SetPosition(pos);
		pEffect->SetColor(D3DXCOLOR(col.r, col.g, col.b, col.a));

		//テクスチャの割り当て
		pEffect->BindTexture(m_pTexture);
	}

	return pEffect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEffect::Init(void)
{
	CScene2D::Init();

	//初期化
	CScene2D::SetObjType(CScene2D::OBJTYPE_EFFECT);
	m_nLife = EFFECT_LIFE;								//エフェクトの表示時間
	CScene2D::SetSize(m_nSize, m_nSize);			//エフェクトのサイズ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	m_nLife--;
	CScene2D::SetSize(m_nSize + m_nLife, m_nSize + m_nLife);

	if (m_nLife == 0)
	{	//表示時間が0になった
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;							//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();		//レンダリングクラスの取得

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CEffect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, EFFECT_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CEffect::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}