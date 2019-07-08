//=============================================================================
//
// �|���S������ [meshfield.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "meshfield.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME		"data\\TEXTURE\\konku.png"							//�ǂݍ��ރe�N�X�`���t�@�C��
#define BULOCK_Z					(2500.0f)											//�u���b�N�̉��s
#define BULOCK_X					(2500.0f)											//�u���b�N�̉��s
#define VERTICAL					(5)													//�c
#define CORSS						(5)													//��
#define VERTEX						((VERTICAL + 1) * (CORSS + 1))						//�w�肵���c�Ɖ�+�P�̒l
#define IDX							((VERTICAL * CORSS) * 2 + (VERTICAL - 1) * 4 + 2)	//�C���f�b�N�X�̎�
#define POLYGON						((VERTICAL * CORSS) * 2 + (VERTICAL - 1) * 4)		//�|���S�����̎�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL; //���_�o�b�t�@
LPDIRECT3DTEXTURE9		g_pTextureMeshField = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//�C���f�b�N�X�o�b�t�@�̃|�C���^
MeshField g_MeshField;

//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�ϐ��錾
	int nCntCorss;						//���̃J�E���g
	int nCntVertical;					//�c�̃J�E���g
	int nCntIdx;						//�C���f�b�N�X�̒��_���

	g_MeshField.nNumVertexMeshField = VERTEX;		//���_��
	g_MeshField.nNumIdxMeshField = IDX;				//�C���f�b�N�X��
	g_MeshField.nNumPolygonMeshField = POLYGON;		//�|���S����


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		MESHFIELD_TEXTURE_NAME,
		&g_pTextureMeshField
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_MeshField.nNumVertexMeshField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL
	);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * g_MeshField.nNumIdxMeshField,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD * pIdx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//�����_���
#if 0
	////���_���
	//pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
	//pVtx[2].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	//pVtx[3].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	//pVtx[8].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	
	////���_�̃C���f�b�N�X���
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;
	//pIdx[7] = 6;
	//pIdx[8] = 6;
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;
#endif

	//���_�A�@���A�J���[�A�e�N�X�`���̒��_�ݒ�
	for (nCntVertical = 0; nCntVertical <= VERTICAL; nCntVertical++)
	{//�c��
		for (nCntCorss = 0; nCntCorss < CORSS + 1; nCntCorss++)
		{//����
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(-BULOCK_X * 2 + (BULOCK_X * nCntCorss)*1.0f, 0.0f, BULOCK_Z * 2 - (BULOCK_Z * nCntVertical)*1.0f);

			//�@��
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(nCntCorss*1.0f, nCntVertical*1.0f);

			//���炵
			pVtx += 1;
		}
	}

	//���_�o�b�t�@�̃A�����b�N����
	g_pVtxBuffMeshField->Unlock();

	//�����_���
