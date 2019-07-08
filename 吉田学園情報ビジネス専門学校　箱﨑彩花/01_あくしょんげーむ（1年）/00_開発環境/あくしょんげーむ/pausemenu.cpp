//===============================================================================
//
// �|�[�Y���j���[���� [pausemenu.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"pausemenu.h"

//==============================================================================
//�}�N����`
//===============================================================================
#define PAUSEMENU_TEXTURE	 "data/TEXTURE/pause100.png"		//�ǂݍ��ރe�N�X�`��
#define PAUSEMENU_POS_X						(0)													//�w�i�̍���X���W
#define PAUSEMENU_POS_Y						(0)													//�w�i�̍���Y���W
#define PAUSEMENU_WIDTH						(SCREEN_WIDTH)							//�w�i�̕�
#define PAUSEMENU_HEIGHT					(SCREEN_HEIGHT)							//�w�i�̍���

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePauseMenu = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//===============================================================================
//�|�[�Y���j���[����������
//===============================================================================
void InitPauseMenu(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;						//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PAUSEMENU_TEXTURE, &g_pTexturePauseMenu);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMenu,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(PAUSEMENU_POS_X, PAUSEMENU_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSEMENU_WIDTH, PAUSEMENU_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSEMENU_POS_X, PAUSEMENU_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSEMENU_WIDTH, PAUSEMENU_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.5);

	//�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//===============================================================================
	//�|�[�Y���j���[�w�i�̍��W�ݒ�
	pVtx[4].pos = D3DXVECTOR3(430, 200, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(790, 200, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(430, 560, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(790, 560, 0.0f);

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//�|�[�Y���j���[�̐F�ݒ�
	pVtx[4].col = D3DXCOLOR(0.3f, 0.2f, 0.3f, 0.7f);
	pVtx[5].col = D3DXCOLOR(0.3f, 0.2f, 0.3f, 0.7f);
	pVtx[6].col = D3DXCOLOR(0.3f, 0.2f, 0.3f, 0.7f);
	pVtx[7].col = D3DXCOLOR(0.3f, 0.2f, 0.3f, 0.7f);

	//�|�[�Y���j���[�w�i�e�N�X�`���̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMenu->Unlock();
}

//===============================================================================
//�|�[�Y���j���[�I������
//===============================================================================
void UninitPauseMenu(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePauseMenu != NULL)
	{
		g_pTexturePauseMenu->Release();
		g_pTexturePauseMenu = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();
		g_pVtxBuffPauseMenu = NULL;
	}
}

//===============================================================================
//�|�[�Y���j���[�X�V����
//===============================================================================
void UpdatePauseMenu(void)
{

}

//===============================================================================
//�|�[�Y���j���[�`�揈��
//===============================================================================
void DrawPauseMenu(void)
{
	int nCntPauseMenu;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseMenu);

	for (nCntPauseMenu = 0; nCntPauseMenu < 2; nCntPauseMenu++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPauseMenu * 4, 2);
	}
}