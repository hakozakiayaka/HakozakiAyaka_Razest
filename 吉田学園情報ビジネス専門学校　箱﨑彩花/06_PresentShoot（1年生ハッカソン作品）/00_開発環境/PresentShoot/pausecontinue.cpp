//=============================================================================
//
// �|�[�Y�R���e�B�j���[��� [pausecontinue.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "pausecontinue.h"
#include "main.h"
#include "input.h"
#include "pause.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CONTINUE_TEXTURENAME "data\\TEXTURE\\continue_logo.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define CONTINUE_WHIDTH		(350)											//�w�i�̕�
#define CONTINUE_HEIGHT		(70)											//�w�i�̍���
#define CONTINUE_POS_X		((SCREEN_WIDTH / 2) - (CONTINUE_WHIDTH / 2))	//�w�i�̍���X���W
#define CONTINUE_POS_Y		(230)											//�w�i�̍���Y���W

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePauseContinue = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseContinue = NULL;			//���_�o�b�t�@�ւ̃|�C���^
CONTINUESTATE g_ContinueState;

//=============================================================================
// ����������
//=============================================================================
void InitPauseContinue(void)
{
	//�ϐ��̏�����
	g_ContinueState = CONTINUESTATE_NORMAL;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		CONTINUE_TEXTURENAME,
		&g_pTexturePauseContinue);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseContinue,
		NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(CONTINUE_POS_X, CONTINUE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(CONTINUE_POS_X + CONTINUE_WHIDTH, CONTINUE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(CONTINUE_POS_X, CONTINUE_POS_Y + CONTINUE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(CONTINUE_POS_X + CONTINUE_WHIDTH, CONTINUE_POS_Y + CONTINUE_HEIGHT, 0.0f);

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
	g_pVtxBuffPauseContinue->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitPauseContinue(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePauseContinue != NULL)
	{
		g_pTexturePauseContinue->Release();
		g_pTexturePauseContinue = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseContinue != NULL)
	{
		g_pVtxBuffPauseContinue->Release();
		g_pVtxBuffPauseContinue = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseContinue(void)
{
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_ContinueState)
	{
	case CONTINUESTATE_NORMAL:
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		pVtx[1].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		pVtx[2].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		pVtx[3].col = D3DXCOLOR(0.2f, 0.2f, 0.35f, 0.65f);
		break;

	case CONTINUESTATE_SELECT:
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.65f);
		break;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseContinue->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPauseContinue(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseContinue, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseContinue);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,											//�J�n���钸�_�̃C���f�b�N�X
		2);											//�v���~�e�B�u�̐�
}

//=============================================================================
// �R���e�B�j���[�̐ݒ菈��
//=============================================================================
void SetPauseContinue(CONTINUESTATE state)
{
	//��Ԃ̐ݒ�
	g_ContinueState = state;
}