#if 0
	//for (nCntVertical = 0; nCntVertical < VERTICAL; nCntVertical++)
	//{//�c��
	//	for (nCntCorss = 0; nCntCorss < CORSS + 1; nCntCorss++)
	//	{//����
	//	    //pVtx[���ẴJ�E���g���@* (���̃u���b�N�� * �|���S����) �܂�Ԃ����y+ �J�E���g�� * �|���S�����z+ ���̃J�E���g * �|���S���� + ���_�ԍ�]
	//		//                                                   .pos = D3DXVECTOR3(���J�E���g * �u���b�N�̕�,Y���͂O,�c�̃J�E���g * �u���b�N�̍��� - �u���b�N�̍���)
	//		//                                                   .pos = D3DXVECTOR3(���J�E���g * �u���b�N�̕�,Y���͂O,�c�̃J�E���g * �u���b�N�̍���)
	//		pVtx[nCntVertical * (CORSS * 2) + nCntVertical * 2 + nCntCorss * 2].pos = D3DXVECTOR3(nCntCorss * BULOCK_X, 0.0f,nCntVertical * BULOCK_Z - BULOCK_Z);	//0
	//		pVtx[nCntVertical * (CORSS * 2) + nCntVertical * 2 + nCntCorss * 2 + 1].pos = D3DXVECTOR3(nCntCorss * BULOCK_X, 0, nCntVertical * BULOCK_Z);			//1


	//		//�Ō�̒��_�ɍs������
	//		//���̃J�E���g���u���b�N��-1�ɍs�����ꍇ�Əc���󔒂̏ꏊ��-1���ďc�̃u���b�N��������Ȃ��Ȃ��ꍇ
	//		if (nCntCorss == CORSS - 1 && nCntVertical - 1 != VERTICAL)
	//		{
	//			//pVtx[���ẴJ�E���g���@* (���̃u���b�N�� * �|���S����) �܂�Ԃ����y+ �J�E���g�� * �|���S�����z+ ���̃J�E���g * �|���S���� + ���_�ԍ�]
	//			//                                                       .pos = D3DXVECTOR3(���J�E���g * �u���b�N�̕�,Y���͂O,�c�̃J�E���g * �u���b�N�̍��� - �u���b�N�̍���)
	//			//                                                       .pos = D3DXVECTOR3(X���͓����Ȃ�����O,Y���͂O,�c�̃J�E���g * �u���b�N�̍��� + �u���b�N�̍���)
	//			pVtx[nCntVertical * (CORSS * 2) + nCntVertical * 2 + nCntCorss * 2 + 2].pos = D3DXVECTOR3(nCntCorss * BULOCK_X, 0, nCntCorss * BULOCK_Z);	//2
	//			pVtx[nCntVertical * (CORSS * 2) + nCntVertical * 2 + nCntCorss * 2 + 3].pos = D3DXVECTOR3(0, 0, nCntVertical * BULOCK_Z + BULOCK_Z);				//3
	//		}	
	//	}
	//}

	//for (nCntNorCol = 0; nCntNorCol < g_nNumVertexMeshField; nCntNorCol++)
	//{//�@���x�N�g���ƒ��_�J���[��for��
	//	//�@���x�N�g��
	//	pVtx[nCntNorCol].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//	//���_�J���[
	//	pVtx[nCntNorCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//}
	////�e�N�X�`���ݒ�
	////                         X     Z
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);
	//pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);
	//pVtx[4].tex = D3DXVECTOR2(1.0f, 0.5f);
	//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[7].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[9].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[10].tex = D3DXVECTOR2(0.5f, 1.0f);
	//pVtx[11].tex = D3DXVECTOR2(0.5f, 0.5f);
	//pVtx[12].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[13].tex = D3DXVECTOR2(1.0f, 0.5f);
#endif

	//�C���f�b�N�X�o�b�t�@�̃��b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̎�
	for (nCntVertical = 0, nCntIdx = 0; nCntVertical < VERTICAL; nCntVertical++)
	{//�c���J�E���g
		for (nCntCorss = 0; nCntCorss < CORSS + 1; nCntCorss++, nCntIdx++)
		{//�����J�E���g
			//pIdx[�ԍ�] = (�w�肵���� + �P�i���̂P�͂O����X�^�[�g�������ɂP����Ȃ�����j + �C���f�b�N�X�̉�)
			pIdx[0] = (CORSS + 1) + nCntIdx;
			//
			pIdx[1] = 0 + nCntIdx;

			//�Q���_���炵
			pIdx += 2;

			if (nCntVertical < VERTICAL - 1 && nCntCorss == CORSS)
			{
				pIdx[0] = 0 + nCntIdx;
				pIdx[1] = (CORSS + 1) + nCntIdx + 1;

				//�Q���_�����炷
				pIdx += 2;
			}
		}
	}

	//�C���f�b�N�X�̃o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshField->Unlock();

	//�����l
	g_MeshField.posMeshField = D3DXVECTOR3(-300.0f, 0.0f, 300.0f);
	g_MeshField.rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField-> Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshField.mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshField.rotMeshField.y, g_MeshField.rotMeshField.x, g_MeshField.rotMeshField.z);

	D3DXMatrixMultiply(&g_MeshField.mtxWorldMeshField, &g_MeshField.mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshField.posMeshField.x, g_MeshField.posMeshField.y, g_MeshField.posMeshField.z);

	D3DXMatrixMultiply(&g_MeshField.mtxWorldMeshField, &g_MeshField.mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshField.mtxWorldMeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0 , g_MeshField.nNumVertexMeshField,0, g_MeshField.nNumPolygonMeshField);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�


	// ���_���̐ݒ�

}

