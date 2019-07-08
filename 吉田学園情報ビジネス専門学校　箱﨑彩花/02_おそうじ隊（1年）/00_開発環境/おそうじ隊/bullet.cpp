//=============================================================================
//
// �e���� [bullet.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "bullet.h"
#include "shadow.h"
#include "explosion.h"
#include "meshField.h"
#include "effect.h"
#include "player.h"
#include "enemy.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_TEX "data/TEXTURE/bullet002.png"		//�e�N�X�`���̓ǂݍ���
#define MAX_BULLET			(300)										//�e�̍ő吔
#define BULLET_SIZE				(10.0f)										//�e�̑傫��
#define POLYGON_RANGE		(20.0f)										//�|���S���̑傫��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;				//�e�N�X�`���ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].vecA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].vecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}

	// ���_���̍쐬
	MakeVertexBullet(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	//�e�N�X�`���̊J��
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
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	//���b�V���t�B�[���h�̎擾
	MESHFIELD * pMeshField = GetMeshField();
	Player * pPlayer = GetPlayer();
	D3DXVECTOR3 aPos[4];										//�O�ρi�t�B�[���h��pos�j
	float fAnswer;														//�x�N�g���̌v�Z����

	//�t�B�[���h�̈ʒu
	aPos[0] = D3DXVECTOR3(-105.0f, 0.0f, 105.0f);
	aPos[1] = D3DXVECTOR3(895.0f, 0.0f, 105.0f);
	aPos[2] = D3DXVECTOR3(895.0f, 0.0f, -895.0f);
	aPos[3] = D3DXVECTOR3(-105.0f, 0.0f, -895.0f);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;

			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{	//�G�̒e
				if (pPlayer->state == PLAYERSTATE_NORMAL)
				{
					if (g_aBullet[nCntBullet].pos.x + POLYGON_RANGE > pPlayer->pos.x
						&& g_aBullet[nCntBullet].pos.x - POLYGON_RANGE < pPlayer->pos.x
						&& g_aBullet[nCntBullet].pos.z + POLYGON_RANGE > pPlayer->pos.z
						&& g_aBullet[nCntBullet].pos.z - POLYGON_RANGE < pPlayer->pos.z)
					{	//�����蔻��
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE_HIT000);
						DeleteShadow(g_aBullet[nCntBullet].nIdxBulletShadow);
						g_aBullet[nCntBullet].bUse = false;																		//�g�p���Ă��Ȃ���Ԃɂ���
					}
				}
			}

			for (int nCnt = 0; nCnt < 4; nCnt++)
			{	//�E�ȊO�̔���
				g_aBullet[nCntBullet].vecA = aPos[nCnt] - aPos[nCnt + 1];
				g_aBullet[nCntBullet].vecC = g_aBullet[nCntBullet].pos - aPos[nCnt];

				//�e�̈ʒu�ݒ�
				SetPositionShadow(g_aBullet[nCntBullet].nIdxBulletShadow, g_aBullet[nCntBullet].pos);

				if (nCnt == 4 - 1)
				{	//�E�̔���
					g_aBullet[nCntBullet].vecA = aPos[nCnt] - aPos[0];
				}

				fAnswer = ((g_aBullet[nCntBullet].vecA.z * g_aBullet[nCntBullet].vecC.x) - (g_aBullet[nCntBullet].vecA.x * g_aBullet[nCntBullet].vecC.z));

				if (fAnswer >= 0)
				{
					SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.3f, 0.5f, 1.0f));		//�����̐ݒ�
					g_aBullet[nCntBullet].bUse = false;
					DeleteShadow(g_aBullet[nCntBullet].nIdxBulletShadow);
				}
			}

#if 0
			//���̔���------------------------------------------------------------------------------------------------------------------------------------------------
			g_aBullet[nCntBullet].vecA = aPos[0] - aPos[1];
			g_aBullet[nCntBullet].vecC = g_aBullet[nCntBullet].pos - aPos[0];

			fAnswer0 = ((g_aBullet[nCntBullet].vecA.z * g_aBullet[nCntBullet].vecC.x) - (g_aBullet[nCntBullet].vecA.x * g_aBullet[nCntBullet].vecC.z));

			if (fAnswer0 >= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//�����̐ݒ�
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxBulletShadow);
			}

			//���̔���-------------------------------------------------------------------------------------------------------------------------------------------------
			g_aBullet[nCntBullet].vecA = aPos[1] - aPos[2];
			g_aBullet[nCntBullet].vecC = g_aBullet[nCntBullet].pos - aPos[1];

			fAnswer1 = ((g_aBullet[nCntBullet].vecA.z * g_aBullet[nCntBullet].vecC.x) - (g_aBullet[nCntBullet].vecA.x * g_aBullet[nCntBullet].vecC.z));

			if (fAnswer1 >= 0)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//�����̐ݒ�
				g_aBullet[nCntBullet].bUse = false;
				DeleteShadow(g_aBullet[nCntBullet].nIdxBulletShadow);
			}

			//�E�̔���--------------------------------------------------------------------------------------------------------------------------------------------------
			//g_aBullet[nCntBullet].vecA = aPos[3] - aPos[0];
			//g_aBullet[nCntBullet].vecC = g_aBullet[nCntBullet].pos - aPos[3];

			//if (g_aBullet[nCntBullet].pos.x > 895.0f
			//	|| g_aBullet[nCntBullet].pos.x < -105.0f
			//	|| g_aBullet[nCntBullet].pos.z > 105.0f
			//	|| g_aBullet[nCntBullet].pos.z < -895.0f)
			//{	//�����蔻��
			//	SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.7f, 0.2f, 0.8f, 1.0f));		//�����̐ݒ�
			//	DeleteShadow(g_aBullet[nCntBullet].nIdxBulletShadow);
			//	g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
			//}
#endif
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			//�v�Z�p�}�g���b�N�X
	int nCntBullet;

	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorldBullet);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�t�s��̐ݒ�
			g_aBullet[nCntBullet].mtxWorldBullet._11 = mtxView._11;
			g_aBullet[nCntBullet].mtxWorldBullet._12 = mtxView._21;
			g_aBullet[nCntBullet].mtxWorldBullet._13 = mtxView._31;
			g_aBullet[nCntBullet].mtxWorldBullet._21 = mtxView._12;
			g_aBullet[nCntBullet].mtxWorldBullet._22 = mtxView._22;
			g_aBullet[nCntBullet].mtxWorldBullet._23 = mtxView._32;
			g_aBullet[nCntBullet].mtxWorldBullet._31 = mtxView._13;
			g_aBullet[nCntBullet].mtxWorldBullet._32 = mtxView._23;
			g_aBullet[nCntBullet].mtxWorldBullet._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorldBullet, &g_aBullet[nCntBullet].mtxWorldBullet, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorldBullet);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//���_���̃|�C���^
	int nCntBullet;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET_TEX, &g_pTextureBullet);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//�e�̐F�ݒ�
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
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].bUse = true;

			//�e�̏����ݒ�
			g_aBullet[nCntBullet].nIdxBulletShadow = SetShadow(g_aBullet[g_aBullet[nCntBullet].nIdxBulletShadow].pos, g_aBullet[g_aBullet[nCntBullet].nIdxBulletShadow].move, 10.0f, 10.0f);

			break;
		}
	}
}