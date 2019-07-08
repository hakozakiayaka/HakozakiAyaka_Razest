//=============================================================================
//
// �u���b�N���� [block.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "block.h"
#include "input.h"
#include"main.h"
#include"player.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BLOCK_GROUND "data/TEXTURE/ground.png"		//�e�N�X�`���̖��O
#define BLOCK_YELLOW "data/TEXTURE/block400.jpg"		//�A�C�e���̉��̃u���b�N
#define BLOCK_NORMAL "data/TEXTURE/block000.jpg"	//�u���b�N

#define MAX_TEXTURE								(3)						//�e�N�X�`���̍ő吔

#define MAX_BLOCK									(300)					// �u���b�N�̍ő吔
#define OUTSIDE										(20)						//�u���b�N�̊O
#define BLOCK_HEIGHT								(30)						//�u���b�N�̍���
#define BLOCK_WIDTH								(100)					//�u���b�N�̍���
#define PLAYER_HEIGHT							(70)						//�v���C���[�̍���

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];																//�u���b�N�̏��

//=============================================================================
// �u���b�N���̃f�[�^
//=============================================================================
BlockInfoSelect g_aBlockInfoSelect[] =
{	//�I����ʂ̃u���b�N�ݒ�
	//�n��
	{ D3DXVECTOR3(0, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(100, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(200, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(300, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(400, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(500, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(600, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(700, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(800, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(900, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1000, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1100, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1200, 660, 0.0f),100,60,0 },

	//�A�C�e�����̃u���b�N
	//���ɂ���
	{ D3DXVECTOR3(250, 630, 0.0f),30,30,1 },
	{ D3DXVECTOR3(280, 630, 0.0f),30,30,1 },
	{ D3DXVECTOR3(250, 600, 0.0f),30,30,1 },
	{ D3DXVECTOR3(280, 600, 0.0f),30,30,1 },
	//�s�[�}��
	{ D3DXVECTOR3(950, 630, 0.0f),30,30,1 },
	{ D3DXVECTOR3(980, 630, 0.0f),30,30,1 },
	{ D3DXVECTOR3(950, 600, 0.0f),30,30,1 },
	{ D3DXVECTOR3(980, 600, 0.0f),30,30,1 },
};

BlockInfoStage1 g_aBlockInfoStage1[] =
{	//���ɂ���X�e�[�W�̐ݒ�
	//�n��
	{ D3DXVECTOR3(0, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(100, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(200, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(300, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(400, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(500, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(600, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(700, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(800, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(900, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(1000, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(1100, 690, 0.0f),100,30,0 },
	{ D3DXVECTOR3(1200, 690, 0.0f),100,30,0 },

	//��i�ځA������--------------------------------
	{ D3DXVECTOR3(20, 530, 0.0f),120,60 ,2},		//1�i�ځ@��

	{ D3DXVECTOR3(240, 450, 0.0f),120,60,2 },	//2�i�ځ@�E

	{ D3DXVECTOR3(10, 310, 0.0f),120,60,2 },		//3�i�ځ@��

	//�E��
	{ D3DXVECTOR3(240, 190, 0.0f),120,60,2 },		//3�i�ځ@��
	{ D3DXVECTOR3(340, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(440, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(540, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(640, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(740, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(840, 190, 0.0f),100,60,2 },
	{ D3DXVECTOR3(940, 190, 0.0f),100,60,2 },

	//����
	{ D3DXVECTOR3(1150, 310, 0.0f),120,60,2 },
	{ D3DXVECTOR3(900, 450, 0.0f),120,60,2 },
	{ D3DXVECTOR3(1090, 530, 0.0f),120,60,2 },
};

BlockInfoStage2 g_aBlockInfoStage2[] =
{	//�s�[�}���X�e�[�W�̐ݒ�
	//�n��
	{ D3DXVECTOR3(0, 660, 0.0f),100,60 ,0},
	{ D3DXVECTOR3(100, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(200, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(300, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(400, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(500, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(600, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(700, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(800, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(900, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1000, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1100, 660, 0.0f),100,60,0 },
	{ D3DXVECTOR3(1200, 660, 0.0f),100,60,0 },

	//2�i��
	{ D3DXVECTOR3(0, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(100, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(200, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(300, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(400, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(500, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(600, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(700, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(800, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1000, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1100, 580, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1200, 580, 0.0f),100,30,2 },

	//
	{ D3DXVECTOR3(0, 460, 0.0f),100,30,2 },
	{ D3DXVECTOR3(100, 460, 0.0f),100,30,2 },

	{ D3DXVECTOR3(0, 340, 0.0f),100,30,2 },
	{ D3DXVECTOR3(70, 340, 0.0f),100,30,2 },

	{ D3DXVECTOR3(0, 220, 0.0f),100,30,2 },
	{ D3DXVECTOR3(50, 220, 0.0f),100,30,2 },

	{ D3DXVECTOR3(0, 100, 0.0f),100,30,2 },
	{ D3DXVECTOR3(30, 100, 0.0f),100,30,2 },

	//���@�ォ��
	{ D3DXVECTOR3(1200, 100, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1170, 100, 0.0f),100,30,2 },

	{ D3DXVECTOR3(1200, 220, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1140, 220, 0.0f),100,30,2 },

	{ D3DXVECTOR3(1200, 360, 0.0f),100,30,2 },
	{ D3DXVECTOR3(1110, 360, 0.0f),100,30,2 },

	{ D3DXVECTOR3(1200, 460, 0.0f),100,30,2 },

	//���S
	{ D3DXVECTOR3(400, 400, 0.0f),30,30,2 },
	{ D3DXVECTOR3(800, 400, 0.0f),30,30,2 },
	{ D3DXVECTOR3(585, 360, 0.0f),30,30,2 },

	{ D3DXVECTOR3(960, 140, 0.0f),30,30,2 },

};

//=============================================================================
// �u���b�N�̏���������
//=============================================================================
void InitBlock(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//�X�e�[�W���擾
	GAMESTAGE pStage;
	pStage = GetGameStage();

	// �u���b�N�̏��̏�����
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0;
		g_aBlock[nCntBlock].fHeight = 0;
		g_aBlock[nCntBlock].nCntType = 0;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_NORMAL;
		g_aBlock[nCntBlock].bLand = false;
		g_aBlock[nCntBlock].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BLOCK_GROUND, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_YELLOW, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_NORMAL, &g_pTextureBlock[2]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//�u���b�N�̍��W�ݒ�
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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
	
	switch (pStage)
	{
	case GAMESTAGE_SELECT:
		for (nCntBlock = 0; nCntBlock < (sizeof g_aBlockInfoSelect / sizeof(BlockInfoSelect)); nCntBlock++)
		{
			SetBlock(g_aBlockInfoSelect[nCntBlock].pos, g_aBlockInfoSelect[nCntBlock].fWidth, g_aBlockInfoSelect[nCntBlock].fHeight, g_aBlockInfoSelect[nCntBlock].nTexType);
		}
		break;

	case GAMESTAGE1:
		for (nCntBlock = 0; nCntBlock < (sizeof g_aBlockInfoStage1 / sizeof(BlockInfoStage1)); nCntBlock++)
		{
			SetBlock(g_aBlockInfoStage1[nCntBlock].pos, g_aBlockInfoStage1[nCntBlock].fWidth, g_aBlockInfoStage1[nCntBlock].fHeight, g_aBlockInfoStage1[nCntBlock].nTexType);
		}
		break;

	case GAMESTAGE2:
		for (nCntBlock = 0; nCntBlock < (sizeof g_aBlockInfoStage2 / sizeof(BlockInfoStage2)); nCntBlock++)
		{
			SetBlock(g_aBlockInfoStage2[nCntBlock].pos, g_aBlockInfoStage2[nCntBlock].fWidth, g_aBlockInfoStage2[nCntBlock].fHeight, g_aBlockInfoStage2[nCntBlock].nTexType);
		}
		break;
	}
}

//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void UninitBlock(void)
{
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_TEXTURE; nCntBlock++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void UpdateBlock(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntBlock;

	//�v���C���[���擾
	Player * pPlayer;
	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{	//�u���b�N���g�p����Ă���

			//�u���b�N�̑傫�����W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�X�e�[�W���擾
	GAMESTAGE pStage;
	pStage = GetGameStage();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse == true)
			{
					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nTexType]);

				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBlock, 2);
			}
		}
}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nTexType)
{	
	int nCntBlock;
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++,pVtx += 4)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{	//�u���b�N���g�p����Ă���

			g_aBlock[nCntBlock].pos = pos;
			//�u���b�N�̑傫�����W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].nTexType = nTexType;
			g_aBlock[nCntBlock].bUse = true;										//�g�p���Ă����Ԃɂ���
			break;																					//�K���K�v
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̓����蔻�菈��
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove,float fWidth,float fHeight)
{
	//�v���C���[���擾
	Player * pPlayer;
	pPlayer = GetPlayer();

	int nCntBlock;
	bool bLand = false;		//���n�������ǂ���

	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{	//�u���b�N���g���Ă��邩�ǂ���
			g_aBlock[nCntBlock].bLand = false;

			if (pPlayer->state == PLAYERSTATE_NORMAL)
			{	//�ʏ���
				if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - OUTSIDE && g_aBlock[nCntBlock].pos.x <= pPos->x + OUTSIDE)
				{	//�ォ��A�u���b�N�̕��Ƀv���C���[�������Ă邩�ǂ����i����Ă邩�ǂ����j
					if (g_aBlock[nCntBlock].pos.y >= pPosOld->y &&	//�v���C���[�O��̈ʒu���u���b�N�̍��������ゾ������
						g_aBlock[nCntBlock].pos.y <= pPos->y)				//�v���C���[���݂̈ʒu���u���b�N�̍�����������������
					{	//���m�����n�ɂ߂荞��
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y;		//�n�ʂ̍���
						pMove->y = 0.0f;
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT <= pPosOld->y &&		//�v���C���[�O��̈ʒu���u���b�N�̈ʒu��艺��������
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT >= pPos->y)						//�v���C���[�̌��݂̈ʒu���u���b�N�̈ʒu�����ゾ������	
					{	//��[��]���߂荞��
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT;
						pMove->y = 0.0f;
					}
					//���̓����蔻��
					if (g_aBlock[nCntBlock].bLand == false)
					{	//�u���b�N�̓����蔻�肪�g�p����Ă��邩�ǂ���
						if (g_aBlock[nCntBlock].pos.y <= pPosOld->y &&																				//�v���C���[���݂̈ʒu���u���b�N�̈ʒu���ゾ������
							g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT >= pPos->y)		//�v���C���[���݂̈ʒu���u���b�N�̈ʒu��艺��������	
						{
							bLand = true;
							g_aBlock[nCntBlock].bLand = true;
							pPos->x = pPosOld->x;
							pMove->x = 0.0f;
						}
					}
				}
			}
			else if (pPlayer->state == PLAYERSTATE_SIZEUP)
			{	//���ɂ���
				if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - OUTSIDE * 1.5f && g_aBlock[nCntBlock].pos.x <= pPos->x + OUTSIDE * 1.5f)
				{	//�ォ��A�u���b�N�̕��Ƀv���C���[�������Ă邩�ǂ����i����Ă邩�ǂ����j
					if (g_aBlock[nCntBlock].pos.y >= pPosOld->y &&	//�v���C���[�O��̈ʒu���u���b�N�̍��������ゾ������
						g_aBlock[nCntBlock].pos.y <= pPos->y)				//�v���C���[���݂̈ʒu���u���b�N�̍�����������������
					{	//���m�����n�ɂ߂荞��
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y;		//�n�ʂ̍���
						pMove->y = 0.0f;
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT * 1.5f <= pPosOld->y &&		//�v���C���[�O��̈ʒu���u���b�N�̈ʒu��艺��������
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT * 1.5f >= pPos->y)						//�v���C���[�̌��݂̈ʒu���u���b�N�̈ʒu�����ゾ������	
					{	//��[��]���߂荞��
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT * 1.5f;
						pMove->y = 0.0f;
					}
					//���̓����蔻��
					if (g_aBlock[nCntBlock].bLand == false)
					{	//�u���b�N�̓����蔻�肪�g�p����Ă��邩�ǂ���
						if (g_aBlock[nCntBlock].pos.y <= pPosOld->y &&																				//�v���C���[���݂̈ʒu���u���b�N�̈ʒu���ゾ������
							g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT * 1.5f >= pPos->y)		//�v���C���[���݂̈ʒu���u���b�N�̈ʒu��艺��������	
						{
							bLand = true;
							g_aBlock[nCntBlock].bLand = true;
							pPos->x = pPosOld->x;
							pMove->x = 0.0f;
						}
					}
				}
			}
			else if (pPlayer->state == PLAYERSTATE_SIZEDOWN)
			{	//�s�[�}��
				if (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth >= pPos->x - OUTSIDE / 2 && g_aBlock[nCntBlock].pos.x <= pPos->x + OUTSIDE / 2)
				{	//�ォ��A�u���b�N�̕��Ƀv���C���[�������Ă邩�ǂ����i����Ă邩�ǂ����j
					if (g_aBlock[nCntBlock].pos.y >= pPosOld->y &&	//�v���C���[�O��̈ʒu���u���b�N�̍��������ゾ������
						g_aBlock[nCntBlock].pos.y <= pPos->y)				//�v���C���[���݂̈ʒu���u���b�N�̍�����������������
					{	//���m�����n�ɂ߂荞��
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y;		//�n�ʂ̍���
						pMove->y = 0.0f;
					}
					else if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT / 2 <= pPosOld->y &&		//�v���C���[�O��̈ʒu���u���b�N�̈ʒu��艺��������
						g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT / 2 >= pPos->y)						//�v���C���[�̌��݂̈ʒu���u���b�N�̈ʒu�����ゾ������	
					{	//��[��]���߂荞��
						bLand = true;
						g_aBlock[nCntBlock].bLand = true;
						pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT / 2;
						pMove->y = 0.0f;
					}
					//���̓����蔻��
					if (g_aBlock[nCntBlock].bLand == false)
					{	//�u���b�N�̓����蔻�肪�g�p����Ă��邩�ǂ���
						if (g_aBlock[nCntBlock].pos.y <= pPosOld->y &&																				//�v���C���[���݂̈ʒu���u���b�N�̈ʒu���ゾ������
							g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + PLAYER_HEIGHT / 2 >= pPos->y)		//�v���C���[���݂̈ʒu���u���b�N�̈ʒu��艺��������	
						{
							bLand = true;
							g_aBlock[nCntBlock].bLand = true;
							pPos->x = pPosOld->x;
							pMove->x = 0.0f;
						}
					}
				}
			}
		}
	}
	return bLand;
}