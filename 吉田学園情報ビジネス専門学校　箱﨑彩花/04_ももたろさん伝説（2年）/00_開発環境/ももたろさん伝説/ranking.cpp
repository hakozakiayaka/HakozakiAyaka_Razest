//=============================================================================
//
// ランキング処理 [ranking.h]
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
#include "ranking.h"			//ランキング
#include "bg.h"					//背景
#include "logo.h"					//ロゴ
#include "fade.h"					//フェード
#include "sound.h"				//サウンド
#include "score.h"				//スコア
#include "number.h"			//ナンバー

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CRanking::m_nCntTime = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{	//何も書かない
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	CNumber::Load();
	CBg::Load();						//背景テクスチャの割り当て
	CLogo::Load();

	//各処理の生成
	CBg::Create();						//背景の生成
	CLogo::Create();
	CScore::Create(CScore::SCOREMODE_RANKING);		//スコア

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	CNumber::Unload();
	CBg::Unload();									//背景のテクスチャの破棄
	CLogo::Unload();								//ロゴのテクスチャの破棄

	CScene::ReleaseFadeAll();				//フェード以外のオブジェクトの破棄
}

//=============================================================================
// 更新処理
//=============================================================================
void CRanking::Update(void)
{
	CInputKeyboard * pInputKeyboard = NULL;								 //キーボードクラスの呼び出し
	CManager::MODE pManager = CManager::GetMode();			 //モードを取得する
	CFade::FADE fade = CFade::GetFade();

	//ジョイコンの設定
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	//画面切り替えのカウンター
	m_nCntTime++;

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	if (pInputKeyboard->GetPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{	//エンターキー、ジョイコンBボタン、5秒間たった
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);

		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_TITLE);
		}
	}
	if (m_nCntTime % 180 == 0)
	{	//画面切り替え（ランキングからタイトル）
		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_TITLE);
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
void CRanking::Draw(void)
{
}