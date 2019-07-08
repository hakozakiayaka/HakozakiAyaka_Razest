//=============================================================================
//
// タイトルの処理 [title.h]
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
#include "title.h"					//タイトル
#include "bg.h"					//背景
#include "logo.h"					//ロゴ
#include "fade.h"					//フェード
#include "sound.h"				//サウンド
#include "animal.h"				//おとも

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CTitle::m_nCntTime = 0;						//画面切り替えのカウンター

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{	//何も書かない
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	CBg::Load();						//背景テクスチャの割り当て
	CLogo::Load();					//ロゴテクスチャの割り当て
	CAnimal::Load();					//おともテクスチャの割り当て

	//各処理の生成
	CBg::Create();																													//背景
	CLogo::Create();																												//ロゴ
	CAnimal::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), CAnimal::ANIMALTYPE_KIJI);		//おとも（キジ）

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	CBg::Unload();									//背景のテクスチャの破棄
	CLogo::Unload();								//ロゴのテクスチャの破棄
	CAnimal::Unload();							//おとものテクスチャの破棄

	CScene::ReleaseFadeAll();				//フェード以外のオブジェクトの破棄
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard * pInputKeyboard = NULL;								 //キーボードクラスの呼び出し
	CManager::MODE pManager = CManager::GetMode();			 //モードを取得する
	CFade::FADE fade = CFade::GetFade();										//フェードの取得

	//ジョイコンの設定
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	//画面切り替えのカウンター
	m_nCntTime++;

	if (pInputKeyboard->GetPress(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{	//エンターキーとジョイコンBボタン押した
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);

		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_TUTORIAL);
		}
	}
	else if (m_nCntTime % 300 == 0)
	{	//5秒間経った時、ランキング画面に移行
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
void CTitle::Draw(void)
{
}