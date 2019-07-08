//=============================================================================
//
// όΝ [input.cpp]
// Author :  ϊ±ΚΤ
//
//=============================================================================
#include "input.h"

//=============================================================================
// }Nθ`
//=============================================================================
#define	NUM_KEY_MAX			(256)	// L[ΜΕε

//=============================================================================
// O[oΟ
//=============================================================================
LPDIRECTINPUT8 g_pInput = NULL;								//DirectInputIuWFNgΦΜ|C^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	//όΝfoCXiL[{[hjΦΜ|C^
BYTE g_aKeyState[NUM_KEY_MAX];							//L[{[hόΝξρivXξρj
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];					//L[{[hΜόΝξρigK[ξρj

//=============================================================================
// L[{[hΜϊ»
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputIuWFNgΜΆ¬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	// όΝfoCX(L[{[h)ΜΆ¬
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// f[^tH[}bgπέθ
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// ¦²[hπέθ
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// L[{[hΦΜANZX πlΎ(όΝ§δJn)
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// L[{[hΜIΉ
//=============================================================================
void UninitKeyboard(void)
{
	// όΝfoCX(L[{[h)ΜJϊ
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//L[{[hΦΜANZX πϊό
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// DirectInputIuWFNgΜJϊ
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================================================
// L[{[hΜXV
//=============================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	// όΝfoCX©ηf[^πζΎ
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			g_aKeyState[nCntKey] = aKeyState[nCntKey];	//L[{[hΜόΝξρΫΆ
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();	//L[{[hΦΜANZX πlΎ
	}
}

//=============================================================================
// L[{[hΜόΝξρ(vXξρ)πζΎ
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//=============================================================================
// L[{[hΜόΝξρ(gK[ξρ)πζΎ
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
