//=============================================================================
//
// �A�C�e���̏��� [item.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "input.h"
#include"main.h"
#include"player.h"
#include "item.h"
#include "score.h"
#include "game.h"
#include "fade.h"
#include "explosion.h"
#include "fadegame.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_NAME "data/TEXTURE/coin000.png"			//�e�N�X�`���̖��O
#define TEXTURE_NAME1 "data/TEXTURE/onigiri.png"			//�e�N�X�`���̖��O
#define TEXTURE_NAME2 "data/TEXTURE/piman.png"			//�e�N�X�`���̖��O
#define MAX_TEXTURE		(3)													//�e�N�X�`���̖���

#define MAX_ITEM				(128)												// �A�C�e���̍ő吔 
#define ITEM_SPEED			(10)													//�A�C�e���̑���
#define ITEM_SIZE				(40)													//�A�C�e���̑傫��
#define PLAYER_WIDTH		(30)													//�v���C���[�̕�
#define PLAYER_HEIGHT	(70)													//�v���C���[�̍���
#define MINUS					(10)													//�A�C�e���̕�
#define PLUS						(30)													//�A�C�e���̍���

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItem[MAX_TEXTURE] = {};			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
Item g_aItem[MAX_ITEM];																			//�A�C�e���̏��
int g_nNumItem;																							//�A�C�e���̑���

//=============================================================================
// �A�C�e�����̃f�[�^
//=============================================================================
ItemInfoStageSelect g_aItemInfoStageSelect[] =
{
	{ D3DXVECTOR3(270,570,0.0f),20,20,1 },
	{ D3DXVECTOR3(970,570,0.0f),20,20,2 }
};

