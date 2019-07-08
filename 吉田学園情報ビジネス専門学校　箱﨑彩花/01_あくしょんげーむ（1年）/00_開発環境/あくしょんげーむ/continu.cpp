//===============================================================================
//
// �R���e�B�j���[���� [continu.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"continu.h"

//==============================================================================
//�}�N����`
//===============================================================================
#define CONTINU_TEXTURE	 "data/TEXTURE/pause000.png"		//�ǂݍ��ރe�N�X�`��

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureContinu = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffContinu = NULL;	//���_�o�b�t�@�ւ̃|�C���^
CONTINUESTATE g_ContinueState;

//===============================================================================
//�R���e�B�j���[����������
//===============================================================================
void InitContinu(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;						//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, CONTINU_TEXTURE, &g_pTextureContinu);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffContinu,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffContinu->Lock(0, 0, (void**)&pVtx, 0);

	//�R���e�B�j���[�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(436, 206, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(784, 206, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(436, 318, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(784, 318, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�R���e�B�j���[�̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�R���e�B�j���[�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffContinu->Unlock();
}

//===============================================================================
//�R���e�B�j���[�I������
//===============================================================================
void UninitContinu(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureContinu != NULL)
	{
		g_pTextureContinu->Release();
		g_pTextureContinu = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffContinu != NULL)
	{
		g_pVtxBuffContinu->Release();
		g_pVtxBuffContinu = NULL;
	}
}

//===============================================================================
//�R���e�B�j���[�X�V����
//===============================================================================
void UpdateContinu(void)
{
	VERTEX_2D * pVtx;						//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffContinu->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_ContinueState)
	{
	case CONTUNUESTATE_SELECT:
		//�R���e�B�j���[�̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case CONTINUESTATE_NONE:
		//�R���e�B�j���[�̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffContinu->Unlock();
}

//===============================================================================
//�R���e�B�j���[�`�揈��
//===============================================================================
void DrawContinu(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	
	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffContinu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);	

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureContinu);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}

//===============================================================================
//�R���e�B�j���[�̐ݒ菈��
//===============================================================================
void SetContinue(CONTINUESTATE state)
{
	g_ContinueState = state;
}