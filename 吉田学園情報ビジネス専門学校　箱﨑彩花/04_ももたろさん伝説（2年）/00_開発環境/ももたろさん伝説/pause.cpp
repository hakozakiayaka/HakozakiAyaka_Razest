//=============================================================================
//
// ポーズ処理 [pause.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//シーン2D
#include "manager.h"			//マネージャー
#include "input.h"				//入力
#include "fade.h"					//フェード
#include "pause.h"				//背景
#include "sound.h"				//サウンド

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	 CPause::m_pTexture[PAUSE_TEXTURE] = {};		//テクスチャのポインタ
CScene2D * CPause::m_apScene2D[PAUSE_TEXTURE] = {};						//ポリゴン管理
bool CPause::m_bPause = false;																	//表示していない状態にする

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause() : CScene(PAUSE_PRIORITY)
{
	m_PauseState = PAUSESTATE_NONE;
	m_PauseColor = PAUSECOLOR_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{	//何も書かない
}

//=============================================================================
// ポリゴンの生成
//=============================================================================
CPause *CPause::Create()
{
	CPause * pPause = NULL;

	//ポーズクラスの動的確保
	if (pPause == NULL)
	{
		pPause = new CPause;
	}

	if (pPause != NULL)
	{
		pPause->Init();																	//初期化
		pPause->SetObjType(CScene::OBJTYPE_PAUSE);			//オブジェクトタイプの設定
	}

	//2回目以降最初の画面がポーズにならないようにする
	m_bPause = false;

	return pPause;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPause::Init(void)
{
	for (int nCntPause = 0; nCntPause < PAUSE_TEXTURE; nCntPause++)
	{
		if (nCntPause == 0)
		{	//画面全体が半透明になる（マスク）
			if (m_apScene2D[nCntPause] == NULL)
			{
				m_apScene2D[nCntPause] = new CScene2D(PAUSE_PRIORITY);
			}
			if (m_apScene2D[nCntPause] != NULL)
			{
				m_apScene2D[nCntPause]->Init();
				m_apScene2D[nCntPause]->SetObjType(CScene::OBJTYPE_PAUSE);				//オブジェクトタイプの設定
				m_apScene2D[nCntPause]->BindTexture(m_pTexture[nCntPause]);					//テクスチャの割り当て
				m_apScene2D[nCntPause]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//サイズ設定
				m_apScene2D[nCntPause]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));			//色の設定
			}
		}
		else if (nCntPause == 1)
		{	//ポーズメニューの背景
			if (m_apScene2D[nCntPause] == NULL)
			{
				m_apScene2D[nCntPause] = new CScene2D(PAUSE_PRIORITY);
			}
			if (m_apScene2D[nCntPause] != NULL)
			{
				m_apScene2D[nCntPause]->Init();
				m_apScene2D[nCntPause]->SetObjType(CScene::OBJTYPE_PAUSE);
				m_apScene2D[nCntPause]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
				m_apScene2D[nCntPause]->BindTexture(m_pTexture[nCntPause]);																				//テクスチャの割り当て
				m_apScene2D[nCntPause]->SetSize(400.0f, 400.0f);																										//サイズ設定
			}
		}
		else
		{	//つづける、やりなおす、タイトルに戻る
			if (m_apScene2D[nCntPause] == NULL)
			{
				m_apScene2D[nCntPause] = new CScene2D(PAUSE_PRIORITY);
			}
			if (m_apScene2D[nCntPause] != NULL)
			{
				m_apScene2D[nCntPause]->Init();
				m_apScene2D[nCntPause]->SetObjType(CScene::OBJTYPE_PAUSE);
				m_apScene2D[nCntPause]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 235.0f + (125.0f * (nCntPause - 2)), 0.0f));
				m_apScene2D[nCntPause]->BindTexture(m_pTexture[nCntPause]);																				//テクスチャの割り当て
				m_apScene2D[nCntPause]->SetSize(200.0f, 100.0f);																											//サイズ設定
			}
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPause::Uninit(void)
{	//背景破棄
	for (int nCntPause = 0; nCntPause < PAUSE_TEXTURE; nCntPause++)
	{
		m_apScene2D[nCntPause]->Uninit();
		m_apScene2D[nCntPause] = NULL;
	}

	//オブジェクト（自分自身）の破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPause::Update(void)
{
	CInputKeyboard * pInputKeyboard = NULL;
	CFade::FADE fade = CFade::GetFade();

	//ジョイコンの設定
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	if (m_bPause == true)
	{
		if (pInputKeyboard->GetTrigger(DIK_DOWN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && CDirectXInput::GetConnectionJoypad() == true) || (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{	// キーボード↓キー(下)、ジョイコン十字キー↓、ジョイコン9スティック↓押した
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_SelectNum = (m_SelectNum + 1) % 3;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		if (pInputKeyboard->GetTrigger(DIK_UP) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP && CDirectXInput::GetConnectionJoypad() == true) || (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{	// キーボード↑キー(上)、ジョイコン十字キー↑、ジョイコン9スティック↑押した
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_SelectNum = (m_SelectNum + 2) % 3;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}

		if (m_SelectNum == 0)
		{	//つづける
			m_PauseColor = PAUSECOLOR_CONTINUE;

			// 決定キーが押されたかどうか
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{	//エンターキーとジョイコンBボタン押した
				CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					m_PauseState = PAUSESTATE_CONTINUE;
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
		}
		if (m_SelectNum == 1)
		{	//やりなおす
			m_PauseColor = PAUSECOLOR_RETRY;

			// 決定キーが押されたかどうか
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{	//エンターキーとジョイコンBボタン押した
				CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					if (fade != CFade::FADE_OUT)
					{
						m_PauseState = PAUSESTATE_RETRY;
					}
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
		}
		if (m_SelectNum == 2)
		{	//タイトルに戻る
			m_PauseColor = PAUSECOLOR_QUIT;

			// 決定キーが押されたかどうか
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_B && CDirectXInput::GetConnectionJoypad() == true))
			{	//エンターキーとジョイコンBボタン押した
				CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
				if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
				{
					if (fade != CFade::FADE_OUT)
					{
						m_PauseState = PAUSESTATE_QUIT;
					}
				}
				CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
			}
		}

		switch (m_PauseState)
		{	//ポーズのステート管理
		case PAUSESTATE_NONE:
			break;

		case PAUSESTATE_CONTINUE:
			m_PauseState = PAUSESTATE_NONE;
			SetPause(false);
			break;

		case PAUSESTATE_RETRY:
			m_PauseState = PAUSESTATE_NONE;

			if (fade != CFade::FADE_OUT)
			{	// フェードモード設定
				CFade::SetFade(CManager::MODE_GAME);
			}
			break;

		case PAUSESTATE_QUIT:
			m_PauseState = PAUSESTATE_NONE;

			if (fade != CFade::FADE_OUT)
			{	// フェードモード設定
				CFade::SetFade(CManager::MODE_TITLE);
			}
			break;
		}

		switch (m_PauseColor)
		{	//メニュー選択時の色管理
		case PAUSECOLOR_NONE:
			break;

		case PAUSECOLOR_CONTINUE:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			break;

		case PAUSECOLOR_RETRY:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			break;

		case PAUSECOLOR_QUIT:
			m_apScene2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apScene2D[4]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPause::Draw(void)
{
}

//=============================================================================
// ポーズの設定
//=============================================================================
void CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
}

#if 1
//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CPause::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "", &m_pTexture[0]);												//ゲーム画面を半透明
	D3DXCreateTextureFromFile(pDevice, PAUSE_PAUSEMENU, &m_pTexture[1]);			//メニューの背景
	D3DXCreateTextureFromFile(pDevice, PAUSE_CONTINUE, &m_pTexture[2]);				//つづける
	D3DXCreateTextureFromFile(pDevice, PAUSE_RETRY, &m_pTexture[3]);						//やりなおす
	D3DXCreateTextureFromFile(pDevice, PAUSE_QUIT, &m_pTexture[4]);							//タイトルに戻る

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CPause::Unload(void)
{
	// テクスチャの破棄
	for (int nCntPause = 0; nCntPause < PAUSE_TEXTURE; nCntPause++)
	{
		if (m_pTexture[nCntPause] != NULL)
		{
			m_pTexture[nCntPause]->Release();
			m_pTexture[nCntPause] = NULL;
		}
	}
}
#endif