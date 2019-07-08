//=============================================================================
//
// ロゴ処理 [logo.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//シーン2D
#include "manager.h"			//マネージャー
#include "input.h"				//入力
#include "logo.h"					//ロゴ

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LOGO_PRIORITY			(0)			//背景の優先順位

//テクスチャ名
#define LOGO_TITLE								"data/TEXTURE/titlelogo.png"						//タイトル
#define LOGO_PRESSENTER					"data/TEXTURE/pressEnter.png"					//プレスエンター
#define LOGO_RANKING						"data/TEXTURE/rankinglogo.png"					//ランキングロゴ
#define LOGO_RANKINGLINE				"data/TEXTURE/rankingLine.png"					//ランキングの下ライン
#define LOGO_RANK								"data/TEXTURE/rank.png"								//順位
#define LOGO_CLEAR								"data/TEXTURE/gameClear.png"					//ゲームクリア
#define LOGO_OVER								"data/TEXTURE/gameOver.png"					//ゲームオーバー
#define LOGO_TUTORIAL						"data/TEXTURE/tutorial100.png"					//チュートリアルロゴ
#define LOGO_RESULT							"data/TEXTURE/resultlogo.png"					//リザルトロゴ

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	 CLogo::m_pTexture[MAX_LOGOTEXTURE] = {};		//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CLogo::CLogo() : CScene2D(LOGO_PRIORITY)
{
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_fFlash = 0.0f;
	m_nCntFlash = 0;

	for (int nCntLogo = 0; nCntLogo < MAX_LOGOTEXTURE; nCntLogo++)
	{
		m_apScene2D[nCntLogo] = NULL;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CLogo::~CLogo()
{	//何も書かない
}

//=============================================================================
// ロゴの生成
//=============================================================================
CLogo *CLogo::Create()
{
	CLogo *pLogo = NULL;

	//背景クラスの動的確保
	if (pLogo == NULL)
	{
		pLogo = new CLogo;
	}

	//背景の初期化処理
	if (pLogo != NULL)
	{
		pLogo->Init();
	}

	return pLogo;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLogo::Init(void)
{
	CManager::MODE BgMode = CManager::GetMode();

	switch (BgMode)
	{
	case CManager::MODE_TITLE:
		if (m_apScene2D[0] == NULL)
		{	//ももたろさん伝説ロゴ
			m_apScene2D[0] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[0]);					//テクスチャの割り当て
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f, 0.0f));
			m_apScene2D[0]->SetSize(800.0f, 250.0f);
		}

		if (m_apScene2D[1] == NULL)
		{	//プレスエンターロゴ
			m_apScene2D[1] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[1] != NULL)
		{
			m_apScene2D[1]->Init();
			m_apScene2D[1]->BindTexture(m_pTexture[1]);																//テクスチャの割り当て
			m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f));
			m_apScene2D[1]->SetSize(380.0f, 90.0f);
			m_logoState = CLogo::LOGOSTATE_FLASH;
			m_fFlash = 0.05f;
		}
		break;

	case CManager::MODE_TUTORIAL:
		if (m_apScene2D[0] == NULL)
		{	//プレスエンターロゴ
			m_apScene2D[0] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[1]);																//テクスチャの割り当て
			m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f));
			m_apScene2D[0]->SetSize(380.0f, 90.0f);
			m_logoState = CLogo::LOGOSTATE_FLASH;
			m_fFlash = 0.05f;
		}
		break;

	case CManager::MODE_GAMECLEAR:
		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();																									//初期化
			m_apScene2D[0]->BindTexture(m_pTexture[4]);																//テクスチャの割り当て
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(300.0f, 200.0f, 0.0f));								//位置の設定
			m_apScene2D[0]->SetSize(450.0f, 150.0f);																		//サイズの設定
		}

		if (m_apScene2D[1] == NULL)
		{	//プレスエンターロゴ
			m_apScene2D[1] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[1] != NULL)
		{
			m_apScene2D[1]->Init();
			m_apScene2D[1]->BindTexture(m_pTexture[8]);																//テクスチャの割り当て
			m_apScene2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f));
			m_apScene2D[1]->SetSize(380.0f, 90.0f);
			m_logoState = CLogo::LOGOSTATE_FLASH;
			m_fFlash = 0.05f;
		}
		break;

	case CManager::MODE_GAMEOVER:
		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();																									//初期化
			m_apScene2D[0]->BindTexture(m_pTexture[5]);																//テクスチャの割り当て
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(850.0f, 200.0f, 0.0f));								//位置の設定
			m_apScene2D[0]->SetSize(550.0f, 170.0f);																		//サイズの設定
		}
		break;

	case CManager::MODE_RANKING:
		if (m_apScene2D[0] == NULL)
		{	//ランキングロゴ
			m_apScene2D[0] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();																									//初期化
			m_apScene2D[0]->BindTexture(m_pTexture[2]);																//テクスチャの割り当て
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 70.0f, 0.0f));		//位置の設定
			m_apScene2D[0]->SetSize(300.0f, 70.0f);																			//サイズ設定
		}

		if (m_apScene2D[1] == NULL)
		{	//順位
			m_apScene2D[1] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[1] != NULL)
		{
			m_apScene2D[1]->Init();																									//初期化
			m_apScene2D[1]->BindTexture(m_pTexture[6]);																//テクスチャの割り当て
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(300.0f, 400.0f, 0.0f));								//位置の設定
			m_apScene2D[1]->SetSize(150.0f, 500.0f);																		//サイズの設定
		}

		if (m_apScene2D[2] == NULL)
		{	//プレスエンターロゴ
			m_apScene2D[2] = new CScene2D(LOGO_PRIORITY);
		}
		if (m_apScene2D[2] != NULL)
		{
			m_apScene2D[2]->Init();
			m_apScene2D[2]->BindTexture(m_pTexture[8]);																//テクスチャの割り当て
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apScene2D[2]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f));
			m_apScene2D[2]->SetSize(380.0f, 90.0f);
			m_logoState = CLogo::LOGOSTATE_FLASH;
			m_fFlash = 0.05f;
		}

		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLogo::Uninit(void)
{	//背景破棄
	for (int nCntBg = 0; nCntBg < MAX_LOGOTEXTURE; nCntBg++)
	{
		m_apScene2D[nCntBg]->Uninit();
		m_apScene2D[nCntBg] = NULL;
	}

	//オブジェクト（自分自身）の破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLogo::Update(void)
{
	CManager::MODE BgMode = CManager::GetMode();

	switch (m_logoState)
	{
	case LOGOSTATE_NONE:
		break;

	case LOGOSTATE_FLASH:
		m_col.a += m_fFlash;
		if (m_col.a <= 0.0f || m_col.a >= 1.0f)
		{
			m_fFlash *= -1.0f;
		}
		break;
	}

	if (BgMode == CManager::MODE_TITLE)
	{
		if (m_logoState == LOGOSTATE_FLASH)
		{
			m_apScene2D[1]->SetColor(m_col);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CLogo::Draw(void)
{
}

#if 1
//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CLogo::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, LOGO_TITLE, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, LOGO_PRESSENTER, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, LOGO_RANKING, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, LOGO_RANKINGLINE, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, LOGO_CLEAR, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, LOGO_OVER, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, LOGO_RANK, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TUTORIAL, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, LOGO_RESULT, &m_pTexture[8]);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CLogo::Unload(void)
{
	// テクスチャの破棄
	for (int nCntBg = 0; nCntBg < MAX_LOGOTEXTURE; nCntBg++)
	{
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}
}
#endif