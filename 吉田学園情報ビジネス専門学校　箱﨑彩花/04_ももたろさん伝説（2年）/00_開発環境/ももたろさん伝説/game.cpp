//=============================================================================
//
// ゲームの処理 [game.h]
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
#include "enemy.h"				//敵
#include "score.h"				//スコア
#include "effect.h"				//エフェクト
#include "bg.h"					//背景
#include "number.h"			//ナンバー
#include "game.h"				//ゲーム
#include "fade.h"					//フェード
#include "pause.h"				//ポーズ
#include "life.h"					//ライフ

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CPlayer * CGame::m_pPlayer = NULL;																		//プレイヤー
CAnimal * CGame::m_pAnimal = NULL;																		//おとも
CEnemy * CGame::m_pEnemy = NULL;																		//エネミー
CNumber * CGame::m_pNumber = NULL;																	//スコア
CPause * CGame::m_pPause = NULL;																		//ポーズ
CScore * CGame::m_pScore = NULL;																		//スコア
int CGame::m_nCntTime = 0;																						//

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{	//何も書かない
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	//テクスチャの割り当て
	CBg::Load();						//背景テクスチャの割り当て
	CPlayer::Load();					//プレイヤーのテクスチャの割り当て
	CAnimal::Load();					//おとものテクスチャの割り当て
	CEnemy::Load();					//エネミーのテクスチャの割り当て
	CBullet::Load();					//弾のテクスチャの割り当て
	CExplosion::Load();				//爆発テクスチャの割り当て
	CNumber::Load();				//ナンバーのテクスチャの割り当て
	CEffect::Load();					//エフェクトのテクスチャの割り当て
	CPause::Load();					//ポーズのテクスチャの割り当て

	//生成処理
	CBg::Create();																																										//背景
	m_pScore = CScore::Create(CScore::SCOREMODE_GAME);																							//スコア
	m_pPause = CPause::Create();																																			//ポーズ
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(200.0f, 430.0f, 0.0f));																				//プレイヤー
	m_pAnimal = CAnimal::Create(D3DXVECTOR3(250.0f, 450.0f, 0.0f), CAnimal::ANIMALTYPE_DOG);								//おとも（最初はイヌ）

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), CEnemy::ENEMYTYPE_RED);				//赤鬼
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(950.0f, 500.0f, 0.0f), CEnemy::ENEMYTYPE_RED);				//赤鬼

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(800.0f, 450.0f, 0.0f), CEnemy::ENEMYTYPE_BLUE);				//青鬼
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(600.0f, 400.0f, 0.0f), CEnemy::ENEMYTYPE_RED);				//青鬼
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(900.0f, 400.0f, 0.0f), CEnemy::ENEMYTYPE_YELLOW);		//青鬼

	return S_OK;
}

//=============================================================================
// 終了処理
//===========================================================================
void CGame::Uninit(void)
{
	CPause::Unload();					//ポーズのテクスチャの破棄
	CBg::Unload();							//背景のテクスチャの破棄
	CNumber::Unload();				//ナンバーのテクスチャの破棄
	CEffect::Unload();					//エフェクトのテクスチャの破棄
	CExplosion::Unload();				//爆発テクスチャの破棄
	CBullet::Unload();					//弾テクスチャの破棄
	CAnimal::Unload();					//おともテクスチャの破棄
	CPlayer::Unload();					//プレイヤーのテクスチャの破棄
	CEnemy::Unload();					//エネミーのテクスチャの破棄

	if (m_pAnimal != NULL)
	{	//おともの破棄
		m_pAnimal = NULL;
	}
	if (m_pEnemy != NULL)
	{	//エネミーの破棄
		m_pEnemy = NULL;
	}
	if (m_pPlayer != NULL)
	{	//プレイヤーの破棄
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}
	if (m_pScore != NULL)
	{	//スコアの破棄
		m_pScore->Uninit();
		m_pScore = NULL;
	}
	if (m_pPause != NULL)
	{	//ポーズの破棄
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	CScene::ReleaseFadeAll();		//フェード以外のオブジェクトの破棄
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	CInputKeyboard * pInputKeyboard = NULL;								//キーボードクラスの呼び出し
	CManager::MODE pManager = CManager::GetMode();			//モードの取得
	CFade::FADE fade = CFade::GetFade();										//フェードの取得
	bool bPause = CPause::GetPause();

	//ジョイコンの設定
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	////タイムのカウンター
	//m_nCntTime++;

	//if (m_nCntTime % 60 == 0)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), CEnemy::ENEMYTYPE_RED);				//赤鬼
	//}
	//if (m_nCntTime % 120 == 0)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(900.0f, 500.0f, 0.0f), CEnemy::ENEMYTYPE_BLUE);				//青鬼
	//}
	//if (m_nCntTime % 240 == 0)
	//{
	//	m_pEnemy = CEnemy::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f), CEnemy::ENEMYTYPE_RED);				//赤鬼
	//}

	//ポーズ処理
	if (pInputKeyboard->GetTrigger(DIK_P) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_START && CDirectXInput::GetConnectionJoypad() == true))
	{
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			bPause = bPause ? false : true;
			CPause::SetPause(bPause);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
	}

	if (m_pPause != NULL)
	{
		if (bPause == true)
		{
			m_pPause->Update();
		}
	}

	//おおもとの枠だけに必要（タイトル、ゲーム、、とか）
	if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_PUSH)
	{
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_NONE);
	}
	else if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NONE)
	{
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_NOTPUSH);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
}