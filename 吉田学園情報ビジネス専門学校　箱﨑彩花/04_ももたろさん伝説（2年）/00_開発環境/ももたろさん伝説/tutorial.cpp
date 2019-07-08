//=============================================================================
//
// チュートリアル処理 [tutorial.h]
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
#include "tutorial.h"			//チュートリアル
#include "bg.h"					//背景
#include "logo.h"					//ロゴ
#include "fade.h"					//フェード
#include "sound.h"				//サウンド
#include "player.h"				//プレイヤー
#include "animal.h"				//おとも
#include "bullet.h"				//弾
#include "explosion.h"			//爆発
#include "effect.h"				//エフェクト

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{	//何も書かない
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	CBg::Load();						//背景テクスチャの割り当て
	CLogo::Load();					//ロゴテクスチャの割り当て
	CPlayer::Load();					//プレイヤーのテクスチャ割り当て
	CAnimal::Load();					//おともテクスチャの割り当て
	CBullet::Load();					//弾のテクスチャの割り当て
	CExplosion::Load();				//爆発テクスチャの割り当て
	CEffect::Load();					//エフェクトのテクスチャの割り当て

	//各処理の生成
	CBg::Create();																																	//背景の生成
	CLogo::Create();																																//ロゴ
	CAnimal::Create(D3DXVECTOR3(250.0f, 450.0f, 0.0f), CAnimal::ANIMALTYPE_DOG);				//おとも
	CPlayer::Create(D3DXVECTOR3(200.0f, 430.0f, 0.0f));											//プレイヤー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	CBg::Unload();									//背景のテクスチャの破棄
	CLogo::Unload();								//ロゴのテクスチャの破棄
	CPlayer::Unload();							//プレイヤーのテクスチャの破棄
	CAnimal::Unload();							//おとものテクスチャの破棄
	CBullet::Unload();							//弾テクスチャの破棄
	CExplosion::Unload();						//爆発テクスチャの破棄
	CEffect::Unload();							//エフェクトのテクスチャの破棄

	CScene::ReleaseFadeAll();				//フェード以外のオブジェクトの破棄
}

//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
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

	if (pInputKeyboard->GetPress(DIK_P) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
	{	//エンターキーとジョイコンBボタン押した
		if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
		{
			CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		}
		CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);

		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_GAME);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{
}