//=============================================================================
//
// リザルトの処理 [result.h]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//シーン2D
#include "manager.h"			//マネージャー
#include "input.h"				//入力
#include "result.h"				//タイトル
#include "bg.h"					//背景
#include "fade.h"					//フェード
#include "logo.h"					//ロゴ
#include "sound.h"				//サウンド

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{	//何も書かない
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	CBg::Load();						//背景テクスチャの割り当て
	CLogo::Load();					//ロゴテクスチャの割り当て

	//各処理の生成
	CBg::Create();						//背景
	CLogo::Create();					//ロゴ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	CBg::Unload();									//背景のテクスチャの破棄
	CLogo::Unload();								//ロゴのテクスチャの破棄

	CScene::ReleaseFadeAll();				//フェード以外のオブジェクトの破棄
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard * pInputKeyboard = NULL;								//キーボードクラスの呼び出し
	CManager::MODE pManager = CManager::GetMode();			//モードを取得する
	CFade::FADE fade = CFade::GetFade();										//フェードの呼び出し

	//ジョイコンの設定
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	if (pInputKeyboard->GetPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);

		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_RANKING);
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
void CResult::Draw(void)
{
}