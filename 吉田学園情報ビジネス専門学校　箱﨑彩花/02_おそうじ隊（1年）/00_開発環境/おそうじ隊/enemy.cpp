//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "enemy.h"
#include "shadow.h"
#include "fade.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "model.h"
#include "sound.h"			//�T�E���h

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_TEX	 "data/TEXTURE/enemy.png"				//�e�N�X�`���̓ǂݍ���
#define ENEMY_TEX1 "data/TEXTURE/enemy1.png"			//�e�N�X�`���̓ǂݍ���

#define MAX_TEX						(2)										//�e�N�X�`���̍ő吔
#define ENEMY_SIZE					(20.0f)									//�G�l�~�[�̃T�C�Y
#define BULLET_SPEED			(1.0f)									//�e�̃X�s�[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;	//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEnemy[MAX_TEX] = {};				//�e�N�X�`���ւ̃|�C���^
Enemy g_Enemy[MAX_ENEMY];
int g_nNumEnemy;
int g_nPosZ = rand() % 600;

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_Enemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].nCntAnim = 0;
		g_Enemy[nCntEnemy].nPatternAnim = 0;
		g_Enemy[nCntEnemy].bUse = false;
	}
	g_nNumEnemy = 0;		//�r���{�[�h�̖�����������

	// ���_���̍쐬
	MakeVertexEnemy(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	//�e�N�X�`���̊J��
	for (int nCntEnemy = 0; nCntEnemy < MAX_TEX; nCntEnemy++)
	{
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();
			g_pTextureEnemy[nCntEnemy] = NULL;
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
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	VERTEX_3D * pVtx;								//���_���̃|�C���^
	FADE g_fade = GetFade();					//�t�F�[�h���擾
	Player * pPlayer = GetPlayer();			//�v���C���[���擾
	float fMoveX = 0;								//�p�x�����߂�X
	float fMoveZ = 0;								//�p�x�����߂�Z
	float fMoveX2 = 0;								//X�̈ړ���
	float fMoveZ2 = 0;								//Z�̈ړ���
	float fAngle = 0;									//�p�x�����߂�

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//�G���e����
			if ((rand() % 100 == 0))		//�������傫���قǁA�e�̐�������
			{
				//�G�̒e���v���C���[�Ɍ������Č����Ă���
				fMoveX = pPlayer->pos.x - g_Enemy[nCntEnemy].pos.x;		//�p�x��X�����߂�
				fMoveZ = pPlayer->pos.z - g_Enemy[nCntEnemy].pos.z;		//�p�x��Y�����߂�
				fAngle = atan2f(fMoveX, fMoveZ);											//�p�x���߂�

				fMoveX2 = sinf(fAngle) * BULLET_SPEED;
				fMoveZ2 = cosf(fAngle) * BULLET_SPEED;

				PlaySound(SOUND_LABEL_SE_SHOT000);
				SetBullet(g_Enemy[nCntEnemy].pos, D3DXVECTOR3(fMoveX2, 0.0f, fMoveZ2), BULLETTYPE_ENEMY);
			}

			if (g_Enemy[nCntEnemy].pos.x + 20 > pPlayer->pos.x
				&& g_Enemy[nCntEnemy].pos.x - 20 < pPlayer->pos.x
				&& g_Enemy[nCntEnemy].pos.z + 20 > pPlayer->pos.z
				&& g_Enemy[nCntEnemy].pos.z - 20 < pPlayer->pos.z)
			{	//�����蔻��i�G���v���C���[�ɓ����������̏����j
				AddScore(2000);
				PlaySound(SOUND_LABEL_SE_HIT000);
				SetExplosion(D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y + 10, g_Enemy[nCntEnemy].pos.z), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
				DeleteEnemy(nCntEnemy);
				g_nPosZ = rand() % 600;
				SetEnemy(D3DXVECTOR3(rand() % 600, g_Enemy[nCntEnemy].pos.y, -g_nPosZ), g_Enemy[nCntEnemy].rot, rand() % 2);
			}

			//�G�̃A�j���[�V����
			g_Enemy[nCntEnemy].nCntAnim++;
			if ((g_Enemy[nCntEnemy].nCntAnim % 10) == 0)
			{
				g_Enemy[nCntEnemy].nPatternAnim = (g_Enemy[nCntEnemy].nPatternAnim + 1) % 2;
			}

			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2((g_Enemy[nCntEnemy].nPatternAnim * 0.5f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_Enemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_Enemy[nCntEnemy].nPatternAnim * 0.5f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_Enemy[nCntEnemy].nPatternAnim * 0.5f) + 0.5f, 1.0f);

			//�e�̈ʒu�ݒ�
			SetPositionShadow(g_Enemy[nCntEnemy].nIdxEnemyShadow, g_Enemy[nCntEnemy].pos);
		}

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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			//�v�Z�p�}�g���b�N�X
	int nCntEnemy;

	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorldEnemy);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�t�s��̐ݒ�
			g_Enemy[nCntEnemy].mtxWorldEnemy._11 = mtxView._11;
			g_Enemy[nCntEnemy].mtxWorldEnemy._12 = mtxView._21;
			g_Enemy[nCntEnemy].mtxWorldEnemy._13 = mtxView._31;
			g_Enemy[nCntEnemy].mtxWorldEnemy._21 = mtxView._12;
			g_Enemy[nCntEnemy].mtxWorldEnemy._22 = mtxView._22;
			g_Enemy[nCntEnemy].mtxWorldEnemy._23 = mtxView._32;
			g_Enemy[nCntEnemy].mtxWorldEnemy._31 = mtxView._13;
			g_Enemy[nCntEnemy].mtxWorldEnemy._32 = mtxView._23;
			g_Enemy[nCntEnemy].mtxWorldEnemy._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorldEnemy, &g_Enemy[nCntEnemy].mtxWorldEnemy, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorldEnemy);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnemy[g_Enemy[nCntEnemy].nTexType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexEnemy(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//���_���̃|�C���^
	int nCntEnemy;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX, &g_pTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEX1, &g_pTextureEnemy[1]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-ENEMY_SIZE, ENEMY_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-ENEMY_SIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(ENEMY_SIZE, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTexType)
{
	//���f���̎擾
	Model * pModel = GetModel();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == false)
		{
			g_Enemy[nCntEnemy].pos = pos;
			if (pModel->pos.x + pModel->vtxMaxModel.x >= g_Enemy[nCntEnemy].pos.x 
				&& pModel->pos.x + pModel->vtxMinModel.x <= g_Enemy[nCntEnemy].pos.x
				&& pModel->pos.z + pModel->vtxMaxModel.z >= g_Enemy[nCntEnemy].pos.z
				&& pModel->pos.z + pModel->vtxMinModel.z <= g_Enemy[nCntEnemy].pos.z)
			{
				SetEnemy(D3DXVECTOR3(rand() % 600, g_Enemy[nCntEnemy].pos.y, -g_nPosZ), g_Enemy[nCntEnemy].rot, rand() % 2);
				break;
			}
			g_Enemy[nCntEnemy].rot = rot;
			g_Enemy[nCntEnemy].nTexType = nTexType;
			g_Enemy[nCntEnemy].bUse = true;

			g_nNumEnemy++;		//�G�̑��������Z����

			//�e�̏����ݒ�
			g_Enemy[nCntEnemy].nIdxEnemyShadow = SetShadow(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].rot, 10.0f, 10.0f);
			break;
		}
	}
}

//=============================================================================
// �G�̎擾
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_Enemy[0];
}

//=============================================================================
// �G�l�~�[����������
//=============================================================================
void DeleteEnemy(int nCntEnemy)
{
	g_nNumEnemy--;
	DeleteShadow(g_Enemy[nCntEnemy].nIdxEnemyShadow);
	g_Enemy[nCntEnemy].bUse = false;
}