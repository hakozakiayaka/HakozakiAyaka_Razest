//=============================================================================
//
// フェード処理 [fade.h]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//シーン2D
#include "manager.h"			//マネージャー
#include "input.h"				//入力
#include "game.h"				//ゲーム
#include "fade.h"					//タイトル

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CFade::FADE CFade::m_fade = CFade::FADE_NONE;									//通常状態
CManager::MODE CFade::m_modeNext = CManager::MODE_TITLE;
D3DXCOLOR CFade::m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//色設定
LPDIRECT3DVERTEXBUFFER9 CFade::m_pVtxBuff = NULL;						//バッファのポインタ
//LPDIRECT3DTEXTURE9	 CFade::m_pTexture = NULL;									//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade() : CScene(7)
{
		CFade::m_fade = FADE_NONE;
		CFade::m_modeNext = CManager::MODE_MAX;
		CFade::m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			//黒い画面
		//m_apScene2D = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{	//何も書かない
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFade::Init(void)
{
	VERTEX_2D * pVtx;																				//頂点情報へのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	CScene::SetObjType(CScene::OBJTYPE_FADE);
	CFade::m_fade = FADE_IN;
	CFade::m_modeNext = CManager::MODE_TITLE;
	CFade::m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);			//黒い画面

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

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
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//ポリゴンの色設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//if (m_apScene2D == NULL)
	//{	//テクスチャの読み込み
	//	m_apScene2D = new CScene2D(FADE_PRIORITY);
	//}
	//if (m_apScene2D != NULL)
	//{
	//	m_apScene2D->Init();
	//	m_apScene2D->BindTexture(m_pTexture);											//テクスチャの割り当て
	//	m_apScene2D->SetPosition(D3DXVECTOR3(1000.0f, 600.0f, 0.0f));	//位置の設定
	//	m_apScene2D->SetSize(200.0f, 100.0f);												//サイズ設定
	//}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFade::Uninit(void)
{
	////テクスチャの破棄
	//if (m_apScene2D != NULL)
	//{
	//	m_apScene2D->Uninit();
	//	m_apScene2D = NULL;
	//}

	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D * pVtx;								//頂点情報へのポインタ

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{	//フェードイン状態
			m_colorFade.a -= 0.03f;				//画面を透明にする
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;			//何もしていない状態にする
			}
		}
		else if (m_fade == FADE_OUT)
		{	//フェードアウト状態
			m_colorFade.a += 0.03f;				//画面を不透明にする
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;					//フェードイン状態

				//モードの設定
				CManager::SetMode(m_modeNext);
			}
		}

		//頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//ポリゴンの色設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();

		//m_apScene2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorFade.a));
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;							//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();		//レンダリングクラスの取得

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Scene2Dの描画
	//m_apScene2D->Draw();
}

//=============================================================================
// フェードの設定
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

#if 0
//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CFade::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, LODING_TEX, &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CFade::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
#endif