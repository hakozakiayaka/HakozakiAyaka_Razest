//===============================================================================
//
// DirectX^ [main.cpp]
// Author :  ú±ÊÔ
//
//===============================================================================
#include "main.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "fade.h"
#include "sound.h"

//===============================================================================
// }Nè`
//===============================================================================
#define CLASS_NAME			"WindowClass"		// EChENXÌ¼O
#define WINDOW_NAME	" ­µåñ°[Þ"		// EChEÌ¼O(LvV¼)

//===============================================================================
// vg^Cvé¾
//===============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);		//I¹
void Update(void);	//XV
void Draw(void);		//`æ

//===============================================================================
// O[oÏ
//===============================================================================
LPDIRECT3D9 g_pD3D = NULL;								//DirectX3DIuWFNgÖÌ|C^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		//DirectX3DfoCXÌ|C^
MODE g_mode = MODE_TITLE;									//»ÝÌ[h

//===============================================================================
// CÖ
//===============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;	//»Ý
	DWORD dwExecLastTime;	//ÅãÉµ½
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();

	// EBhENXÌo^
	RegisterClassEx(&wcex);

	//wèµ½NCAgÌæðmÛ·é½ßÉKvÈEChEÀWðvZ
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// EBhEÌ¶¬
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	// ú»(EBhEð¶¬µÄ©çs¤)
	if (FAILED(Init(hInstance, hWnd, TRUE)))		//FALSEÅtXN[
	{	//¸sµ½ç
		return -1;
	}

	// EChEÌ\¦(ú»ÌãÉs¤)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// bZ[W[v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// bZ[Wðæ¾µÈ©Á½ê"0"ðÔ·
		{// WindowsÌ
			if (msg.message == WM_QUIT)
			{// "WM_QUIT"bZ[WªçêÄ«½ç[vð²¯é
				break;
			}
			else
			{
				// bZ[WÌ|óÆo
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXÌ
			timeBeginPeriod(1);
			dwCurrentTime = 0;								//ú»·é
			dwCurrentTime = timeGetTime();			//»Ýðæ¾
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;	//µ½ðÛ¶

				// XV
				Update();
				// `æ
				Draw();
			}
		}
	}

	// I¹
	Uninit();

	//ªð\ðß·
	timeEndPeriod(1);

	// EBhENXÌo^ðð
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//===============================================================================
// EChEvV[W
//===============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		// "WM_QUIT"bZ[Wðé
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			// EBhEðjü·é("WM_DESTROY"bZ[Wðé)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// ùèÌðÔ·
}

//===============================================================================
// ú»
//===============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;					//fBXvC[h
	D3DPRESENT_PARAMETERS d3dpp;	//v[e[Vp[^[

	// Direct3DIuWFNgÌ¶¬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// »ÝÌfBXvC[hðæ¾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// foCXÌv[e[Vp[^ÌÝè
	ZeroMemory(&d3dpp, sizeof(d3dpp));														// [Nð[NA
	d3dpp.BackBufferWidth = SCREEN_WIDTH;												// Q[æÊTCY()
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;											// Q[æÊTCY(³)
	d3dpp.BackBufferFormat = d3ddm.Format;												// obNobt@Ì`®
	d3dpp.BackBufferCount = 1;																		// obNobt@Ì
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;									// _uobt@ÌØèÖ¦(fMÉ¯ú)
	d3dpp.EnableAutoDepthStencil = TRUE;													// fvXobt@(yobt@)ÆXeVobt@ðì¬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;										// fvXobt@ÆµÄ16bitðg¤
	d3dpp.Windowed = bWindow;																	// EBhE[h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// tbV[g(»ÝÌ¬xÉí¹é)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// C^[o(VSyncðÒÁÄ`æ)

	// Direct3DfoCXÌ¶¬
	// [foCXì¬§ä]<`æ>Æ<¸_>ðn[hEFAÅsÈ¤
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,				// fBXvCA_v^
		D3DDEVTYPE_HAL,																			// foCX^Cv
		hWnd,																									// tH[JX·éEChEÖÌnh
		D3DCREATE_HARDWARE_VERTEXPROCESSING,							// foCXì¬§äÌgÝí¹
		&d3dpp,																								// foCXÌv[e[Vp[^
		&g_pD3DDevice)))																				// foCXC^[tF[XÖÌ|C^
	{
		// ãLÌÝèª¸sµ½ç
		// [foCXì¬§ä]<`æ>ðn[hEFAÅs¢A<¸_>ÍCPUÅsÈ¤
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,			// fBXvCA_v^
			D3DDEVTYPE_HAL,																		// foCX^Cv
			hWnd,																								// tH[JX·éEChEÖÌnh
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,							// foCXì¬§äÌgÝí¹
			&d3dpp,																							// foCXÌv[e[Vp[^
			&g_pD3DDevice)))																			// foCXC^[tF[XÖÌ|C^
		{
			// ãLÌÝèª¸sµ½ç
			// [foCXì¬§ä]<`æ>Æ<¸_>ðCPUÅsÈ¤
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,		// fBXvCA_v^
				D3DDEVTYPE_REF,																	// foCX^Cv
				hWnd,																							// tH[JX·éEChEÖÌnh
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,						// foCXì¬§äÌgÝí¹
				&d3dpp,																						// foCXÌv[e[Vp[^
				&g_pD3DDevice)))																		// foCXC^[tF[XÖÌ|C^
			{
				return E_FAIL;
			}
		}
	}
	//_[Xe[gÌÝè
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//JOÌÝèÆ ÊðJO

	//eNX`Xe[WXe[gÌÝè
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//At@uhÌÝè
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//TEhÌú»
	InitSound(hWnd);
	//L[{[hÌú»
	InitKeyboard(hInstance,hWnd);
	//tF[hÌÝè
	InitFade(g_mode);
	//[hÌÝè
	SetMode(g_mode);

	return S_OK;
}

