//=============================================================================
//
// �G���� [enemy.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "enemy.h"
#include"main.h"
#include"explosion.h"
#include"bullet.h"
#include "game.h"
#include "score.h"
#include "effect.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TYPE_ENEMY		(4)												// �G�̎��
#define DAMAGE_STATE			(5)												//�_���[�W���
#define ENEMY_LIFE					(5)												//�G�̃��C�t
#define TEX_PATTAERN				(2)												//�p�^�[����
#define TEXTURE_NAME "data/TEXTURE/monster000_1.png"		//�e�N�X�`���̖��O
#define TEXTURE_NAME2 "data/TEXTURE/monster001_1.png"		//�e�N�X�`���̖��O
#define TEXTURE_NAME3 "data/TEXTURE/monster002_1.png"		//�e�N�X�`���̖��O
#define TEXTURE_NAME4 "data/TEXTURE/monster003_1.png"		//�e�N�X�`���̖��O

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];																	//�G�̏��
int g_nNumEnemy;																							//�G�̑���

//=============================================================================
// �G�̏���������
//=============================================================================
void InitEnemy(void)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].nCntAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nCntMove = 0;
		g_aEnemy[nCntEnemy].nChangeMove = 0;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME2, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME3, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME4, &g_apTextureEnemy[3]);

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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

	g_nNumEnemy = 0;		//�G�̑������N���A

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �G�̏I������
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
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
// �G�̍X�V����
//=============================================================================
void UpdateEnemy(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	int nCntEnemy = 0;
	float fMoveX = 0;		//�p�x�����߂邽�߂�X
	float fMoveY = 0;		//�p�x�����߂邽�߂�Y
	float fangle = 0;			//�p�x�����߂�
	float fMoveX2 = 0;		//X�̈ړ���
	float fMoveY2 = 0;		//Y�̈ړ���

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�|���S���̍��W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);

			g_aEnemy[nCntEnemy].nCntAnim++;				//�J�E���^�[���Z
			if ((g_aEnemy[nCntEnemy].nCntAnim % 40) == 0)
			{	//�|���S���̑���
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % 2;		//�p�^�[��No.�X�V
			}

			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f + 0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_aEnemy[nCntEnemy].nPatternAnim) * 0.5f + 0.5f, 1.0f);
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	//�G���g�p����Ă���
			//g_aEnemy[nCntEnemy].nCntBullet++;

			if (g_aEnemy[nCntEnemy].nCntMove > 150 || g_aEnemy[nCntEnemy].nCntMove < -150)
			{
				g_aEnemy[nCntEnemy].nChangeMove *= -1;
			}

			g_aEnemy[nCntEnemy].nCntMove += g_aEnemy[nCntEnemy].nChangeMove;
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].nChangeMove;

			switch (g_aEnemy[nCntEnemy].state)
			{	//�G�̏�Ԋm�F
			case ENEMYSTATE_NORMAL:	//�G���ʏ��Ԃ̎�
				//��莞�Ԍo��
				if ((rand() % 600) == 0)
				{	//��莞�ԂɂȂ�����G�͒e�������Ă���
					//�v���C���[���擾
					Player * pPlayer;
					pPlayer = GetPlayer();

					//�G�̒e���v���C���[�Ɍ������Č����Ă���
					fMoveX = pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x;		//�p�x��X�����߂�
					fMoveY = pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y;		//�p�x��Y�����߂�
					fangle = atan2f(fMoveX,fMoveY);												//�p�x���߂�

					fMoveX2 = sinf(fangle) * 10.0f;
					fMoveY2 = cosf(fangle) * 10.0f;

					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(fMoveX2,fMoveY2, 0.0f),BULLETTYPE_ENEMY);
				}
				break;

			case ENEMYSTATE_DAMADE:	//�G���_���[�W���󂯂�
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{	//�_���[�W��Ԃ��I�������A�̗͎c���Ă�
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//�G�̃_���\�W�F�ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}	
				break;
			}
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{	//�G���g�p����Ă���
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//�|���S���̕`��
 			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEnemy, 2);
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType, int ChangeMove)
{
	int nCntEnemy;
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{	//�G���g�p����Ă��Ȃ�
			//�G�̍��W�ݒ�
			g_aEnemy[nCntEnemy].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y - 25, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 25, g_aEnemy[nCntEnemy].pos.y + 25, 0.0f);

			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nCntAnim = 0;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;
			g_aEnemy[nCntEnemy].nLife = ENEMY_LIFE;
			g_aEnemy[nCntEnemy].nCntMove = 0;
			g_aEnemy[nCntEnemy].nChangeMove = ChangeMove;
			g_aEnemy[nCntEnemy].bUse = true;	//�g�p���Ă����Ԃɂ���
			g_nNumEnemy++;								//�G�̑��������Z����
			break;													//�K���K�v
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �G�̎擾
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void HitEnemy(int nCntEnemy,int nDamage)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{	//���C�t��0�ɂȂ�����
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		if (g_aEnemy[nCntEnemy].nType == 0)
		{	//������̔����̐F
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.9f, 0.4f, 0.1f, 0.7f));
			AddScore(8000);
			g_aEnemy[nCntEnemy].bUse = false;
		}
		else if (g_aEnemy[nCntEnemy].nType == 1)
		{	//�݂�����̔����̐F
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.1f, 0.4f, 0.4f, 0.7f));
			AddScore(6000);
			g_aEnemy[nCntEnemy].bUse = false;
		}
		else if (g_aEnemy[nCntEnemy].nType == 2)
		{	//�ނ炳���̔����̐F
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.6f, 0.1f, 0.8f, 0.7f));
			AddScore(4000);
			g_aEnemy[nCntEnemy].bUse = false;
		}
		else if (g_aEnemy[nCntEnemy].nType == 3)
		{	//���݂ǂ�̔����̐F
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.1f, 0.7f, 0.3f, 0.7f));
			AddScore(2000);
			g_aEnemy[nCntEnemy].bUse = false;
		}

		g_nNumEnemy--;
		if (g_nNumEnemy <= 0)
		{	//�G���S�ł�����
			SetGameState(GAMESTATE_CLEAR);
		}
	}
	else
	{	//���C�t���c���Ă���
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMADE;
		g_aEnemy[nCntEnemy].nCounterState = DAMAGE_STATE;		//�_���[�W��Ԃ̎���

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aEnemy[nCntEnemy].nType == 0)
		{	//�G�r�����̃_���[�W�̐F
			//�_���[�W�̐F�ݒ�
			pVtx[nCntEnemy * 4].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
			pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
			pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
			pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(0, 0.5f, 1.0f, 1.0f);
		}
		else
		{	//���̑��̓G
			//�_���[�W�̐F�ݒ�
			pVtx[nCntEnemy * 4].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
			pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0, 0, 1.0f);
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();
	}
}
