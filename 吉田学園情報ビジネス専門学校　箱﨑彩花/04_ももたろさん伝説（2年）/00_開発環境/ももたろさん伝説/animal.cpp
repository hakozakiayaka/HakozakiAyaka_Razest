//=============================================================================
//
// おとも処理 [animal.cpp]
// Author : 箱﨑彩花
//
//=============================================================================
#include "main.h"				//メイン
#include "scene.h"				//シーン
#include "renderer.h"			//レンダリング
#include "scene2D.h"			//シーン2D
#include "manager.h"			//マネージャー
#include "input.h"				//入力
#include "animal.h"				//おとも
#include "bullet.h"				//弾
#include "player.h"				//プレイヤー
#include "bg.h"					//背景
#include "fade.h"					//フェード
#include "score.h"				//スコア
#include "sound.h"				//サウンド

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9 CAnimal::m_pTexture[MAX_ANIMALTEX] = {};
CAnimal::ANIMALTYPE CAnimal::m_animalType = CAnimal::ANIMALTYPE_DOG;			//最初のおとも
CLife * CAnimal::m_pLife[ANIMAL_LIFE] = {};																	//ライフ

//=============================================================================
// コンストラクタ
//=============================================================================
CAnimal::CAnimal(int nPriority) : CScene2D(4)
{
	m_animalState = ANIMALSTATE_NONE;					//通常状態
	m_BulletType = CBullet::BULLETTYPE_NONE;			//弾の種類
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//移動量
	m_nCntState = 0;														//状態カウンター
}

//=============================================================================
// デストラクタ
//=============================================================================
CAnimal::~CAnimal()
{	//何も書かない
}

