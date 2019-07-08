//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "effect.h"
#include "shadow.h"
#include "fade.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EFFECT_TEX	 "data/TEXTURE/effect000.jpg"				//�e�N�X�`���̓ǂݍ���

#define MAX_EFFECT		(100)
#define MAX_TEX			(2)												//�e�N�X�`���̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;				//�e�N�X�`���ւ̃|�C���^
Effect g_Effect[MAX_EFFECT];

//=============================================================================
// ����������
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	int nCntEffect;

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Effect[nCntEffect].fRadius = 0.0f;
		g_Effect[nCntEffect].nLife = 0;
		g_Effect[nCntEffect].bUse = false;
	}

	// ���_���̍쐬
	MakeVertexEffect(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	//�e�N�X�`���̊J��
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_pTextureEffect != NULL)
		{
			g_pTextureEffect->Release();
			g_pTextureEffect = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	VERTEX_3D * pVtx;			//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{
			g_Effect[nCntEffect].nLife--;
			g_Effect[nCntEffect].fRadius--;

			//�G�t�F�N�g�̑傫�����W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x - g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].pos.y - g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x + g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].pos.y - g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x - g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].pos.y + g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x + g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].pos.y + g_Effect[nCntEffect].fRadius, 0.0f);

			if (g_Effect[nCntEffect].nLife == 0)
			{
				g_Effect[nCntEffect].bUse = false;
			}
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			//�v�Z�p�}�g���b�N�X
	int nCntEffect;

	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Effect[nCntEffect].mtxWorldEffect);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�t�s��̐ݒ�
			g_Effect[nCntEffect].mtxWorldEffect._11 = mtxView._11;
			g_Effect[nCntEffect].mtxWorldEffect._12 = mtxView._21;
			g_Effect[nCntEffect].mtxWorldEffect._13 = mtxView._31;
			g_Effect[nCntEffect].mtxWorldEffect._21 = mtxView._12;
			g_Effect[nCntEffect].mtxWorldEffect._22 = mtxView._22;
			g_Effect[nCntEffect].mtxWorldEffect._23 = mtxView._32;
			g_Effect[nCntEffect].mtxWorldEffect._31 = mtxView._13;
			g_Effect[nCntEffect].mtxWorldEffect._32 = mtxView._23;
			g_Effect[nCntEffect].mtxWorldEffect._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorldEffect, &g_Effect[nCntEffect].mtxWorldEffect, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].mtxWorldEffect);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//���_���̃|�C���^
	int nCntEffect;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEX, &g_pTextureEffect);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �r���{�[�h�̐ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	VERTEX_3D * pVtx;			//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{
			g_Effect[nCntEffect].pos = pos;
			pVtx[0].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x - fRadius, g_Effect[nCntEffect].pos.y - fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x + fRadius, g_Effect[nCntEffect].pos.y - fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x - fRadius, g_Effect[nCntEffect].pos.y + fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Effect[nCntEffect].pos.x + fRadius, g_Effect[nCntEffect].pos.y + fRadius, 0.0f);

			g_Effect[nCntEffect].col = col;
			pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
			pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

			g_Effect[nCntEffect].fRadius = fRadius;
			g_Effect[nCntEffect].nLife = nLife;
			g_Effect[nCntEffect].bUse = true;

			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}