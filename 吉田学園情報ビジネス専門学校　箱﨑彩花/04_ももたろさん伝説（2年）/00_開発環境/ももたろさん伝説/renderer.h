//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _RENDERER_H_		//二重インクルード防止
#define _RENDERER_H_

#include	"main.h"				//メイン

//*****************************************************************************
// レンダリングクラス
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);													//初期化処理
	void Uninit(void);																								//終了処理
	void Update(void);																							//更新処理
	void Draw(void);																								//描画処理
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }				//デバイスの取得

private:
	//デバックのみ有効
#ifdef _DEBUG
	void DrawFPS(void);																						//FPSの描画
#endif

	//メンバ変数
	LPDIRECT3D9									m_pD3D;												// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9					m_pD3DDevice;									// Deviceオブジェクト(描画に必要)

	//デバックのみ有効
#ifdef _DEBUG
	LPD3DXFONT									m_pFont;												// フォントへのポインタ
#endif
};

#endif