//===============================================================================
//
// �w�i���� [bg.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"bg.h"
#include "game.h"

//==============================================================================
//�}�N����`
//===============================================================================
#define BG_TEXTURE		 "data/TEXTURE/sky005.jpg"						//�w�i�@�ǂݍ��ރe�N�X�`��
#define BG_TEXTURE1	 "data/TEXTURE/kanban1.png"				//�Ŕ@�ǂݍ��ރe�N�X�`��
#define MAX_BG							(3)													//�e�N�X�`���̐�

#define BG_POS_X						(0)													//�w�i�̍���X���W
#define BG_POS_Y						(0)													//�w�i�̍���Y���W
#define BG_WIDTH						(SCREEN_WIDTH)							//�w�i�̕�
#define BG_HEIGHT					(SCREEN_HEIGHT)							//�w�i�̍���
#define VERTEX_NUMBER			(4)													//���_��

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBG[MAX_BG] = {};				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;	//���_�o�b�t�@�ւ̃|�C���^
float g_nBg;

//===============================================================================
//�w�i����������
//===============================================================================
void InitBG(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;						//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = GetDevice();

	//�X�e�[�W���擾
	GAMESTAGE pStage;
	pStage = GetGameStage();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE, &g_pTextureBG[0]);

	if (pStage == GAMESTAGE_SELECT)
	{	//�I����ʂ̎������g�p
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURE1, &g_pTextureBG[1]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUMBER * MAX_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//�I�����---------------------------------------------
	if (pStage == GAMESTAGE_SELECT)
	{
		//�w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(200, 70, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1000, 70, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(200, 450, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1000, 450, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�w�i�F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	pVtx += 4;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//===============================================================================
//�w�i�I������
//===============================================================================
void UninitBG(void)
{
	int nCntBg;

	//�e�N�X�`���̔j��
	for (nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		if (g_pTextureBG[nCntBg] != NULL)
		{
			g_pTextureBG[nCntBg]->Release();
			g_pTextureBG[nCntBg] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//===============================================================================
//�w�i�X�V����
//===============================================================================
void UpdateBG(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//�X�e�[�W���擾
	GAMESTAGE pStage;
	pStage = GetGameStage();

	g_nBg += 0.0001f;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + g_nBg, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + g_nBg, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + g_nBg, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_nBg, 1.0f);

	pVtx += 4;

	//if (pStage == GAMESTAGE_SELECT)
	//{
	//	//�w�i�̍��W�ݒ�
	//	pVtx[0].pos = D3DXVECTOR3(100, 100, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(300, 100, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(100, 200, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(300, 200, 0.0f);

	//	//�e�N�X�`���̍��W�ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//}
	//pVtx += 4;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//===============================================================================
//�w�i�`�揈��
//===============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	int nCntBg;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);	

	for (nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBG[nCntBg]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBg, 2);
	}
}