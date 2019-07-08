//=========================================================================================================================
//
// ���U���g�̏��� [result.cpp]
// Author :  �L�n�@���u�@���@����
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "result.h"		//���U���g
#include "input.h"		//����
#include "fade.h"		//�t�F�[�h
#include "Game.h"		//�Q�[��
#include "sound.h"		//�T�E���h
#include "enter.h"		//�G���^�[
#include "camera.h"
#include "object.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define RESULT_TEXTURE_WIN		"data\\TEXTURE\\player_win.png"//�ǂݍ��ރe�N�X�`���t�@�C��
#define RESULT_TEXTURE_NOTWIN	"data\\TEXTURE\\oni_win2.png"//�ǂݍ��ރe�N�X�`���t�@�C��
#define RESULT_POS_X			(0)							//���U���g�̍���X���W
#define RESULT_POS_Y			(0)							//���U���g�̍���Y���W
#define RESULT_WIDTH			(SCREEN_WIDTH)				//���U���g�̕�
#define RESULT_HEIGHT			(SCREEN_HEIGHT)				//���U���g�̍���
#define RESULT_MAX				(2)							//���U���g�̍���
#define RESULT_TEXTURE_SPEED	(5)							//�e�N�X�`���A�j���[�V�����X�s�[�h
#define RESULT_TEXTURE_PATTERN	(10)						//�e�N�X�`���A�j���[�V�����p�^�[����
#define RESULT_TEXTURE_UV_U		(1.0f)						//�e�N�X�`���A�j���[�V����U�͈�
#define RESULT_TEXTURE_UV_V		(1.0f)						//�e�N�X�`���A�j���[�V����V�͈�
#define RESULT_BACKTEXTURE_UV_U	(1.0f)						//�O�e�N�X�`���A�j���[�V����U�͈�
#define RESULT_BACKTEXTURE_UV_V	(1.0f)						//�O�e�N�X�`���A�j���[�V����V�͈�
#define RESULT_SPEED			(0.003f)					//���U���g�X�s�[�h

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posResult;							//���U���g�̈ʒu
D3DXVECTOR3 g_moveResult;							//���U���g�̈ړ�

//=========================================================================================================================
// ���U���g����������
//=========================================================================================================================
void InitResult(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	Camera *pCamera = GetCamera();

	Object *pObject = GetObject();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_posResult = D3DXVECTOR3((RESULT_POS_X + RESULT_WIDTH) / 2, (RESULT_POS_Y + RESULT_HEIGHT) / 2, 0.0f);		//�|���S���̒��S�l
	g_moveResult = D3DXVECTOR3(0.0f, RESULT_SPEED, 0.0f);		//�|���S���ړ��l

	GAMESTATE GameStateNow = GetGameState();
	
	//�����Ɣs�k
	//�e�N�X�`���̓ǂݍ���
	if (GameStateNow == GAMESTATE_CLEAR)
	{
		D3DXCreateTextureFromFile
		(
			pDevice,
			RESULT_TEXTURE_WIN,
			&g_pTextureResult
		);

		//�j���g���̐�
		PlaySound(SOUND_LABEL_SE_CHICEN);
	}
	else
	{
		D3DXCreateTextureFromFile
		(
			pDevice,
			RESULT_TEXTURE_NOTWIN,
			&g_pTextureResult
		);
	}

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffResult->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);
	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(RESULT_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, RESULT_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(RESULT_TEXTURE_UV_U, RESULT_TEXTURE_UV_V);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResult->Unlock();

	InitEnter();
}

//=========================================================================================================================
// ���U���g�I������
//=========================================================================================================================
void UninitResult(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	UninitEnter();
}

//=========================================================================================================================
// ���U���g�X�V����
//=========================================================================================================================
void UpdateResult(void)
{
	FADE	  pFade = GetFade();  //�@�t�F�[�h�̃|�C���^

	static int nCount = 0;

	nCount++;

	if (pFade == FADE_NONE)
	{
		//�ݒ�L�[�iENTER�L�[�j�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(3, 0) == true || (nCount % 190) == 0)
		{
			//���艹
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFade(MODE_TITLE);
		}
	}

	UpdateEnter();
}

//=========================================================================================================================
// ���U���g�`�揈��
//=========================================================================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffResult,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//���U���g�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	DrawEnter();
}