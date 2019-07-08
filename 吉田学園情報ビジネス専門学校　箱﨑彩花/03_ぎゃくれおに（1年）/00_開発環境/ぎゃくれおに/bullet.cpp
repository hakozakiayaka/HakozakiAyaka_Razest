//=============================================================================
//
// �|���S������ [bullet.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "bullet.h"		//�e
#include "shadow.h"		//�e
#include "explosion.h"	//����
#include "effect.h"		//�G�t�F�N�g
#include "object.h"		//�I�u�W�F�N�g
#include "billboord.h"	//�r���{�[�h
#include "input.h"		//�L�[�{�[�h

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_TEXTURE_NAME		"data\\TEXTURE\\bullet000.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_BULLET				(20)								//�e�̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	//�e�N�X�`���ւ̃|�C���^
Bullet					g_Bullet[MAX_BULLET];		//�e�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{//�S�J�E���g����
		g_Bullet[nCount].rotBullet = D3DXVECTOR3(0, 0, 0);	//����
		g_Bullet[nCount].posBullet = D3DXVECTOR3(0, 0, 0);	//�ʒu
		g_Bullet[nCount].moveBullet = D3DXVECTOR3(0, 0, 0);	//����
		g_Bullet[nCount].bUse = false;						//�g�p���Ă��邩�ǂ���
	}

	//���_���
	MakeVertexBullet(pDevice);
}
//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureBullet != NULL)
		{
			g_pTextureBullet->Release();
			g_pTextureBullet = NULL;
		}
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�|�C���^

	int nCntBullet;									//�e�J�E���g

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//�e���J�E���g
		if (g_Bullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���

			//�A�C�e���̂����蔻��
			CollisionBillBoord(&g_Bullet[nCntBullet].posBullet,&g_Bullet[nCntBullet].moveBullet);

			//�G�t�F�N�g
			SetBulletEffect(g_Bullet[nCntBullet].posBullet,D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),EFFECTTYPE_BULLET,3.0f, 0,0);

			//�ړ��l���
			g_Bullet[nCntBullet].posBullet += g_Bullet[nCntBullet].moveBullet;

			//�e�����Ă���
			SetPositionShadow(g_Bullet[nCntBullet].nIdxShadow, g_Bullet[nCntBullet].posBullet, g_Bullet[nCntBullet].rotBullet);

			//�ǂƂ̂����蔻��
			if (g_Bullet[nCntBullet].posBullet.z >= 1500 || g_Bullet[nCntBullet].posBullet.z <= -1500 || g_Bullet[nCntBullet].posBullet.x >= 1500 || g_Bullet[nCntBullet].posBullet.x <= -1500 || g_Bullet[nCntBullet].posBullet.y <= 0 || g_Bullet[nCntBullet].posBullet.y >= 450)
			{
				//�e��false
				g_Bullet[nCntBullet].bUse = false;

				//�g���Ă���e��false
				DeleteShadow(g_Bullet[nCntBullet].nIdxShadow);

				//����
				SetExplosion(g_Bullet[nCntBullet].posBullet,g_Bullet[nCntBullet].rotBullet);

				//�G�t�F�N�g
				//SetParticleEffect(g_Bullet[nCntBullet].posBullet, EFFECTTYPE_EXPLOSION, 50, 6.0f, 10,0);

				////�X�R�A���Z
				//AddScore(1000,SCORE_EXSPLOSION);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans,mtxView;		//�v�Z�p�}�g���b�N�X


	//�A���t�@�e�X�g����
	//�f�t�H���g�̏ꍇFALSE�ɂȂ��Ă��邩��TRUE�ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�����̎��͎Q�Ƃ��Ӗ����A�Q�Ƃ����l����l�ɒu��������
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	//�����̎��͏������Ӗ����A��r����Ƃ�����
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�|���S���̕`��
	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{//�e���J�E���g
		if (g_Bullet[nCount].bUse == true)
		{//�e������ꍇ

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Bullet[nCount].mtxWorldBullet);

			//�e
			pDevice->GetTransform
			(
				D3DTS_VIEW,
				&mtxView
			);

			//�t�s���ݒ�
			g_Bullet[nCount].mtxWorldBullet._11 = mtxView._11;
			g_Bullet[nCount].mtxWorldBullet._12 = mtxView._21;
			g_Bullet[nCount].mtxWorldBullet._13 = mtxView._31;
			g_Bullet[nCount].mtxWorldBullet._21 = mtxView._12;
			g_Bullet[nCount].mtxWorldBullet._22 = mtxView._22;
			g_Bullet[nCount].mtxWorldBullet._23 = mtxView._32;
			g_Bullet[nCount].mtxWorldBullet._31 = mtxView._13;
			g_Bullet[nCount].mtxWorldBullet._32 = mtxView._23;
			g_Bullet[nCount].mtxWorldBullet._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCount].posBullet.x, g_Bullet[nCount].posBullet.y, g_Bullet[nCount].posBullet.z);

			D3DXMatrixMultiply(&g_Bullet[nCount].mtxWorldBullet, &g_Bullet[nCount].mtxWorldBullet, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCount].mtxWorldBullet);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}

	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		BULLET_TEXTURE_NAME,
		&g_pTextureBullet
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{//�S�J�E���g����
	 //���_��
		pVtx[0].pos = D3DXVECTOR3(-2.0f, 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(2.0f, 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(2.0f, 0.0f, 0.0f);
		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N����
	g_pVtxBuffBullet->Unlock();
}
//=============================================================================
// �e�̍쐬
//=============================================================================
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 move)
{
	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		if (g_Bullet[nCount].bUse == false)
		{
			g_Bullet[nCount].posBullet = pos;			//pos�l���
			g_Bullet[nCount].rotBullet = rot;			//rot�l���
			g_Bullet[nCount].moveBullet = move;			//move�l���
			g_Bullet[nCount].bUse = true;				//�g�p���Ă����Ԃɂ���

			//�e������
			g_Bullet[nCount].nIdxShadow = SetShadow(g_Bullet[nCount].posBullet, g_Bullet[nCount].rotBullet, 2, 2);
			break;
		}
	}
}
//=============================================================================
//	�J�����̎擾
//=============================================================================
Bullet *GetBullet(void)
{
	return &g_Bullet[0];
}
