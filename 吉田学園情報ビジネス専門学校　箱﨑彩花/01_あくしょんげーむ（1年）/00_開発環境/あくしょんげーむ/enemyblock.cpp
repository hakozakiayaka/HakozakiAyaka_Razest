//=============================================================================
//
// �G�u���b�N���� [enemyblock.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "enemyblock.h"
#include"main.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_NAME "data/TEXTURE/monster000_1.png"		//�e�N�X�`���̖��O
#define	MAX_ENEMYBLOCK	(256)	// �G�u���b�N�u���b�N�̍ő吔

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureEnemy = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
ENEMYBLOCK g_aEnemyBlock[MAX_ENEMYBLOCK];				//�G�u���b�N�̏��
int g_nNumEnemyBlock;																	//�G�u���b�N�̑���

//=============================================================================
// �G�u���b�N�̏���������
//=============================================================================
void InitEnemyBlock(void)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�u���b�N�̏��̏�����
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMYBLOCK; nCntEnemy++)
	{
		g_aEnemyBlock[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyBlock[nCntEnemy].state = ENEMYBLOCKSTATE_NORMAL;
		g_aEnemyBlock[nCntEnemy].nCounterState = 0;
		g_aEnemyBlock[nCntEnemy].fHeight = 0;
		g_aEnemyBlock[nCntEnemy].fWidth = 0;
		g_aEnemyBlock[nCntEnemy].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_apTextureEnemy);

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMYBLOCK,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMYBLOCK; nCntEnemy++)
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
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	g_nNumEnemyBlock = 0;		//�G�u���b�N�̑������N���A

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �G�u���b�N�̏I������
//=============================================================================
void UninitEnemyBlock(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_ENEMYBLOCK; nCntTex++)
	{
		if (g_apTextureEnemy != NULL)
		{
			g_apTextureEnemy ->Release();
			g_apTextureEnemy = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// �G�u���b�N�̍X�V����
//=============================================================================
void UpdateEnemyBlock(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntEnemyBlock = 0;

	//�v���C���[���擾
	Player * pPlayer;
	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemyBlock = 0; nCntEnemyBlock < MAX_ENEMYBLOCK; nCntEnemyBlock++)
	{	
		if (g_aEnemyBlock[nCntEnemyBlock].bUse == true)
		{
			//�u���b�N�̑傫�����W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemyBlock].pos.x, g_aEnemyBlock[nCntEnemyBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemyBlock].pos.x + g_aEnemyBlock[nCntEnemyBlock].fWidth, g_aEnemyBlock[nCntEnemyBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemyBlock].pos.x, g_aEnemyBlock[nCntEnemyBlock].pos.y + g_aEnemyBlock[nCntEnemyBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemyBlock].pos.x + g_aEnemyBlock[nCntEnemyBlock].fWidth, g_aEnemyBlock[nCntEnemyBlock].pos.y + g_aEnemyBlock[nCntEnemyBlock].fHeight, 0.0f);
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
}

//=============================================================================
// �G�u���b�N�̕`�揈��
//=============================================================================
void DrawEnemyBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMYBLOCK; nCntEnemy++)
	{
		if (g_aEnemyBlock[nCntEnemy].bUse == true)
		{	//�G�u���b�N���g�p����Ă���
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy);

			//�|���S���̕`��
 			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEnemy, 2);
		}
	}
}

//=============================================================================
// �G�u���b�N�̐ݒ�
//=============================================================================
void SetEnemyBlock(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nCntEnemy;
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMYBLOCK; nCntEnemy++)
	{
		if (g_aEnemyBlock[nCntEnemy].bUse == false)
		{	//�G�u���b�N���g�p����Ă��Ȃ�
			//�G�u���b�N�̍��W�ݒ�
			g_aEnemyBlock[nCntEnemy].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemy].pos.x - 25, g_aEnemyBlock[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemy].pos.x + 25, g_aEnemyBlock[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemy].pos.x - 25, g_aEnemyBlock[nCntEnemy].pos.y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemyBlock[nCntEnemy].pos.x + 25, g_aEnemyBlock[nCntEnemy].pos.y + 25, 0.0f);

			g_aEnemyBlock[nCntEnemy].state = ENEMYBLOCKSTATE_NORMAL;
			g_aEnemyBlock[nCntEnemy].nCounterState = 0;
			g_aEnemyBlock[nCntEnemy].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_nNumEnemyBlock++;									//�G�u���b�N�̑��������Z����
			break;																//�K���K�v
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �G�u���b�N�̃_���[�W����
//=============================================================================
void CollisionEnemyBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeight)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);


		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();
}
