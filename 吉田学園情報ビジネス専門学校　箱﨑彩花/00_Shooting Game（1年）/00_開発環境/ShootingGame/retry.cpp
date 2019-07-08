//===============================================================================
//
// ���g���C���� [pause.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"retry.h"

//==============================================================================
//�}�N����`
//===============================================================================
#define RETRY_TEXTURE	 "data/TEXTURE/pause001.png"		//�ǂݍ��ރe�N�X�`��

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureRetry = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRetry = NULL;	//���_�o�b�t�@�ւ̃|�C���^
RETRYSTATE g_RetryState;

//===============================================================================
//���g���C����������
//===============================================================================
void InitRetry(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;						//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	
	//�f�o�C�X���擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, RETRY_TEXTURE, &g_pTextureRetry);
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRetry,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

	//���g���C�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(436, 318, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(784, 318, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(436, 430, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(784, 430, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���g���C�̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���g���C�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRetry->Unlock();
}

//===============================================================================
//���g���C�I������
//===============================================================================
void UninitRetry(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRetry != NULL)
	{
		g_pTextureRetry->Release();
		g_pTextureRetry = NULL;
	}
	
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRetry != NULL)
	{
		g_pVtxBuffRetry->Release();
		g_pVtxBuffRetry = NULL;
	}
}

//===============================================================================
//���g���C�X�V����
//===============================================================================
void UpdateRetry(void)
{
	VERTEX_2D * pVtx;						//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRetry->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_RetryState)
	{
	case RETRYSTATE_SELECT:
		//���g���C�̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case RETRYSTATE_NONE:
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRetry->Unlock();
}

//===============================================================================
//���g���C�`�揈��
//===============================================================================
void DrawRetry(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	
	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRetry, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);	

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRetry);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0 , 2);
}

//===============================================================================
//���g���C�̐ݒ菈��
//===============================================================================
void SetRetry(RETRYSTATE state)
{
	g_RetryState = state;
}