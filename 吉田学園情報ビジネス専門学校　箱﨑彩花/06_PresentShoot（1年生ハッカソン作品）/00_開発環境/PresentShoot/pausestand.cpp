//=============================================================================
//
// �|�[�Y���j���[��� [pausestand.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "pausestand.h"
#include "main.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RESULT_TEXTURENAME "data\\TEXTURE\\pausemenu.jpg"					//�ǂݍ��ރe�N�X�`���t�@�C��
#define RESULT_WHIDTH		(600)										//�w�i�̕�
#define RESULT_HEIGHT		(550)										//�w�i�̍���
#define RESULT_POS_X		((SCREEN_WIDTH / 2) - (RESULT_WHIDTH / 2))	//�w�i�̍���X���W
#define RESULT_POS_Y		((SCREEN_HEIGHT / 2) - (RESULT_HEIGHT / 2))	//�w�i�̍���Y���W

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePauseStand = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseStand = NULL;		//���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitPauseStand(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		RESULT_TEXTURENAME,
		&g_pTexturePauseStand);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseStand,
		NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseStand->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_POS_X + RESULT_WHIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y + RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_POS_X + RESULT_WHIDTH, RESULT_POS_Y + RESULT_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseStand->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitPauseStand(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePauseStand != NULL)
	{
		g_pTexturePauseStand->Release();
		g_pTexturePauseStand = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseStand != NULL)
	{
		g_pVtxBuffPauseStand->Release();
		g_pVtxBuffPauseStand = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseStand(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPauseStand(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseStand, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseStand);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,											//�J�n���钸�_�̃C���f�b�N�X
		2);											//�v���~�e�B�u�̐�
}