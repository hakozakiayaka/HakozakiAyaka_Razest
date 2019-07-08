//=============================================================================
//
// �|���S������ [shadow.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SHADOW_TEXTURE_NAME		"data\\TEXTURE\\shadow000.jpg"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_SHADOW				(1000)								//�e�̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL; //���_�o�b�t�@
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL; //�e�N�X�`���ւ̃|�C���^
Shadow g_Shadow[MAX_SHADOW];					 //�e�̏��		

//=============================================================================
// ����������
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�e�̐��𐔂���J�E���g
	int nCntShadow;

	//�e�̏��̏�����
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{//�e���J�E���g
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0, 0, 0);//�ʒu
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0, 0, 0);//����
		g_Shadow[nCntShadow].ShadowDepth = 0;			//�[��
		g_Shadow[nCntShadow].ShadowWidth = 0;			//����
		g_Shadow[nCntShadow].bUse = false;				//�g�p���Ă��邩�ǂ���
	}

	//���_���
	MakeVertexShadow(pDevice);
}
//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//���Z�����̐ݒ�
	pDevice->SetRenderState
	(
		D3DRS_BLENDOP,
		D3DBLENDOP_REVSUBTRACT
	);
	pDevice->SetRenderState
	(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA
	);
	pDevice->SetRenderState
	(
		D3DRS_DESTBLEND,
		D3DBLEND_ONE
	);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{//�e������ꍇ
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);

			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);

			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);


			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);


			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);


			//�e�N�X�`����NULL�ɂ��Ĕ��f����Ȃ��悤�ɂ���
			pDevice->SetTexture(0, NULL);

		}
	}
	//���̐ݒ�ɖ߂�
	pDevice->SetRenderState
	(
		D3DRS_BLENDOP,
		D3DBLENDOP_ADD
	);
	pDevice->SetRenderState
	(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA
	);
	pDevice->SetRenderState
	(
		D3DRS_DESTBLEND,
		D3DBLEND_INVSRCALPHA
	);

}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		SHADOW_TEXTURE_NAME,
		&g_pTextureShadow
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0);
		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@�̃A�����b�N����
	g_pVtxBuffShadow->Unlock();

}
//=============================================================================
// �e�̏��̍쐬
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float ShadowWidth,float ShadowDepth)
{
	//�e�̐��𐔂���J�E���g
	int nCntShadow;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;			

	//���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{//�e���J�E���g
		if (g_Shadow[nCntShadow].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_Shadow[nCntShadow].pos = pos;					//pos�l���
			g_Shadow[nCntShadow].rot = rot;					//move�l���
			g_Shadow[nCntShadow].ShadowDepth = ShadowDepth;	//�[��
			g_Shadow[nCntShadow].ShadowWidth = ShadowWidth;	//����
			g_Shadow[nCntShadow].bUse = true;				//�g�p���Ă����Ԃɂ���

			//���_�ݒ�
			pVtx[nCntShadow * 4].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].ShadowWidth, 0.0f, g_Shadow[nCntShadow].ShadowDepth);
			pVtx[nCntShadow * 4 + 1].pos = D3DXVECTOR3(g_Shadow[nCntShadow].ShadowWidth , 0.0f, g_Shadow[nCntShadow].ShadowDepth);
			pVtx[nCntShadow * 4 + 2].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].ShadowWidth, 0.0f, -g_Shadow[nCntShadow].ShadowDepth);
			pVtx[nCntShadow * 4 + 3].pos = D3DXVECTOR3(g_Shadow[nCntShadow].ShadowWidth , 0.0f, -g_Shadow[nCntShadow].ShadowDepth);

			//�e���n�ʂɔ��Ȃ��悤�ɂO�D�P�グ��
			g_Shadow[nCntShadow].pos.y = 0.1f;

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();

	//�g�p���Ă���e�̔ԍ�(�C���f�b�N�X)��Ԃ�
	return nCntShadow;
}
//=============================================================================
// �e�̐ݒ�
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
		if (g_Shadow[nIdxShadow].bUse == true)
		{//�������g�p����Ă��Ȃ�
			g_Shadow[nIdxShadow].pos = pos;			//pos�l���
			g_Shadow[nIdxShadow].rot = rot;			//move�l���

			//�e�̈ʒu
			g_Shadow[nIdxShadow].pos.y = 0.1f;
		}
}
//=============================================================================
// �e�̍폜����
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	if (g_Shadow[nIdxShadow].bUse == true)
	{//�e���g�p����Ă���ꍇ
		//����̔ԍ��̉e������
		g_Shadow[nIdxShadow].bUse = false;
	}
}