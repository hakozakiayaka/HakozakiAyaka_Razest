//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//シーン2D
#include "manager.h"			//マネージャー
#include "input.h"				//入力
#include "player.h"				//プレイヤー
#include "bullet.h"				//弾
#include "animal.h"				//おとも
#include "sound.h"				//サウンド

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(4)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{	//何も書かない
}

//=============================================================================
// プレイヤーの生成
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = NULL;

	//プレイヤークラスの動的確保
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
	}
	if(pPlayer != NULL)
	{
		pPlayer->Init();
		pPlayer->SetPosition(pos);							//位置の設定
		pPlayer->m_bJump = true;									//ジャンプしていない状態にする

		//テクスチャの割り当て
		pPlayer->BindTexture(m_pTexture);
	}

	return pPlayer;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init()
{
	CBullet * pBullet = NULL;

	CScene2D::Init();

	//オブジェクトの設定
	CScene2D::SetObjType(CScene::OBJTYPE_PLAYER);

	//プレイヤーのサイズを設定
	SetSize(70.0f, 70.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	m_pos = CScene2D::GetPosition();								//位置を取得
	int nPatternAnim = CScene2D::GetPatternAnim();		//アニメーションの取得

	//ジョイコンの設定
	XINPUT_STATE state;
	XInputGetState(0, &state);
	XINPUT_KEYSTROKE keystroke;
	XInputGetKeystroke(0, 0, &keystroke);

	//キーボードクラスの呼び出し
	CInputKeyboard * pInputKeyboard = NULL;
	if (pInputKeyboard == NULL)
	{
		pInputKeyboard = CManager::GetInputKeyboard();
	}

	//プレイヤーの移動
	if (pInputKeyboard->GetPress(DIK_A) == true || (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
	{	//キーボードAキー、ジョイコン9スティック←押した
		m_move.x += sinf(D3DX_PI * -0.5f) * PLAYER_SPEED;
		m_move.y += cosf(D3DX_PI * -0.5f) * PLAYER_SPEED;
	}
	if (pInputKeyboard->GetPress(DIK_D) == true || (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
	{	//キーボードDキー、ジョイコン9スティック→押した
		m_move.x += sinf(D3DX_PI * 0.5f) * PLAYER_SPEED;
		m_move.y += cosf(D3DX_PI * 0.5f) * PLAYER_SPEED;
	}

	//ジャンプの処理
	if (m_bJump == false)
	{	//ジャンプしていない状態
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
		{	//スペースキー、ジョイコンAボタン押した
			m_move.y = -PLAYER_JUMP;
			m_bJump = true;							//ジャンプしている状態
		}
	}

	m_move.y += GRAVITY;		//重力加算

	m_pos.x += m_move.x;			//横移動
	m_pos.y += m_move.y;			//落下
	CSound::PlaySound(CSound::SOUND_LABEL_SE_JUMP);

	//慣性
	m_move.x += (0.0f - m_move.x) * PLAYER_INERTIA_SPEED;

	//移動範囲の処理
	if (m_pos.x >= 1000.0f)
	{	//右端行った
		m_pos.x = 1000.0f;
	}
	if (m_pos.x <= 20)
	{	//左端に行った
		m_pos.x = 20;
	}
	if (m_pos.y <= 20)
	{	//上行った
		m_pos.y = 20;
	}
	if (m_pos.y >= PLAYER_FIELD_RANGE)
	{	//下行った
		m_pos.y = PLAYER_FIELD_RANGE;
		m_bJump = false;									//地面に付いたらジャンプしていない状態に戻す
	}

	//設定した位置を反映
	SetPosition(m_pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, PLAYER_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CPlayer::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}