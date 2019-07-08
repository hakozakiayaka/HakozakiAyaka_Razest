//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "input.h"			//入力

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;
bool CDirectXInput::m_bConnectionJoypad = false;
CDirectXInput::InputJoyState CDirectXInput::m_nState = INPUT_JOYSTATE_NOTPUSH;

//=============================================================================
// コンストラクタ
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの生成
	if (m_pInput == NULL)
	{	//本体がつくられていなかったら生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CInput::Uninit(void)
{
	// 入力デバイス(キーボード)の開放
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	//キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// コンストラクタ	キーボード
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//キーボード情報のクリア
	m_aKeyState[0];
	m_aKeyStateTrigger[0];
}

//=============================================================================
// デストラクタ		キーボード
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{	//何も書かない
}

//=============================================================================
// 初期化処理			キーボード
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hIIstance, HWND hWnd)
{
	//本体の生成の呼び出し
	CInput::Init(hIIstance, hWnd);

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// 終了処理				キーボード
//=============================================================================
void CInputKeyboard::Uninit(void)
{	//本体の終了処理の呼び出し
	CInput::Uninit();
}

//=============================================================================
// 更新処理				キーボード
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//キーボードの入力情報保存
		}
	}
	else
	{
		m_pDevice->Acquire();	//キーボードへのアクセス権を獲得
	}
}

//=============================================================================
// キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CDirectXInput::CDirectXInput()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CDirectXInput::~CDirectXInput()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CDirectXInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//親クラスの初期化処理
	CInput::Init(hInstance, hWnd);

	m_nState = INPUT_JOYSTATE_NOTPUSH;
	m_bConnectionJoypad = false;

	DWORD dwResult;
	for (DWORD dCnt = 0; dCnt < MAX_CONTROLLERS; dCnt++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// XInputからコントローラの状態を取得する
		dwResult = XInputGetState(dCnt, &state);

		if (dwResult == ERROR_SUCCESS)
		{
#ifdef _DEBUG
			//MessageBox(0, "コントローラーが接続されています", "", MB_OK);
#endif // _DEBUG
			// デッドゾーンの設定
			if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbLX = 0;
				state.Gamepad.sThumbLY = 0;
			}

			if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
				(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			{
				state.Gamepad.sThumbRX = 0;
				state.Gamepad.sThumbRY = 0;
			}

			m_bConnectionJoypad = true;
		}
		else
		{
#ifdef _DEBUG
			//MessageBox(0, "コントローラーが接続されていません", "", MB_OK);
#endif // _DEBUG

			m_bConnectionJoypad = false;
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CDirectXInput::Uninit(void)
{
	XInputEnable(false);

	//親クラスの終了処理
	CInput::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CDirectXInput::Update(void)
{
}

//=============================================================================
// インプットの状態の設定
//=============================================================================
void CDirectXInput::SetInputJoyState(CDirectXInput::InputJoyState state)
{
	m_nState = state;
}