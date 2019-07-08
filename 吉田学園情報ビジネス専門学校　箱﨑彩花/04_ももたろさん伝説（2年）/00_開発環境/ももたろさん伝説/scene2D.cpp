//=============================================================================
//
// シーン2D処理 [scene2D.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//シーン2D
#include "manager.h"			//マネージャー
#include "input.h"				//入力
#include "pause.h"				//ポーズ
#include "life.h"					//ライフ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
bool g_bDelete = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D()
{
}

//=============================================================================
// オーバーロードされたコンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//位置
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				//色
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//移動量
	m_fSize = 0;																//拡大・縮小
	m_nCntAnim = 0;														//カウンターアニメーション
	m_nPatternAnim = 0;													//パターンアニメーション
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{	//何も書かない
}

//=============================================================================
// ポリゴンの生成
//=============================================================================
CScene2D *CScene2D::Create(void)
{
	CScene2D *pScene2D = NULL;

	//オブジェクトクラスの動的確保
	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
	}
	if(pScene2D != NULL)
	{
		pScene2D->Init();
	}

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
{
	VERTEX_2D * pVtx;																				//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	//変数の初期化
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSize = 0;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * MAX_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//ポリゴンの色設定
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクト（自分自身）の破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene2D::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;							//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();		//レンダリングクラスの取得
	CScene::OBJTYPE type = CScene::GetObjType();

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	bool bPause = CPause::GetPause();

	if (type == CScene::OBJTYPE_PAUSE)
	{
		if (bPause == true)
		{
			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, m_pTexture);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
	else
	{
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// ポリゴンの設定
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;

	//ポリゴンの座標設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, - m_fHeight, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3(+m_fWidth,  - m_fHeight, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, + m_fHeight, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3(+m_fWidth, + m_fHeight, 0.0f) + m_pos;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

#if 1
//=============================================================================
// ポリゴンのアニメーションの設定
//=============================================================================
void CScene2D::SetAnimation(float uv, int nPatternAnim)
{
	VERTEX_2D * pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2((uv * nPatternAnim), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((uv * nPatternAnim) + uv, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((uv * nPatternAnim), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((uv * nPatternAnim) + uv, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
#endif

//=============================================================================
// サイズ変更の処理
//=============================================================================
void CScene2D::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	VERTEX_2D * pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの座標設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y - fHeight / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y - fHeight / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth / 2, m_pos.y + fHeight / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth / 2, m_pos.y + fHeight / 2, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 色の処理
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D * pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_col = col;

	//ポリゴンの色設定
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 背景動かす処理（横）
//=============================================================================
void CScene2D::SetBgMove(int nCntBg, float fScrollSpeed)
{
	VERTEX_2D * pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (nCntBg * (fScrollSpeed + 1)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + (nCntBg * (fScrollSpeed + 1)), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nCntBg * (fScrollSpeed + 1)), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (nCntBg * (fScrollSpeed + 1)), 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

#if 0
//=============================================================================
// ライフ処理
//=============================================================================
void CScene2D::SetLife(float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLife = 0; nCntLife < ANIMAL_LIFE; nCntLife++)
	{
		//テクスチャの座標設定
		pVtx[0].pos = D3DXVECTOR3(0.0f + (60.0f * (ANIMAL_LIFE - nCntLife - 1)), 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + (60.0f * (ANIMAL_LIFE - nCntLife - 1)), 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f + (60.0f * (ANIMAL_LIFE - nCntLife - 1)), 55.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + (60.0f * (ANIMAL_LIFE - nCntLife - 1)), 55.0f, 0.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
#endif

//=============================================================================
// テクスチャを割り当てる処理
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}