//=============================================================================
// おともの生成
//=============================================================================
CAnimal *CAnimal::Create(D3DXVECTOR3 pos, ANIMALTYPE animalType)
{
	CAnimal * pAnimal = NULL;

	//おともクラスの動的確保
	if (pAnimal == NULL)
	{
		pAnimal = new CAnimal;
	}
	if(pAnimal != NULL)
	{
		pAnimal->Init();
		pAnimal->SetPosition(pos);												//位置の設定
		pAnimal->m_bJump = true;												//ジャンプしている状態
		pAnimal->SetAnimation(PATTERN_ANIM, 0);					//アニメーションの設定
		pAnimal->m_nLife = ANIMAL_LIFE;									//ライフの設定
		pAnimal->m_animalType = animalType;							//おともの種類

		if (pAnimal->m_animalType == ANIMALTYPE_DOG)
		{	//イヌ、テクスチャの割り当て
			pAnimal->BindTexture(m_pTexture[0]);
		}
		if (pAnimal->m_animalType == ANIMALTYPE_MONKEY)
		{	//サル、テクスチャの割り当て
			pAnimal->BindTexture(m_pTexture[1]);
		}
		if (pAnimal->m_animalType == ANIMALTYPE_KIJI)
		{	//キジ、テクスチャの割り当て
			pAnimal->BindTexture(m_pTexture[2]);
		}
	}

	return pAnimal;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CAnimal::Init()
{
	CManager::MODE mode = CManager::GetMode();			//モードの取得

	//初期化
	CScene2D::Init();

	//テクスチャの割り当て
	CLife::Load();

	//オブジェクトの設定
	CScene2D::SetObjType(CScene::OBJTYPE_ANIMAL);

	//おとものサイズを設定
	SetSize(70.0f, 70.0f);

	if (mode == CManager::MODE_GAME)
	{	//ゲームの時だけライフ生成
		for (int nCntLife = 0; nCntLife < ANIMAL_LIFE; nCntLife++)
		{	//ライフの生成
			m_pLife[nCntLife] = CLife::Create(D3DXVECTOR3(100.0f + (100.0f * nCntLife), 50.0f, 0.0f), nCntLife);
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CAnimal::Uninit(void)
{
	CLife::Unload();						//ライフのテクスチャの破棄

	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CAnimal::Update(void)
{
	m_pos = CScene2D::GetPosition();										//位置
	int nPatternAnim = CScene2D::GetPatternAnim();				//アニメーション
	CFade::FADE fade = CFade::GetFade();									//フェード
	CManager::MODE mode = CManager::GetMode();				//モードの取得

	float nSpeed = 1.0f;																//タイトル画面で使用（スピード）

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

	switch (m_animalState)
	{	//おとものステート
	case ANIMALSTATE_NONE:
		break;

	case ANIMALSTATE_DAMAGE:
		m_nCntState--;
		if (m_nCntState <= 0)
		{
			m_pLife[m_nLife]->Uninit();
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));			//光ってる状態から透明に戻す
			m_animalState = ANIMALSTATE_NONE;				//通常状態に戻す
		}
		break;

	case ANIMALSTATE_DEATH:
		m_pLife[m_nLife]->Uninit();
		if (fade != CFade::FADE_OUT)
		{
			CFade::SetFade(CManager::MODE_GAMEOVER);
		}
		break;
	}

	//*****************************************************************************
	// アニメーション処理
	//*****************************************************************************
	m_nCntAnim++;			//カウンターを加算

	if ((m_nCntAnim % ANIMAL_ANIMSPEED) == 0)
	{
		m_nPatternAnim++;		//パターンNoを更新
		CScene2D::SetAnimation(PATTERN_ANIM, m_nPatternAnim);
	}

	//*****************************************************************************
	// タイトルでキジ飛ばす
	//*****************************************************************************
	if (mode == CManager::MODE_TITLE)
	{
		//移動量にスピードを加算
		m_move.x += nSpeed;

		if (m_pos.x >= SCREEN_WIDTH)
		{	//右端までいった
			m_pos.x = -30.0f;
		}

		if (m_animalType != ANIMALTYPE_KIJI)
		{
			m_move.y += ANIMAL_GRAVITY;		//重力加算
			m_pos.y += m_move.y;						//落下
			CSound::PlaySound(CSound::SOUND_LABEL_SE_SHOT);
		}
		m_pos.x += m_move.x;			//横移動

		//慣性
		m_move.x += (0.0f - m_move.x) * ANIMAL_INERTIA_SPEED;
	}

	//*****************************************************************************
	// おともの切り替え処理
	//*****************************************************************************
	if (mode == CManager::MODE_GAME || mode == CManager::MODE_TUTORIAL)
	{
		//おとも切り替え処理（ジョイコン）
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && CDirectXInput::GetConnectionJoypad() == true)
		{	//ジョイコンRB/5押した
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_nSelect = (m_nSelect + 1) % 3;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && CDirectXInput::GetConnectionJoypad() == true)
		{	//ジョイコンLB/5押した
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				m_nSelect = (m_nSelect + 2) % 3;
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}

		//おとも切り替え処理（キーボード）
		if (pInputKeyboard->GetTrigger(DIK_F1) == true)
		{	//イヌ
			m_nSelect = 0;
		}
		if (pInputKeyboard->GetTrigger(DIK_F2) == true)
		{	//サル
			m_nSelect = 1;
		}
		if (pInputKeyboard->GetTrigger(DIK_F3) == true)
		{	//キジ
			m_nSelect = 2;
		}

		if (m_nSelect == 0)
		{
			m_animalType = ANIMALTYPE_DOG;
			m_BulletType = CBullet::BULLETTYPE_DOG;
			BindTexture(m_pTexture[0]);
		}
		if (m_nSelect == 1)
		{
			m_animalType = ANIMALTYPE_MONKEY;
			m_BulletType = CBullet::BULLETTYPE_MONKEY;
			BindTexture(m_pTexture[1]);
		}
		if (m_nSelect == 2)
		{
			if (mode == CManager::MODE_TUTORIAL)
			{	//チュートリアル
				m_pos.y = 320.0f;
			}
			if (mode == CManager::MODE_GAME)
			{	//ゲーム
				m_pos.y = 150.0f;
			}
			m_animalType = ANIMALTYPE_KIJI;
			m_BulletType = CBullet::BULLETTYPE_KIJI;
			BindTexture(m_pTexture[2]);
		}

		//弾発射の処理
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_X && CDirectXInput::GetConnectionJoypad() == true))
		{	//エンターキー、ジョイコンXボタン押した
			if (CDirectXInput::GetInputJoyState() == CDirectXInput::INPUT_JOYSTATE_NOTPUSH)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SHOT);
				CBullet::Create(m_pos, BULLET_SPEED, m_BulletType);
			}
			CDirectXInput::SetInputJoyState(CDirectXInput::INPUT_JOYSTATE_PUSH);
		}

		//おともの移動
		if (pInputKeyboard->GetPress(DIK_A) == true || (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{	//キーボードAキー、ジョイコン9スティック←押した
			m_move.x += sinf(D3DX_PI * -0.5f) * ANIMAL_SPEED;
			m_move.y += cosf(D3DX_PI * -0.5f) * ANIMAL_SPEED;
		}
		if (pInputKeyboard->GetPress(DIK_D) == true || (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && CDirectXInput::GetConnectionJoypad() == true))
		{	//キーボードDキー、ジョイコン9スティック→押した
			m_move.x += sinf(D3DX_PI * 0.5f) * ANIMAL_SPEED;
			m_move.y += cosf(D3DX_PI * 0.5f) * ANIMAL_SPEED;
		}

		if (m_animalType != ANIMALTYPE_KIJI)
		{
			m_move.y += ANIMAL_GRAVITY;		//重力加算
			m_pos.y += m_move.y;		//落下
		}
		m_pos.x += m_move.x;			//横移動

		//慣性
		m_move.x += (0.0f - m_move.x) * ANIMAL_INERTIA_SPEED;

		//ジャンプの処理
		if (m_animalType == ANIMALTYPE_DOG || m_animalType == ANIMALTYPE_MONKEY)
		{	//イヌとサルの時だけジャンプ
			if (m_bJump == false)
			{	//ジャンプしていない状態
				if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && CDirectXInput::GetConnectionJoypad() == true))
				{	//スペースキー、ジョイコンAボタン押した
					m_move.y = -ANIMAL_JUMP;
					m_bJump = true;							//ジャンプしている状態
				}
				CSound::PlaySound(CSound::SOUND_LABEL_SE_JUMP);
			}
		}

		//移動範囲の処理
		if (m_pos.x >= 1000.0f)
		{	//右端行った
			m_pos.x = 1000.0f;
		}
		if (m_pos.x <= LEFT_WIDTH)
		{	//左端に行った
			m_pos.x = LEFT_WIDTH;
		}
		if (m_pos.y <= 20)
		{	//上行った
			m_pos.y = 20;
		}
		if (m_pos.y >= ANIMAL_FIELD_RANGE)
		{	//下行った
			m_pos.y = ANIMAL_FIELD_RANGE;
			m_bJump = false;									//地面に付いたらジャンプしていない状態に戻す
		}
	}

	//設定した位置を反映
	SetPosition(m_pos);

	if (m_animalState == ANIMALSTATE_DEATH)
	{
		Uninit();		//おともの破棄
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CAnimal::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ダメージ処理
//=============================================================================
void CAnimal::HitAnimal(int nDamage)
{
	CFade::FADE fade = CFade::GetFade();

	m_nLife -= nDamage;

	if (m_nLife <= 0)
	{	//ライフが0になったらおともの破棄
		m_animalState = ANIMALSTATE_DEATH;
	}
	else
	{	//ライフが残ってる
		m_animalState = ANIMALSTATE_DAMAGE;
		m_nCntState = 5;
		SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));			//赤色になる
	}
}

//=============================================================================
// テクスチャを読み込む
//=============================================================================
HRESULT CAnimal::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = NULL;											//デバイスの取得
	CRenderer * pRenderer = CManager::GetRenderer();						//レンダリングクラスの呼び出し

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, ANIMAL_DOG, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, ANIMAL_MONKEY, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, ANIMAL_KIJI, &m_pTexture[2]);

	return S_OK;
}

//=============================================================================
// テクスチャを破棄
//=============================================================================
void CAnimal::Unload(void)
{
	// テクスチャの破棄
	for (int nCntAnimal = 0; nCntAnimal < MAX_ANIMALTEX; nCntAnimal++)
	{
		if (m_pTexture[nCntAnimal] != NULL)
		{
			m_pTexture[nCntAnimal]->Release();
			m_pTexture[nCntAnimal] = NULL;
		}
	}
}