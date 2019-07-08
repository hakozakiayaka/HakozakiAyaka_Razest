//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//シーン2D
#include "manager.h"			//マネージャー
#include "input.h"				//入力
#include "bg.h"					//背景

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	 CBg::m_pTexture[MAX_TEXTURE] = {};		//テクスチャのポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CBg::CBg() : CScene(BG_PRIORITY)
{
	m_bgState = BGSTATE_NONE;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		m_apScene2D[nCntBg] = NULL;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{	//何も書かない
}

//=============================================================================
// 背景の生成
//=============================================================================
CBg *CBg::Create()
{
	CBg *pBg = NULL;

	//背景クラスの動的確保
	if (pBg == NULL)
	{
		pBg = new CBg;
	}

	//背景の初期化処理
	if (pBg != NULL)
	{
		pBg->Init();
	}

	return pBg;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(void)
{
	CManager::MODE BgMode = CManager::GetMode();

	switch (BgMode)
	{
	case CManager::MODE_TITLE:
		if (m_apScene2D[0] == NULL)
		{
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[0]);								//テクスチャの割り当て
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		break;

	case CManager::MODE_TUTORIAL:
		if (m_apScene2D[0] == NULL)
		{	//空
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[1]);					//テクスチャの割り当て
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[1] == NULL)
		{	//山
			m_apScene2D[1] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[1] != NULL)
		{
			m_apScene2D[1]->Init();
			m_apScene2D[1]->BindTexture(m_pTexture[2]);					//テクスチャの割り当て
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[1]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[2] == NULL)
		{	//地面
			m_apScene2D[2] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[2] != NULL)
		{
			m_apScene2D[2]->Init();
			m_apScene2D[2]->BindTexture(m_pTexture[4]);					//テクスチャの割り当て
			m_apScene2D[2]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[2]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[3] == NULL)
		{	//手前の草
			m_apScene2D[3] = new CScene2D(5);
		}
		if (m_apScene2D[3] != NULL)
		{
			m_apScene2D[3]->Init();
			m_apScene2D[3]->BindTexture(m_pTexture[8]);					//テクスチャの割り当て
			m_apScene2D[3]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[3]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[4] == NULL)
		{	//チュートリアル1枚目
			m_apScene2D[4] = new CScene2D(3);
		}
		if (m_apScene2D[4] != NULL)
		{
			m_apScene2D[4]->Init();
			m_apScene2D[4]->BindTexture(m_pTexture[9]);					//テクスチャの割り当て
			m_apScene2D[4]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[4]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[5] == NULL)
		{	//チュートリアル2枚目
			m_apScene2D[5] = new CScene2D(6);
		}
		if (m_apScene2D[5] != NULL)
		{
			m_apScene2D[5]->Init();
			m_apScene2D[5]->BindTexture(m_pTexture[10]);					//テクスチャの割り当て
			m_apScene2D[5]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[5]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		break;

	case CManager::MODE_GAME:
		if (m_apScene2D[0] == NULL)
		{	//空
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[1]);					//テクスチャの割り当て
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[1] == NULL)
		{	//山
			m_apScene2D[1] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[1] != NULL)
		{
			m_apScene2D[1]->Init();
			m_apScene2D[1]->BindTexture(m_pTexture[2]);					//テクスチャの割り当て
			m_apScene2D[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[1]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[2] == NULL)
		{	//地面
			m_apScene2D[2] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[2] != NULL)
		{
			m_apScene2D[2]->Init();
			m_apScene2D[2]->BindTexture(m_pTexture[4]);					//テクスチャの割り当て
			m_apScene2D[2]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[2]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[3] == NULL)
		{	//手前の草
			m_apScene2D[3] = new CScene2D(5);
		}
		if (m_apScene2D[3] != NULL)
		{
			m_apScene2D[3]->Init();
			m_apScene2D[3]->BindTexture(m_pTexture[8]);					//テクスチャの割り当て
			m_apScene2D[3]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[3]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}

		if (m_apScene2D[4] == NULL)
		{	//鬼ヶ島
			m_apScene2D[4] = new CScene2D(4);
		}
		if (m_apScene2D[4] != NULL)
		{
			m_apScene2D[4]->Init();
			m_apScene2D[4]->BindTexture(m_pTexture[11]);					//テクスチャの割り当て
			m_apScene2D[4]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[4]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		break;

	case CManager::MODE_GAMECLEAR:
		if (m_apScene2D[0] == NULL)
		{	//クリア
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[5]);					//テクスチャの割り当て
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
			m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
		break;

	case CManager::MODE_GAMEOVER:
		if (m_apScene2D[0] == NULL)
		{	//オーバー
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[6]);					//テクスチャの割り当て
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
			m_apScene2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}
		break;

	case CManager::MODE_RANKING:
		if (m_apScene2D[0] == NULL)
		{	//オーバー
			m_apScene2D[0] = new CScene2D(BG_PRIORITY);
		}
		if (m_apScene2D[0] != NULL)
		{
			m_apScene2D[0]->Init();
			m_apScene2D[0]->BindTexture(m_pTexture[7]);					//テクスチャの割り当て
			m_apScene2D[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[0]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBg::Uninit(void)
{	//背景破棄
	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		m_apScene2D[nCntBg]->Uninit();
		m_apScene2D[nCntBg] = NULL;
	}

	//オブジェクト（自分自身）の破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBg::Update(void)
{
	CManager::MODE BgMode = CManager::GetMode();
	CInputKeyboard * pInputKeyboard = NULL;								 //キーボードクラスの呼び出し
	//D3DXVECTOR3 pos = CBg::GetPos();
	float nSpeed = 10.0f;

	//ジョイコンの設定
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	if (BgMode == CManager::MODE_TUTORIAL)
	{
		if (pInputKeyboard->GetPress(DIK_LEFT) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && CDirectXInput::GetConnectionJoypad() == true))
		{	//エンターキーとジョイコン十字キー←ボタン押した
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				//CSound::PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);

			m_apScene2D[5]->BindTexture(m_pTexture[10]);					//テクスチャの割り当て
			m_apScene2D[5]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			m_apScene2D[5]->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		if (BgMode == CManager::MODE_GAME)
		{
			m_BgMove++;

			m_apScene2D[1]->SetBgMove(m_BgMove, 0.00005f);				//空
			m_apScene2D[2]->SetBgMove(m_BgMove, 0.0005f);				//山
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
}

//=============================================================================
// 描画処理
//=============================================================================
void CBg::Draw(void)
{
}

#if 1
//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BG_TITLE, &m_pTexture[0]);							//タイトル
	D3DXCreateTextureFromFile(pDevice, BG_SKY, &m_pTexture[1]);								//空
	D3DXCreateTextureFromFile(pDevice, BG_MOUNTAIN, &m_pTexture[2]);					//山
	D3DXCreateTextureFromFile(pDevice, BG_FOREST, &m_pTexture[3]);						//草
	D3DXCreateTextureFromFile(pDevice, BG_FIELD, &m_pTexture[4]);							//地面
	D3DXCreateTextureFromFile(pDevice, BG_GAMECLEAR, &m_pTexture[5]);				//ゲームクリア
	D3DXCreateTextureFromFile(pDevice, BG_GAMEOVER, &m_pTexture[6]);					//ゲームオーバー
	D3DXCreateTextureFromFile(pDevice, BG_RANKING, &m_pTexture[7]);						//ランキング
	D3DXCreateTextureFromFile(pDevice, BG_FRONTWEED, &m_pTexture[8]);				//手前の草
	D3DXCreateTextureFromFile(pDevice, BG_TUTORIAL01, &m_pTexture[9]);				//チュートリアル1枚目
	D3DXCreateTextureFromFile(pDevice, BG_TUTORIAL02, &m_pTexture[10]);				//チュートリアル2枚目
	D3DXCreateTextureFromFile(pDevice, BG_STONE, &m_pTexture[11]);						//鬼ヶ島

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CBg::Unload(void)
{
	// テクスチャの破棄
	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}
}
#endif