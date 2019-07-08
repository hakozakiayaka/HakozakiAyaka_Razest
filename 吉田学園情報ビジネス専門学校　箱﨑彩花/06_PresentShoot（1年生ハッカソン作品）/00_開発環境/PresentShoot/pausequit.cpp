//=============================================================================
//
// �|�[�Y���j���[��� [pausecontinue.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "pausequit.h"
#include "main.h"
#include "input.h"
#include "pause.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define QUIT_TEXTURENAME "data\\TEXTURE\\quit_logo.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define QUIT_WHIDTH		(200)										//�w�i�̕�
#define QUIT_HEIGHT		(80)										//�w�i�̍���
#define QUIT_POS_X		((SCREEN_WIDTH / 2) - (QUIT_WHIDTH / 2))	//�w�i�̍���X���W
#define QUIT_POS_Y		(460)										//�w�i�̍���Y���W

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePauseQuit = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseQuit = NULL;		//���_�o�b�t�@�ւ̃|�C���^
QUITSTATE g_QuitState;

//=============================================================================
// ����������
//=============================================================================
void InitPauseQuit(void)
{
	//�ϐ��̏�����
	g_QuitState = QUITSTATE_NORMAL;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		QUIT_TEXTURENAME,
		&g_pTexturePauseQuit);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseQuit,
		NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseQuit->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(QUIT_POS_X, QUIT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(QUIT_POS_X + QUIT_WHIDTH, QUIT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(QUIT_POS_X, QUIT_POS_Y + QUIT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(QUIT_POS_X + QUIT_WHIDTH, QUIT_POS_Y + QUIT_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseQuit->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitPauseQuit(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePauseQuit != NULL)
	{
		g_pTexturePauseQuit->Release();
		g_pTexturePauseQuit = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseQuit != NULL)
	{
		g_pVtxBuffPauseQuit->Release();
		g_pVtxBuffPauseQuit = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseQuit(void)
{
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseQuit->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_QuitState)
	{
	case QUITSTATE_NORMAL:
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		pVtx[1].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		pVtx[2].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		pVtx[3].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		break;

	case QUITSTATE_SELECT:
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);

		break;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseQuit->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPauseQuit(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseQuit, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseQuit);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,											//�J�n���钸�_�̃C���f�b�N�X
		2);											//�v���~�e�B�u�̐�
}

//=============================================================================
// �R���e�B�j���[�̐ݒ菈��
//=============================================================================
void SetPauseQuit(QUITSTATE state)
{
	//��Ԃ̐ݒ�
	g_QuitState = state;
}