ItemInfoStage1 g_aItemInfoStage1[] =
{
	//1�i��
	{ D3DXVECTOR3(35,500,0.0f),10,20,0 },
	{ D3DXVECTOR3(65,500,0.0f),10,20,0 },
	{ D3DXVECTOR3(95,500,0.0f),10,20,0 },

	//2�i��
	{ D3DXVECTOR3(255,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(285,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(315,410,0.0f),10,20,0 },

	//3�i��
	{ D3DXVECTOR3(35,280,0.0f),10,20,0 },
	{ D3DXVECTOR3(65,280,0.0f),10,20,0 },
	{ D3DXVECTOR3(95,280,0.0f),10,20,0 },

	//��ԏ�̒i
	{ D3DXVECTOR3(275,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(305,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(340,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(375,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(405,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(440,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(475,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(505,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(540,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(575,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(605,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(640,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(675,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(705,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(740,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(775,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(805,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(840,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(875,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(905,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(940,160,0.0f),10,20,0 },
	{ D3DXVECTOR3(975,160,0.0f),10,20,0 },

	//����ԏ�
	{ D3DXVECTOR3(1170,280,0.0f),10,20,0 },
	{ D3DXVECTOR3(1200,280,0.0f),10,20,0 },
	{ D3DXVECTOR3(1230,280,0.0f),10,20,0 },

	//�ォ��Q�i��
	{ D3DXVECTOR3(930,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(960,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(990,410,0.0f),10,20,0 },

	//�ォ��P�i��
	{ D3DXVECTOR3(1120,500,0.0f),10,20,0 },
	{ D3DXVECTOR3(1150,500,0.0f),10,20,0 },
	{ D3DXVECTOR3(1180,500,0.0f),10,20,0 },

	//�E�@�^��
	{ D3DXVECTOR3(755,330,0.0f),10,20,0 },
	{ D3DXVECTOR3(740,360,0.0f),10,20,0 },
	{ D3DXVECTOR3(770,360,0.0f),10,20,0 },

	//���@�^��
	{ D3DXVECTOR3(520,330,0.0f),10,20,0 },
	{ D3DXVECTOR3(505,360,0.0f),10,20,0 },
	{ D3DXVECTOR3(535,360,0.0f),10,20,0 },

	////
	//{ D3DXVECTOR3(535,600,0.0f),10,20,0 },
	//{ D3DXVECTOR3(585,600,0.0f),10,20,0 },
	//{ D3DXVECTOR3(615,600,0.0f),10,20,0 },

};

ItemInfoStage2 g_aItemInfoStage2[] =
{
	//
	{ D3DXVECTOR3(30,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(70,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(100,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(130,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(160,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(190,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(220,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(250,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(280,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(310,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(340,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(370,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(400,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(430,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(460,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(490,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(520,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(550,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(580,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(610,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(640,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(670,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(700,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(730,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(800,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(830,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(860,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1020,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1050,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1080,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1110,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1140,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1170,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1200,550,0.0f),10,20,0 },
	{ D3DXVECTOR3(1260,550,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(30,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(70,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(100,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(130,410,0.0f),10,20,0 },
	{ D3DXVECTOR3(160,410,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(30,310,0.0f),10,20,0 },
	{ D3DXVECTOR3(60,310,0.0f),10,20,0 },
	{ D3DXVECTOR3(90,310,0.0f),10,20,0 },
	{ D3DXVECTOR3(120,310,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(30,190,0.0f),10,20,0 },
	{ D3DXVECTOR3(60,190,0.0f),10,20,0 },
	{ D3DXVECTOR3(90,190,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(30,70,0.0f),10,20,0 },
	{ D3DXVECTOR3(60,70,0.0f),10,20,0 },
	{ D3DXVECTOR3(90,70,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(1170,70,0.0f),10,20,0 },
	{ D3DXVECTOR3(1200,70,0.0f),10,20,0 },
	{ D3DXVECTOR3(1230,70,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(1170,190,0.0f),10,20,0 },
	{ D3DXVECTOR3(1200,190,0.0f),10,20,0 },
	{ D3DXVECTOR3(1230,190,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(1170,330,0.0f),10,20,0 },
	{ D3DXVECTOR3(1200,330,0.0f),10,20,0 },
	{ D3DXVECTOR3(1230,330,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(1200,430,0.0f),10,20,0 },
	{ D3DXVECTOR3(1230,430,0.0f),10,20,0 },

	//���S
	{ D3DXVECTOR3(400,370,0.0f),10,20,0 },
	{ D3DXVECTOR3(440,400,0.0f),10,20,0 },
	{ D3DXVECTOR3(330,370,0.0f),10,20,0 },
	{ D3DXVECTOR3(360,370,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(800,370,0.0f),10,20,0 },
	{ D3DXVECTOR3(850,370,0.0f),10,20,0 },

	//
	{ D3DXVECTOR3(605,330,0.0f),10,20,0 },
	{ D3DXVECTOR3(605,200,0.0f),10,20,0 },

	{ D3DXVECTOR3(1230,190,0.0f),10,20,0 },

};

//=============================================================================
// �A�C�e���̏���������
//=============================================================================
void InitItem(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//�X�e�[�W���擾
	GAMESTAGE pStage;
	pStage = GetGameStage();

	// �A�C�e���̏��̏�����
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].nType = 0;
		g_aItem[nCntItem].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME1, &g_pTextureItem[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME2, &g_pTextureItem[2]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//�|���S���̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�|���S���̐F�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	g_nNumItem = 0;		//�A�C�e���̑������N���A

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();

	if (pStage == GAMESTAGE_SELECT)
	{	//�I����ʂŎg�p����A�C�e��
		for (nCntItem = 0; nCntItem < (sizeof g_aItemInfoStageSelect / sizeof(ItemInfoStageSelect)); nCntItem++)
		{
			SetItem(g_aItemInfoStageSelect[nCntItem].pos, g_aItemInfoStageSelect[nCntItem].fWidth, g_aItemInfoStageSelect[nCntItem].fHeight, g_aItemInfoStageSelect[nCntItem].nType);
		}
	}
	else if (pStage == GAMESTAGE1)
	{	//�X�e�[�W1�Ŏg�p����A�C�e��
		for (nCntItem = 0; nCntItem < (sizeof g_aItemInfoStage1 / sizeof(ItemInfoStage1)); nCntItem++)
		{	
			SetItem(g_aItemInfoStage1[nCntItem].pos, g_aItemInfoStage1[nCntItem].fWidth, g_aItemInfoStage1[nCntItem].fHeight, g_aItemInfoStage1[nCntItem].nType);
		}
	}
	else if (pStage == GAMESTAGE2)
	{	//�X�e�[�W2�Ŏg�p����A�C�e��
		for (nCntItem = 0; nCntItem < (sizeof g_aItemInfoStage2 / sizeof(ItemInfoStage2)); nCntItem++)
		{	
			SetItem(g_aItemInfoStage2[nCntItem].pos, g_aItemInfoStage2[nCntItem].fWidth, g_aItemInfoStage2[nCntItem].fHeight, g_aItemInfoStage2[nCntItem].nType);
		}
	}
}

//=============================================================================
// �A�C�e���̏I������
//=============================================================================
void UninitItem(void)
{
	int nCnt;

	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// �A�C�e���̍X�V����
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{	//�A�C�e�����g�p����Ă���
			if(g_aItem[nCntItem].nType == 0)
			{	//�R�C��
				//�J�E���^�[���Z
				g_aItem[nCntItem].nCounterAnim++;
				if ((g_aItem[nCntItem].nCounterAnim % ITEM_SPEED) == 0)
				{	//�A�C�e���̑���
					g_aItem[nCntItem].nPatternAnim++;		//�p�^�[��No.�X�V
				}

				//�e�N�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim  * 0.25f) + 0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim * 0.25f) + 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim * 0.25f) + 0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_aItem[nCntItem].nPatternAnim * 0.25f) + 0.25f, 1.0f);
			}
			else if (g_aItem[nCntItem].nType == 1)
			{	//���ɂ���
				//�e�N�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (g_aItem[nCntItem].nType == 2)
			{	//�s�[�}��
				//�e�N�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			//�A�C�e���̍��W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - MINUS, g_aItem[nCntItem].pos.y - MINUS, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + PLUS, g_aItem[nCntItem].pos.y - MINUS, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - MINUS, g_aItem[nCntItem].pos.y + PLUS, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + PLUS, g_aItem[nCntItem].pos.y + PLUS, 0.0f);
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �A�C�e���̕`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntItem,  2);
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ�
//=============================================================================
void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	int nCntItem;
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{	//�A�C�e�����g�p���Ă��Ȃ�
			//�A�C�e���̍��W�ݒ�
			g_aItem[nCntItem].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - MINUS, g_aItem[nCntItem].pos.y - MINUS, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + PLUS, g_aItem[nCntItem].pos.y - MINUS, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - MINUS, g_aItem[nCntItem].pos.y + PLUS, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + PLUS, g_aItem[nCntItem].pos.y + PLUS, 0.0f);

			g_aItem[nCntItem].nCounterAnim = 0;
			g_aItem[nCntItem].nPatternAnim = 0;
			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].bUse = true;		//�g�p���Ă����Ԃɂ���

			if (g_aItem[nCntItem].nType == 0)
			{	//�R�C���̂�
				g_nNumItem++;		//�R�C���̑��������Z����
			}
			break;							//�K���K�v
		}
	}
	pVtx += 4;
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �A�C�e���̏���
//=============================================================================
void CollisionItem(int nType)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntItem;

	//�v���C���[���擾
	Player * pPlayer;
	pPlayer = GetPlayer();

	//�X�e�[�W���擾
	GAMESTAGE pStage;
	pStage = GetGameStage();

	//�t�F�[�h���擾
	FADEGAME  g_fadeGame;
	g_fadeGame = GetFadeGame();
	 
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{	//�A�C�e�����g�p����Ă���
			if (g_aItem[nCntItem].nType == 0)
			{	//�R�C��
				if (g_aItem[nCntItem].pos.x > pPlayer->pos.x - PLAYER_WIDTH
					&& g_aItem[nCntItem].pos.x < pPlayer->pos.x + PLAYER_WIDTH
					&& g_aItem[nCntItem].pos.y > pPlayer->pos.y - PLAYER_HEIGHT
					&& g_aItem[nCntItem].pos.y < pPlayer->pos.y)
				{
					AddScore(100);
					PlaySound(SOUND_LABEL_SE_COIN);
					DeleteItem(nCntItem);
				}
			}
			else if (g_aItem[nCntItem].nType == 1)
			{	//���ɂ���
				if (g_aItem[nCntItem].bUse == true)
				{
					if (g_aItem[nCntItem].pos.x > pPlayer->pos.x - PLAYER_WIDTH + 10
						&& g_aItem[nCntItem].pos.x < pPlayer->pos.x + PLAYER_WIDTH + 10
						&& g_aItem[nCntItem].pos.y > pPlayer->pos.y - PLAYER_HEIGHT
						&& g_aItem[nCntItem].pos.y < pPlayer->pos.y)
					{
						pPlayer->state = PLAYERSTATE_SIZEUP;
						DeleteItem(nCntItem);

						if (g_fadeGame != FADE_OUT)
						{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
							//���[�h�ݒ�
							SetFadeGame(GAMESTAGE1);
						}
					}
				}
			}
			else if (g_aItem[nCntItem].nType == 2)
			{	//�s�[�}��
				if (g_aItem[nCntItem].bUse == true)
				{
					if (g_aItem[nCntItem].pos.x > pPlayer->pos.x - PLAYER_WIDTH + 10
						&& g_aItem[nCntItem].pos.x < pPlayer->pos.x + PLAYER_WIDTH + 10
						&& g_aItem[nCntItem].pos.y > pPlayer->pos.y - PLAYER_HEIGHT
						&& g_aItem[nCntItem].pos.y < pPlayer->pos.y)
					{
						pPlayer->state = PLAYERSTATE_SIZEDOWN;
						DeleteItem(nCntItem);

						if (g_fadeGame != FADE_OUT)
						{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
							//���[�h�ݒ�
							SetFadeGame(GAMESTAGE2);
						}
					}
				}
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �A�C�e������������
//=============================================================================
void DeleteItem(int nCntItem)
{
	g_nNumItem--;
	if (g_aItem[nCntItem].nType == 0)
	{	//�R�C����S�������
		SetExplosion(g_aItem[nCntItem].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f));
		g_aItem[nCntItem].bUse = false;

		if (g_nNumItem <= 0)
		{
			SetGameState(GAMESTATE_CLEAR);
		}
	}
}