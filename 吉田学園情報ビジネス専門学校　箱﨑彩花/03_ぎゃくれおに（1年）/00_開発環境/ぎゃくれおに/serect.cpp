//=========================================================================================================================
//
// �Z���N�g�̏��� [Serect.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "serect.h"		//�Z���N�g
#include "input.h"		//�L�[�{�[�h
#include "fade.h"		//�t�F�[�h
#include "game.h"		//�Q�[��
#include "sound.h"		//�T�E���h
#include "main.h"		//���C��

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define SERECT_TEXTURE_NAME		"data\\TEXTURE\\�Z���N�g.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define SERECT_TEXTURE_NAME0	"data\\TEXTURE\\play.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define SERECT_TEXTURE_NAME1	"data\\TEXTURE\\End.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_TEXTURE				(3)									//�e�N�X�`���̍ő吔
#define SERECT_POS_X			(0)								
//�Z���N�g�̍���X���W
#define SERECT_POS_Y			(0)									//�Z���N�g�̍���Y���W
#define SERECT_WIDTH			(SCREEN_WIDTH)						//�Z���N�g�̕�
#define SERECT_HEIGHT			(SCREEN_HEIGHT)						//�Z���N�g�̍���
#define SERECT_TEXTURE_UV_U		(1.0f)								//�e�N�X�`���A�j���[�V����U�͈�
#define SERECT_TEXTURE_UV_V		(1.0f)								//�e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSerect[MAX_TEXTURE] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSerect = NULL;		 //���_�o�b�t�@�ւ̃|�C���^
SERECT g_Serect;										 //�|�X�̏��

//=========================================================================================================================
// �Z���N�g����������
//=========================================================================================================================
void InitSerect(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Serect.pos = D3DXVECTOR3((SERECT_POS_X + SERECT_WIDTH) / 2, (SERECT_POS_Y + SERECT_HEIGHT) / 2, 0.0f);
	g_Serect.SelectNum = 0;
	g_Serect.SelectColor = 1.0f;

	//�Z���N�g�̍��W
	float PosSerect = (SCREEN_HEIGHT / 2 - 240);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�P���ڂ̉摜
		pDevice,
		SERECT_TEXTURE_NAME,
		&g_pTextureSerect[0]
	);
	D3DXCreateTextureFromFile
	(//�Q���ڂ̉摜
		pDevice,
		SERECT_TEXTURE_NAME0,
		&g_pTextureSerect[1]
	);
	D3DXCreateTextureFromFile
	(//�S���ڂ̉摜
		pDevice,
		SERECT_TEXTURE_NAME1,
		&g_pTextureSerect[2]
	);
	
	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSerect,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffSerect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		if (nCount == 0)
		{//�J�E���g�O�������ꍇ
			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(SERECT_POS_X, SERECT_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SERECT_WIDTH, SERECT_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SERECT_POS_X, SERECT_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SERECT_WIDTH, SERECT_HEIGHT, 0.0f);
			//���_�J���[�ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{//����ȊO�̏ꍇ
			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(SERECT_WIDTH / 2 - 300, PosSerect, 0.0f);				//����
			pVtx[1].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 300, PosSerect, 0.0f);				//�E��
			pVtx[2].pos = D3DXVECTOR3(SERECT_WIDTH / 2 - 300, PosSerect + 150, 0.0f);		//����
			pVtx[3].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 300, PosSerect + 150, 0.0f);		//�E��
			if (nCount == 1)
			{
				//���_�J���[�ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else
			{
				//���_�J���[�ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(127, 127, 127, 255);
				pVtx[1].col = D3DCOLOR_RGBA(127, 127, 127, 255);
				pVtx[2].col = D3DCOLOR_RGBA(127, 127, 127, 255);
				pVtx[3].col = D3DCOLOR_RGBA(127, 127, 127, 255);
			}

			//�I�𗓂̕�
			PosSerect += 230;
		}

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(SERECT_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, SERECT_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(SERECT_TEXTURE_UV_U, SERECT_TEXTURE_UV_V);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffSerect->Unlock();
}

//=========================================================================================================================
// �Z���N�g�I������
//=========================================================================================================================
void UninitSerect(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureSerect[nCount] != NULL)
		{
			g_pTextureSerect[nCount] -> Release();
			g_pTextureSerect[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSerect != NULL)
	{
		g_pVtxBuffSerect->Release();
		g_pVtxBuffSerect = NULL;
	}
}

//=========================================================================================================================
// �Z���N�g�X�V����
//=========================================================================================================================
void UpdateSerect(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	FADE pFade = GetFade();

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffSerect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//GAMESTATE pGameState = GetGameState();

	if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_W) == true || GetJoyPadTrigger(DIJS_BUTTON_18, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_10, 0) == true)
	{//���L�[�̏���������Ƃ�
		// ���_�J���[�ݒ�
		pVtx[g_Serect.SelectNum * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Serect.SelectNum = (g_Serect.SelectNum + 1) % 2;
		g_Serect.SelectColor = 1.0f;

		PlaySound(SOUND_LABEL_SE_UPDWON);
	}
	else if (GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_S) == true || GetJoyPadTrigger(DIJS_BUTTON_19, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_11, 0) == true)
	{//���L�[�̉����������Ƃ�
		// ���_�J���[�ݒ�
		pVtx[g_Serect.SelectNum * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Serect.SelectNum = (g_Serect.SelectNum + 1) % 2;
		g_Serect.SelectColor = 1.0f;

		PlaySound(SOUND_LABEL_SE_UPDWON);
	}

	//�_�ŏ���
	//�I�����Ă���J���[�̒l�����炵�Ă���
	g_Serect.SelectColor -= 0.01f;

	if (g_Serect.SelectColor < 0.5f)
	{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
		g_Serect.SelectColor = 1.0f;
	}

	// ���_�J���[�ݒ�
	pVtx[g_Serect.SelectNum * 4 + 4].col = D3DXCOLOR(g_Serect.SelectColor, g_Serect.SelectColor, g_Serect.SelectColor, 1.0f);
	pVtx[g_Serect.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(g_Serect.SelectColor, g_Serect.SelectColor, g_Serect.SelectColor, 1.0f);
	pVtx[g_Serect.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(g_Serect.SelectColor, g_Serect.SelectColor, g_Serect.SelectColor, 1.0f);
	pVtx[g_Serect.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(g_Serect.SelectColor, g_Serect.SelectColor, g_Serect.SelectColor, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffSerect->Unlock();

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(3, 0) == true)
		{
			if (g_Serect.SelectNum == 0)
			{
				//���艹
				PlaySound(SOUND_LABEL_SE_DECIDE);
				//�Q�[���ɍs��
				SetFade(MODE_TUTORIAL);
			}
			else if (g_Serect.SelectNum == 1)
			{
				//���艹
				PlaySound(SOUND_LABEL_SE_DECIDE);
				SetFade(MODE_END);
			}
		}
	}
}

//=========================================================================================================================
// �Z���N�g�`�揈��
//=========================================================================================================================
void DrawSerect(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffSerect,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureSerect[nCount]);

		//�Z���N�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}