//=============================================================================
//
//入力処理 [input.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _INPUT_H_		//二重インクルード防止
#define _INPUT_H_

#include	"main.h"		//メイン

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX					(256)				// キーの最大数
#define MAX_CONTROLLERS         (1)					//コントローラーの最大数
#define NUM_JOYKEY_MAX		     (128)				//キーの最大数

//*****************************************************************************
// 入力処理のクラス
//*****************************************************************************
class CInput
{
public:
	CInput();																									//コンストラクタ
	virtual ~CInput();																					//デストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);				//初期化処理
	virtual void Uninit(void);																			//終了処理
	virtual void Update(void) = 0;																	//更新処理（純粋仮想関数）

protected:
	LPDIRECTINPUTDEVICE8		m_pDevice;												//入力処理のデバイスを扱う変数

	//静的メンバ変数
	static LPDIRECTINPUT8			m_pInput;												//オブジェクトの本体
};

//*****************************************************************************
// キーボードクラス
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();																					//コンストラクタ
	~CInputKeyboard();																				//デストラクタ
	HRESULT Init(HINSTANCE hIIstance, HWND hWnd);							//初期化処理
	void Uninit(void);																						//終了処理
	void Update(void);																					//更新処理
	bool GetPress(int nKey);																			//キーボードの入力情報(プレス情報)を取得
	bool GetTrigger(int nKey);																		//キーボードの入力情報(トリガー情報)を取得

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
};

//*****************************************************************************
// コントローラークラス
//*****************************************************************************
class CDirectXInput : public CInput
{
public:
	typedef enum
	{//ボタンの押し状況
		INPUT_JOYSTATE_NOTPUSH = 0,
		INPUT_JOYSTATE_PUSH,
		INPUT_JOYSTATE_NONE,
	}InputJoyState;

	CDirectXInput();
	~CDirectXInput();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	static void SetInputJoyState(InputJoyState state);
	static bool GetConnectionJoypad(void) { return m_bConnectionJoypad; }
	static InputJoyState GetInputJoyState(void) { return m_nState; }

private:
	static InputJoyState m_nState;											//ジョイパッドの状態
	static bool m_bConnectionJoypad;										  //ジョイパッドの接続状態
	LPDIRECTINPUTDEVICE8 m_pDevJoyPad = NULL;           //入力デバイス(ジョイパッド)へのポインタ
	BYTE m_aJoyKeyState[NUM_JOYKEY_MAX];					  //ジョイパッドの入力情報(プレス情報)
	BYTE m_aJoyKeyStateTrigger[NUM_JOYKEY_MAX];         //ジョイパッドの入力情報(トリガー情報)
};

#endif