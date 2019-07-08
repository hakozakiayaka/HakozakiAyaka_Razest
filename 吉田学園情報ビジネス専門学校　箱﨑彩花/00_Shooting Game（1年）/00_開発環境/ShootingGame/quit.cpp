//===============================================================================
//
// �N�E�B�b�g���� [quit.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"quit.h"

//==============================================================================
//�}�N����`
//===============================================================================
#define QUIT_TEXTURE	 "data/TEXTURE/pause002.png"		//�ǂݍ��ރe�N�X�`��

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureQuit = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffQuit = NULL;	//���_�o�b�t�@�ւ̃|�C���^
QUITSTATE g_QuitState;

//===============================================================================
//�N�E�B�b�g����������
//===============================================================================
void InitQuit(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;						//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, QUIT_TEXTURE, &g_pTextureQuit);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffQuit,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

	//�N�E�B�b�g�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(436, 430, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(784, 430, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(436, 542, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(784, 542, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�N�E�B�b�g�̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�N�E�B�b�g�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffQuit->Unlock();
}

//===============================================================================
//�N�E�B�b�g�I������
//===============================================================================
void UninitQuit(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureQuit != NULL)
	{
		g_pTextureQuit->Release();
		g_pTextureQuit = NULL;
	}
	
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffQuit != NULL)
	{
		g_pVtxBuffQuit->Release();
		g_pVtxBuffQuit = NULL;
	}
}

//===============================================================================
//�N�E�B�b�g�X�V����
//===============================================================================
void UpdateQuit(void)
{
	VERTEX_2D * pVtx;						//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffQuit->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_QuitState)
	{
	case QUITSTATE_SELECT:
		//�R���e�B�j���[�̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case 	QUITSTATE_NONE:
		//�R���e�B�j���[�̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffQuit->Unlock();
}

//===============================================================================
//�N�E�B�b�g�`�揈��
//===============================================================================
void DrawQuit(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	
	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffQuit, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);	

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureQuit);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===============================================================================
//�N�E�B�b�g�̐ݒ�
//===============================================================================
void  SetQuit(QUITSTATE state)
{
	g_QuitState = state;
}