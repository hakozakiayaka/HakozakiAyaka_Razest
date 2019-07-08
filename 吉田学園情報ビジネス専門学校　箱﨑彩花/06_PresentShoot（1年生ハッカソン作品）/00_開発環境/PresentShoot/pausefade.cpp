//=============================================================================
//
// �|�[�Y��������� [pause_fade.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "pausefade.h"
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PAUSEFADE_WHIDTH		(SCREEN_WIDTH)										//�w�i�̕�
#define PAUSEFADE_HEIGHT		(SCREEN_HEIGHT)										//�w�i�̍���
#define PAUSEFADE_POS_X		(0)	//�w�i�̍���X���W
#define PAUSEFADE_POS_Y		(0)	//�w�i�̍���Y���W

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePauseFade = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseFade = NULL;		//���_�o�b�t�@�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
void InitPauseFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseFade,
		NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(PAUSEFADE_POS_X, PAUSEFADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSEFADE_POS_X + PAUSEFADE_WHIDTH, PAUSEFADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSEFADE_POS_X, PAUSEFADE_POS_Y + PAUSEFADE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSEFADE_POS_X + PAUSEFADE_WHIDTH, PAUSEFADE_POS_Y + PAUSEFADE_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseFade->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitPauseFade(void)
{

	// �e�N�X�`���̊J��
	if (g_pTexturePauseFade != NULL)
	{
		g_pTexturePauseFade->Release();
		g_pTexturePauseFade = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseFade != NULL)
	{
		g_pVtxBuffPauseFade->Release();
		g_pVtxBuffPauseFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePauseFade(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPauseFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseFade);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,											//�J�n���钸�_�̃C���f�b�N�X
		2);											//�v���~�e�B�u�̐�
}