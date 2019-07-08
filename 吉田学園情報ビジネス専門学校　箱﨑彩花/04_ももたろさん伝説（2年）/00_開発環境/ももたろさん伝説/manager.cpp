//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include	"manager.h"		//マネージャー
#include "main.h"			//メイン
#include "renderer.h"		//レンダリング
#include "scene.h"			//シーン
#include "scene2D.h"		//シーン2D
#include "input.h"			//入力
#include "game.h"			//ゲーム
#include "title.h"				//タイトル
#include "tutorial.h"		//チュートリアル
#include "result.h"			//リザルト
#include "ranking.h"		//ランキング
#include "fade.h"				//フェード
#include "sound.h"			//サウンド

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRenderer * CManager::m_pRenderer = NULL;																				//レンダリング
CInputKeyboard * CManager::m_pInputKeyboard = NULL;																//キーボード
CDirectXInput * CManager::m_pDirectXInput = NULL;																		//ジョイコン
CFade * CManager::m_pFade = NULL;																								//フェード
CTitle * CManager::m_pTitle = NULL;																								//タイトル
CTutorial * CManager::m_pTutorial = NULL;																						//チュートリアル
CGame * CManager::m_pGame = NULL;																							//ゲーム
CResult * CManager::m_pResult = NULL;																							//リザルト
CRanking * CManager::m_pRanking = NULL;																					//ランキング
CSound * CManager::m_pSound = NULL;																							//サウンド
int CManager::m_nScore = 0;																												//スコアの初期化
int CManager::m_nHighScore[RANKING_NUMBER] = { 50000, 40000, 30000, 20000, 10000 };		//スコアの初期値

//モードの設定
CManager::MODE  CManager::m_mode = MODE_GAME;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{	//何も書かない
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダリングクラスの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	//レンダリングの初期化処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, TRUE);
	}

	//サウンドクラスの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	//サウンドクラスの初期化処理
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}

	//キーボードクラスの生成
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;
	}

	//キーボードの初期化処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Init(hInstance, hWnd);
	}

	//ジョイコンクラスの生成
	if (m_pDirectXInput == NULL)
	{
		m_pDirectXInput = new CDirectXInput;
	}

	//ジョイコンの初期化処理
	if (m_pDirectXInput != NULL)
	{
		m_pDirectXInput->Init(hInstance, hWnd);
	}

	//フェードクラスの生成
	if (m_pFade == NULL)
	{
		m_pFade = new CFade;
	}

	//フェードの初期化処理
	if (m_pFade != NULL)
	{
		m_pFade->Init();
	}

	//モードの設定
	CManager::SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{	//内側から消していく

	//フェードクラスの破棄
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		m_pFade = NULL;
	}

	//全てのオブジェクトの破棄
	CScene::ReleaseAll();

	//サウンドクラスの破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
	}

	//ジョイコンクラスの破棄
	if (m_pDirectXInput != NULL)
	{
		m_pDirectXInput->Uninit();
		delete m_pDirectXInput;
		m_pDirectXInput = NULL;
	}

	//キーボードクラスの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//レンダリングクラスの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	//キーボードの更新処理（いちばん最初に呼び出す）
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//ジョイコンの更新処理（いちばん最初に呼び出す）
	if (m_pDirectXInput != NULL)
	{
		m_pDirectXInput->Update();
	}

	// レンダリングの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	switch (m_mode)
	{	//更新処理
	case MODE_TITLE:
		m_pTitle->Update();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Update();
		break;

	case MODE_GAME:
		m_pGame->Update();
		break;

	case CManager::MODE_GAMECLEAR:
		m_pResult->Update();
		break;

	case CManager::MODE_GAMEOVER:
		m_pResult->Update();
		break;

	case MODE_RANKING:
		m_pRanking->Update();
		break;
	}

	//フェードの更新
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// レンダリングの描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{	//描画処理
	case MODE_TITLE:
		m_pTitle->Draw();
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Draw();
		break;

	case MODE_GAME:
		m_pGame->Draw();
		break;

	case CManager::MODE_GAMECLEAR:
		m_pResult->Draw();
		break;

	case CManager::MODE_GAMEOVER:
		m_pResult->Draw();
		break;

	case MODE_RANKING:
		m_pRanking->Draw();
		break;
	}

	//フェードの描画処理
	if (m_pFade != NULL)
	{
		m_pFade->Draw();
	}
}

//=============================================================================
// モードの設定
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{	//終了処理
	case MODE_TITLE:
		m_pTitle->Uninit();
		//サウンドの停止
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM000);
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Uninit();
		//サウンドの停止
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM001);
		break;

	case MODE_GAME:
		m_pGame->Uninit();
		m_pGame = NULL;
		//サウンドの停止
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM002);
		break;

	case CManager::MODE_GAMECLEAR:
		m_pResult->Uninit();
		//サウンドの停止
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM003);
		break;

	case CManager::MODE_GAMEOVER:
		m_pResult->Uninit();
		//サウンドの停止
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM004);
		break;

	case MODE_RANKING:
		m_pRanking->Uninit();
		//サウンドの停止
		m_pSound->StopSound(CSound::SOUND_LABEL_BGM005);
		break;
	}

	m_mode = mode;

	switch (mode)
	{	//入力処理
	case MODE_TITLE:
		m_pTitle->Init();
		//サウンド再生
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM000);
		break;

	case MODE_TUTORIAL:
		m_pTutorial->Init();
		//サウンド再生
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM001);
		break;

	case MODE_GAME:
		m_pGame = new CGame;
		m_pGame->Init();
		//サウンド再生
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM002);
		break;

	case CManager::MODE_GAMECLEAR:
		m_pResult->Init();
		//サウンド再生
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM003);
		break;

	case CManager::MODE_GAMEOVER:
		m_pResult->Init();
		//サウンド再生
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM004);
		break;

	case MODE_RANKING:
		m_pRanking->Init();
		//サウンド再生
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM005);
		break;
	}
}