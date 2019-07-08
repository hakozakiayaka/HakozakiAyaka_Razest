//=============================================================================
//
// �G���� [enemy.cpp]
// Author :Gokan akane
//
//=============================================================================
#include "enemy.h"
#include "Game.h"
#include "fade.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(4)									// �G�̎��
#define ENEMY_TEXTURE0		"data\\TEXTURE\\Clow.png"		//�G�̃e�N�X�`���̖��O0
#define PLAYER_PATTERN		(2)
#define ENEMY_SIZE			(60)

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEnemy = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];										//�G�̏��
int g_nNumEnemy;												//�G�̑���

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;// ���_���̍쐬
	int nCntEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	// �G�̏��̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nCntAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nDirectionMove = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOMAL;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	g_nNumEnemy = 0;

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE0, &g_pTextureEnemy);

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
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);//��ڂ̒��_�̏ꏊ�w��
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);//��ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���炷
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEnemy != NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;// ���_���̍쐬
	Player*pPlayer;
	pPlayer = GetPlayer();


	//���_�o�b�t�@�����b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{

			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NOMAL:
				//���ړ�
				g_aEnemy[nCntEnemy].nDirectionMove = 1;
				g_aEnemy[nCntEnemy].CntMove = 3;
				g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].CntMove;

				break;

			case ENEMYSTATE_DAMAGE:
				//���ړ�
				g_aEnemy[nCntEnemy].nDirectionMove = 0;
				g_aEnemy[nCntEnemy].CntMove = 3;
				g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].CntMove;

				break;

			}
			g_aEnemy[nCntEnemy].nCntAnim++;//�J�E���^�[�̉��Z

			if ((g_aEnemy[nCntEnemy].nCntAnim % 30) == 0)//��莞�Ԃ��o��
			{
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % PLAYER_PATTERN;		//�p�^�[�����X�V
			}

			/*if (g_aEnemy[nCntEnemy].pos.x < -50.0f)
			{
				g_aEnemy[nCntEnemy].bUse = false;
			}
			if (g_aEnemy[nCntEnemy].pos.x > SCREEN_WIDTH + 50.0f)
			{
				g_aEnemy[nCntEnemy].bUse = false;
			}*/

			//�����蔻��
			if (pPlayer->pos.x + 80 > g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE&&
				pPlayer->pos.x - 80 < g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE&&
				pPlayer->pos.y + 40 > g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE&&
				pPlayer->pos.y - 40 < g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE)
			{//�v���C���[���G�̕��ɓ����Ă��邩�ǂ���
				HitPlayer(1);
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			}

			//�e�N�X�`�����W�̐ݒ�
			if (g_aEnemy[nCntEnemy].nDirectionMove == 0)
			{//�E�����̎�
				pVtx[1].tex = D3DXVECTOR2(0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[0].tex = D3DXVECTOR2(0.5f + 0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 1.0f);
			}
			if (g_aEnemy[nCntEnemy].nDirectionMove == 1)
			{//���Ɍ����Ă���Ƃ�
				pVtx[0].tex = D3DXVECTOR2(0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * g_aEnemy[nCntEnemy].nPatternAnim, 1.0f);
			}

			//���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);//��ڂ̒��_�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);;//��ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);//�O�ڂ̒��_�̏ꏊ�w��i�E���j

		}
		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �`�揈��
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
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)//�G���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnemy);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 4,
				2);
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos)
{
	int nCntEnemy;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//���_����ݒ�
			g_aEnemy[nCntEnemy].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);//����̒��_X�̏ꏊ�w��
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);//����̒��_X�̏ꏊ�w��

			g_aEnemy[nCntEnemy].bUse = true;
			g_nNumEnemy++;

			break;
		}
		pVtx += 4;//�Y���̈ʒu�܂Ői�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}
//=============================================================================
// �G�̎擾
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}