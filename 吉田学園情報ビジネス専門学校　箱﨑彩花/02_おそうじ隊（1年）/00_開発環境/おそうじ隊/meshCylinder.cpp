//=============================================================================
//
// ���b�V���V�����_�[���� [meshCylinder.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "meshCylinder.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHCYLINDER_TEX "data/TEXTURE/mesh000.jpg"		//�ǂݍ��ރe�N�X�`��
#define VERTEX_NUMBER		(18)														//���_��
#define MAX_POLYGON			(16)														//�|���S���̐�
#define INDEX_NUMBER		(18)														//�C���f�b�N�X�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;	//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
int g_nNumVertexMeshCylinder;														//���_��
int g_nNumIndexMeshCylinder;															//�C���f�b�N�X��
int g_nNumPolygonMeshCylinder;														//�|���S����
MESHCYLINDER g_aMeshCylinder;

//=============================================================================
// ����������
//=============================================================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	g_aMeshCylinder.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aMeshCylinder.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aMeshCylinder.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_���̍쐬
	MakeVertexMeshCylinder(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshCylinder(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshCylinder(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;							//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_aMeshCylinder.mtxWorldMeshCylinder);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshCylinder.rot.y, g_aMeshCylinder.rot.x, g_aMeshCylinder.rot.z);
	D3DXMatrixMultiply(&g_aMeshCylinder.mtxWorldMeshCylinder, &g_aMeshCylinder.mtxWorldMeshCylinder, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_aMeshCylinder.pos.x, g_aMeshCylinder.pos.y, g_aMeshCylinder.pos.z);
	D3DXMatrixMultiply(&g_aMeshCylinder.mtxWorldMeshCylinder, &g_aMeshCylinder.mtxWorldMeshCylinder, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_aMeshCylinder.mtxWorldMeshCylinder);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,VERTEX_NUMBER,0, MAX_POLYGON);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshCylinder(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;								//���_���̃|�C���^
	WORD * pIdx;										//�C���f�b�N�X�ւ̃|�C���^
	int nCntV;											//����
	int nCntH;											//����
	float fAngle = (D3DX_PI * 2) / 8;		//�������̊p�x

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHCYLINDER_TEX, &g_pTextureMeshCylinder);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_NUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_NUMBER,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntV = 0; nCntV < 2; nCntV++)
	{	//��������
		for (nCntH = 0; nCntH < 9; nCntH++)
		{	//��������  
			// ���_���̐ݒ�
			pVtx[0].pos.x = sinf(D3DX_PI + (fAngle * nCntH)) * 10.0f;		//�p�x�~���a
			pVtx[0].pos.y = 25.0f + (nCntV * 25.0f);										//����
			pVtx[0].pos.z = cosf(D3DX_PI + (fAngle * nCntH)) * 10.0f;		//�p�x�~���a

			//�@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(pVtx[0].pos.x, pVtx[0].pos.y, pVtx[0].pos.z);
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);											//���K������

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (nCntH * 1.0f), 0.0f + (nCntV * 1.0f));

			pVtx += 1;
		}
	}

	// ���_���̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(-25.0f, 0.0f, 25.0);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 25.0f);
	//pVtx[2].pos = D3DXVECTOR3(25.0f, 0.0f, 25.0f);

	//pVtx[3].pos = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(25.0f, 0.0f, 0.0f);

	//pVtx[6].pos = D3DXVECTOR3(-25.0f, 0.0f, -25.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -25.0f);
	//pVtx[8].pos = D3DXVECTOR3(25.0f, 0.0f, -25.0f);

	////�e�N�X�`���̍��W�ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//pVtx[4].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[5].tex = D3DXVECTOR2(2.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(2.0f, 1.0f);

	//pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[9].tex = D3DXVECTOR2(2.0f, 0.0f);
	//pVtx[10].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[11].tex = D3DXVECTOR2(2.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshCylinder->Unlock();

	//�C���f�b�N�X�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̐ݒ�
	pIdx[0] = 9;
	pIdx[1] = 0;

	pIdx[2] = 10;
	pIdx[3] = 1;

	pIdx[4] = 11;
	pIdx[5] = 2;

	pIdx[6] = 12;
	pIdx[7] = 3;

	pIdx[8] = 13;
	pIdx[9] = 4;

	pIdx[10] = 14;
	pIdx[11] = 5;

	pIdx[12] = 15;
	pIdx[13] = 6;

	pIdx[14] = 16;
	pIdx[15] = 7;

	pIdx[16] = 17;
	pIdx[17] = 8;

	//���_�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshCylinder->Unlock();
}