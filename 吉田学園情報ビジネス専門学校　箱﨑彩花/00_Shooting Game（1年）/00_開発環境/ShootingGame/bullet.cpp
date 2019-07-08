//=============================================================================
//
// �e���� [bullet.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include"main.h"
#include"player.h"
#include"explosion.h"
#include"enemy.h"
#include "effect.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_BULLET								(300)									// �e�̍ő吔
#define LIFE												(50)										//�e�̔򋗗�
#define POLYGON_RANGE							(30)										//�e���G�ɓ�����Ƃ��͈̔�
#define BULLET_TEXTURE_NAME "data/TEXTURE/bullet002.png"	//�e�N�X�`���̖��O

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nLife;							//����
	BULLETTYPE type;			//�e�̎��
	bool bUse;						//�g�p���Ă��邩�ǂ���
} Bullet;

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];												//�e�̏��

//=============================================================================
// �e�̏���������
//=============================================================================
void InitBullet(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURE_NAME, &g_pTextureBullet);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�e�̍��W�ݒ�
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
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �e�̏I������
//=============================================================================
void UninitBullet(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{	//�e���g�p����Ă���
			int nCntEnemy;
			Enemy * pEnemy;

			//�e�̈ʒu���ړ�������
			//g_aBullet[nCntBullet].pos -= D3DXVECTOR3(0.0f,10.0f,0.0f);
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{	//�v���C���[�̒e
				//�G�̎擾
				pEnemy = GetEnemy();
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 0.3f, 0.5f, 1.0f), 20.0f, 20);

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{	//�G���g�p����Ă���
						if (g_aBullet[nCntBullet].pos.x > pEnemy->pos.x - POLYGON_RANGE 
							&& g_aBullet[nCntBullet].pos.x < pEnemy->pos.x + POLYGON_RANGE 
							&& g_aBullet[nCntBullet].pos.y > pEnemy->pos.y - POLYGON_RANGE 
							&& g_aBullet[nCntBullet].pos.y < pEnemy->pos.y + POLYGON_RANGE)
						{	//�����蔻��
							HitEnemy(nCntEnemy, 1);
							PlaySound(SOUND_LABEL_SE_HIT000);
							g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
						}
					}
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{	//�G�̒e
				Player * pPlayer;

				//�v���C���[�̎擾
				pPlayer = GetPlayer();
				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 16.0f, 10);

				if (pPlayer ->state == PLAYERSTATE_NORMAL)
				{
					if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - POLYGON_RANGE
						&& g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + POLYGON_RANGE
						&& g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - POLYGON_RANGE
						&& g_aBullet[nCntBullet].pos.y < pPlayer->pos.y + POLYGON_RANGE)
					{	//�����蔻��
						HitPlayer(1); 

						PlaySound(SOUND_LABEL_SE_HIT001);
						g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
					}
				}
			}

			//�e�̑傫�����W�ݒ�
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x -10, g_aBullet[nCntBullet].pos.y -10 ,0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x +10, g_aBullet[nCntBullet].pos.y -10, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x -10, g_aBullet[nCntBullet].pos.y +10, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x +10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);

			if (30 + g_aBullet[nCntBullet].pos.y < 0 || 30 -  g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT)
			{
				g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
			}

			//��莞�Ԍo��
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	// �|���S���̕`��
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet,  2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move ,BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			//�e�̑傫�����W�ݒ�
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_aBullet[nCntBullet].nLife = LIFE;
			break;													//�K���K�v
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}