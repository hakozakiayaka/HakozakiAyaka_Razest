//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "billboard.h"
#include "shadow.h"
#include "fade.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BILLBOARD_TEX	 "data/TEXTURE/mio.jpg"				//�e�N�X�`���̓ǂݍ���
#define BILLBOARD_TEX1 "data/TEXTURE/enemy.png"			//�e�N�X�`���̓ǂݍ���

#define MAX_BILLBOARD	(100)
#define MAX_TEX				(2)												//�e�N�X�`���̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard[MAX_TEX] = {};				//�e�N�X�`���ւ̃|�C���^
Billboard g_billboard[MAX_BILLBOARD];
int g_nNumItem;

//=============================================================================
// ����������
//=============================================================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	int nCntBillboard;

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_billboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_billboard[nCntBillboard].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_billboard[nCntBillboard].bUse = false;
	}
	g_nNumItem= 0;		//�r���{�[�h�̖�����������

	// ���_���̍쐬
	MakeVertexBillboard(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitBillboard(void)
{
	//�e�N�X�`���̊J��
	for (int nCntBillboard = 0; nCntBillboard < MAX_TEX; nCntBillboard++)
	{
		if (g_pTextureBillboard[nCntBillboard] != NULL)
		{
			g_pTextureBillboard[nCntBillboard]->Release();
			g_pTextureBillboard[nCntBillboard] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBillboard(void)
{
	FADE g_fade = GetFade();
	Player * pPlayer = GetPlayer();

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_billboard[nCntBillboard].bUse == true)
		{
			if (g_billboard[nCntBillboard].pos.x + 10> pPlayer->pos.x
				&& g_billboard[nCntBillboard].pos.x - 10 < pPlayer->pos.x
				&& g_billboard[nCntBillboard].pos.z + 10 > pPlayer->pos.z
				&& g_billboard[nCntBillboard].pos.z - 10 < pPlayer->pos.z)
			{
				AddScore(20000);
				DeleteBillboard(nCntBillboard);
			}

			//�e�̈ʒu�ݒ�
			SetPositionShadow(g_billboard[nCntBillboard].nIdxBillboardShadow, g_billboard[nCntBillboard].pos);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxView;			//�v�Z�p�}�g���b�N�X
	int nCntBillboard;

	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_billboard[nCntBillboard].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_billboard[nCntBillboard].mtxWorldBillboard);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�t�s��̐ݒ�
			g_billboard[nCntBillboard].mtxWorldBillboard._11 = mtxView._11;
			g_billboard[nCntBillboard].mtxWorldBillboard._12 = mtxView._21;
			g_billboard[nCntBillboard].mtxWorldBillboard._13 = mtxView._31;
			g_billboard[nCntBillboard].mtxWorldBillboard._21 = mtxView._12;
			g_billboard[nCntBillboard].mtxWorldBillboard._22 = mtxView._22;
			g_billboard[nCntBillboard].mtxWorldBillboard._23 = mtxView._32;
			g_billboard[nCntBillboard].mtxWorldBillboard._31 = mtxView._13;
			g_billboard[nCntBillboard].mtxWorldBillboard._32 = mtxView._23;
			g_billboard[nCntBillboard].mtxWorldBillboard._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_billboard[nCntBillboard].pos.x, g_billboard[nCntBillboard].pos.y, g_billboard[nCntBillboard].pos.z);
			D3DXMatrixMultiply(&g_billboard[nCntBillboard].mtxWorldBillboard, &g_billboard[nCntBillboard].mtxWorldBillboard, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_billboard[nCntBillboard].mtxWorldBillboard);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBillboard[g_billboard[nCntBillboard].nTexType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBillboard * 4, 2);
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//���_���̃|�C���^
	int nCntBillboard;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BILLBOARD_TEX, &g_pTextureBillboard[0]);
	D3DXCreateTextureFromFile(pDevice, BILLBOARD_TEX1, &g_pTextureBillboard[1]);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
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
	g_pVtxBuffBillboard->Unlock();
}

//=============================================================================
// �r���{�[�h�̐ݒ�
//=============================================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nTexType)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_billboard[nCntBillboard].bUse == false)
		{
			g_billboard[nCntBillboard].pos = pos;
			g_billboard[nCntBillboard].rot = rot;
			g_billboard[nCntBillboard].nTexType = nTexType;
			g_billboard[nCntBillboard].bUse = true;

			g_nNumItem++;		//�r���{�[�h�̑��������Z����

			//�e�̏����ݒ�
			g_billboard[nCntBillboard].nIdxBillboardShadow = SetShadow(g_billboard[nCntBillboard].pos, g_billboard[nCntBillboard].rot, 10.0f, 10.0f);
			break;
		}
	}
}

//=============================================================================
// �A�C�e������������
//=============================================================================
void DeleteBillboard(int nCntBillboard)
{
	g_nNumItem--;
	DeleteShadow(g_billboard[nCntBillboard].nIdxBillboardShadow);
	g_billboard[nCntBillboard].bUse = false;
	if (g_nNumItem <= 0)
	{
		SetGameState(GAMESTATE_CLEAR);
	}
}