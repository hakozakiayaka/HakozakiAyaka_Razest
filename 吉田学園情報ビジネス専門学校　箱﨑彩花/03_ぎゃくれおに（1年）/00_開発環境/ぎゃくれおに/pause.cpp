//=========================================================================================================================
//
// �|�[�Y�̏��� [pause.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "pause.h"		//�|�[�Y
#include "input.h"		//�L�[�{�[�h
#include "fade.h"		//�t�F�[�h
#include "game.h"		//�|�[�Y
#include "sound.h"		//�T�E���h

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define PAUSE_TEXTURE_NAME		"data\\TEXTURE\\�|�[�Y.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define PAUSE_TEXTURE_NAME0		"data\\TEXTURE\\pause000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define PAUSE_TEXTURE_NAME1		"data\\TEXTURE\\pause001.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define PAUSE_TEXTURE_NAME2		"data\\TEXTURE\\pause002.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_TEXTURE				(4)								//�e�N�X�`���̍ő吔
#define PAUSE_POS_X				(0)								//�|�[�Y�̍���X���W
#define PAUSE_POS_Y				(0)								//�|�[�Y�̍���Y���W
#define PAUSE_WIDTH				(SCREEN_WIDTH)					//�|�[�Y�̕�
#define PAUSE_HEIGHT			(SCREEN_HEIGHT)					//�|�[�Y�̍���
#define PAUSE_TEXTURE_UV_U		(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define PAUSE_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�
#define PAUSE_SPEED				(0.003f)						//�|�[�Y�X�s�[�h

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_TEXTURE] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		 //���_�o�b�t�@�ւ̃|�C���^
PAUSE g_Pause;										 //�|�X�̏��

//=========================================================================================================================
// �|�[�Y����������
//=========================================================================================================================
void InitPause(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Pause.pos = D3DXVECTOR3((PAUSE_POS_X + PAUSE_WIDTH) / 2, (PAUSE_POS_Y + PAUSE_HEIGHT) / 2, 0.0f);
	g_Pause.SelectNum = 0;
	g_Pause.SelectColor = 1.0f;

	//�|�[�Y�̍��W
	float PosPause = (SCREEN_HEIGHT / 2) - 300;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�P���ڂ̉摜
		pDevice,
		PAUSE_TEXTURE_NAME,
		&g_pTexturePause[0]
	);
	D3DXCreateTextureFromFile
	(//�Q���ڂ̉摜
		pDevice,
		PAUSE_TEXTURE_NAME0,
		&g_pTexturePause[1]
	);
	D3DXCreateTextureFromFile
	(//�R���ڂ̉摜
		pDevice,
		PAUSE_TEXTURE_NAME1,
		&g_pTexturePause[2]
	);
	D3DXCreateTextureFromFile
	(//�S���ڂ̉摜
		pDevice,
		PAUSE_TEXTURE_NAME2,
		&g_pTexturePause[3]
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffPause->Lock
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
			pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);
			//���_�J���[�ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{//����ȊO�̏ꍇ
		 //���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(PAUSE_WIDTH / 2 - 250, PosPause, 0.0f);			//����
			pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH / 2 + 250, PosPause, 0.0f);			//�E��
			pVtx[2].pos = D3DXVECTOR3(PAUSE_WIDTH / 2 - 250, PosPause + 200, 0.0f);		//����
			pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH / 2 + 250, PosPause + 200, 0.0f);		//�E��

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
			PosPause += 200;
		}

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(PAUSE_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, PAUSE_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(PAUSE_TEXTURE_UV_U, PAUSE_TEXTURE_UV_V);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
}

//=========================================================================================================================
// �|�[�Y�I������
//=========================================================================================================================
void UninitPause(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTexturePause[nCount] != NULL)
		{
			g_pTexturePause[nCount] -> Release();
			g_pTexturePause[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=========================================================================================================================
// �|�[�Y�X�V����
//=========================================================================================================================
void UpdatePause(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffPause->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_W) == true || GetJoyPadTrigger(DIJS_BUTTON_18, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_10, 0) == true)
	{//���L�[�̏���������Ƃ�
		// ���_�J���[�ݒ�
		pVtx[g_Pause.SelectNum * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Pause.SelectNum = (g_Pause.SelectNum + 2) % 3;
		g_Pause.SelectColor = 1.0f;

		PlaySound(SOUND_LABEL_SE_UPDWON);
	}
	if (GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_S) == true || GetJoyPadTrigger(DIJS_BUTTON_19, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_11, 0) == true)
	{//���L�[�̉����������Ƃ�
		// ���_�J���[�ݒ�
		pVtx[g_Pause.SelectNum * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Pause.SelectNum = (g_Pause.SelectNum + 1) % 3;
		g_Pause.SelectColor = 1.0f;
		PlaySound(SOUND_LABEL_SE_UPDWON);
	}

	//�_�ŏ���
	//�I�����Ă���J���[�̒l�����炵�Ă���
	g_Pause.SelectColor -= 0.01f;

	if (g_Pause.SelectColor < 0.5f)
	{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
		g_Pause.SelectColor = 1.0f;
	}

	// ���_�J���[�ݒ�
	pVtx[g_Pause.SelectNum * 4 + 4].col = D3DXCOLOR(g_Pause.SelectColor, g_Pause.SelectColor, g_Pause.SelectColor, 1.0f);
	pVtx[g_Pause.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(g_Pause.SelectColor, g_Pause.SelectColor, g_Pause.SelectColor, 1.0f);
	pVtx[g_Pause.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(g_Pause.SelectColor, g_Pause.SelectColor, g_Pause.SelectColor, 1.0f);
	pVtx[g_Pause.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(g_Pause.SelectColor, g_Pause.SelectColor, g_Pause.SelectColor, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(3, 0) == true)
	{
		if (g_Pause.SelectNum == 0)
		{
			//���艹
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//�L�����Z��
			SetPauseState(false);
		}
		else if (g_Pause.SelectNum == 1)
		{
			//���艹
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//�Q�[���̍ŏ��ɖ߂�
			SetFade(MODE_GAME);
		}
		else if (g_Pause.SelectNum == 2)
		{
			//���艹
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//�Q�[���̃^�C�g���ɖ߂�
			SetFade(MODE_TITLE);
		}
	}
}

//=========================================================================================================================
// �|�[�Y�`�揈��
//=========================================================================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffPause,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCount]);

		//�|�[�Y�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}