//===============================================================================
// I¹
//===============================================================================
void Uninit(void)
{
	//TEhÌI¹
	UninitSound();
	//L[{[hÌI¹
	UninitKeyboard();
	//^CgæÊÌI¹
	UninitTitle();
	//`[gAæÊÌI¹
	UninitTutorial();
	//Q[æÊÌI¹
	UninitGame();
	//UgæÊÌI¹
	UninitResult();
	//tF[hÌI¹
	UninitFade();

	// Direct3DfoCXÌJú
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3DIuWFNgÌJú
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//===============================================================================
// XV
//===============================================================================
void Update(void)
{
	//L[{[hÌXV
	UpdateKeyboard();

	//L[{[hÌXV
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_TUTORIAL:
		UpdateTutorial();
		break;

	case MODE_GAME:
		UpdateGame();
		break;

	case MODE_RESULT:
		UpdateResult();
		break;
	}

	//tF[hÌXV
	UpdateFade();
}

//===============================================================================
// `æ
//===============================================================================
void Draw(void)
{
	// obNobt@yobt@ÌNA
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//`æÌJn
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_TUTORIAL:
			DrawTutorial();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RESULT:
			DrawResult();
			break;
		}

		//tF[hÌ`æ
		DrawFade();

		// `æÌI¹
		g_pD3DDevice->EndScene();
	}

	// obNobt@Ætgobt@ÌüêÖ¦
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===============================================================================
//foCXÌæ¾
//===============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//===============================================================================
//[hÌÝè
//===============================================================================
void SetMode(MODE mode)
{
	//Xe[Wðæ¾
	GAMESTAGE pStage;
	pStage = GetGameStage();

	//Q[ÌóÔðæ¾
	GAMESTATE pGame;
	pGame = GetGameState();

	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		StopSound(SOUND_LABEL_BGM000);
		break;

	case MODE_TUTORIAL:
		UninitTutorial();
		StopSound(SOUND_LABEL_BGM001);
		break;

	case MODE_GAME:
		UninitGame();
		StopSound(SOUND_LABEL_BGM002);
		StopSound(SOUND_LABEL_BGM003);
		break;

	case MODE_RESULT:
		UninitResult();
		StopSound(SOUND_LABEL_BGM006);
		StopSound(SOUND_LABEL_BGM005);

		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		PlaySound(SOUND_LABEL_BGM000);
		break;

	case MODE_TUTORIAL:
		InitTutorial();
		PlaySound(SOUND_LABEL_BGM001);
		break;

	case MODE_GAME:
		InitGame();
		if (pStage == GAMESTAGE_SELECT)
		{	//IðæÊ
			PlaySound(SOUND_LABEL_BGM002);
		}
		else if (pStage == GAMESTAGE1 || pStage == GAMESTAGE2)
		{	//Xe[W1ÆXe[W2
			PlaySound(SOUND_LABEL_BGM003);
		}
		break;

	case MODE_RESULT:
		InitResult();
		if (pGame == GAMESTATE_CLEAR)
		{
			PlaySound(SOUND_LABEL_BGM006);
		}
		else if (pGame == GAMESTATE_OVER)
		{
			PlaySound(SOUND_LABEL_BGM005);
		}
		break;
	}

	g_mode = mode;
}

//===============================================================================
//[hÌæ¾
//===============================================================================
MODE GetMode(void)
{
	return g_mode;
}