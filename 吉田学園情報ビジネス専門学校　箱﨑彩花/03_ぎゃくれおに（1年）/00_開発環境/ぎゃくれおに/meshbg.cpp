//=============================================================================
//
// �|���S������ [meshbg.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "meshbg.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHWALL_TEXTURE_NAME		"data\\TEXTURE\\Bg002.jpg"							//�ǂݍ��ރe�N�X�`���t�@�C��
#define BULOCK_Z					(1.0f)												//�u���b�N�̉��s
#define BULOCK_X					(1.0f)												//�u���b�N�̉��s
#define BULOCK_Y					(1.0f)												//�u���b�N�̏c
#define VERTICAL					(1)													//�c
#define CORSS						(15)												//��
#define VERTEX						((VERTICAL + 1) * (CORSS + 1))						//�ӂƕӂ̌v�Z
#define ANGLE						(1.0f / (CORSS/2))									//�w�肵��������PI���o����
#define IDX							(((2 + CORSS) * 2 * VERTICAL) + (VERTICAL - 1) * 4)	//�C���f�b�N�X�̌v�Z
#define POLYGON						((VERTICAL * CORSS) * 2 + (VERTICAL - 1) * 4)		//�|���S���̌v�Z		

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshBg(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshBg = NULL;	//���_�o�b�t�@
LPDIRECT3DTEXTURE9		g_pTextureMeshBg = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshBg = NULL;	//�C���f�b�N�X�o�b�t�@�̃|�C���^
MeshBg g_MeshBg;								//���b�V���E�H�[���̏��

//=============================================================================
// ����������
//=============================================================================
void InitMeshBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	//�����l
	g_MeshBg.posMeshBg = D3DXVECTOR3(2100.0f, 0.0f, -2000.0f);	//�ʒu
	g_MeshBg.rotMeshBg = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	g_MeshBg.nNumVertexMeshBg = VERTEX;							//���_��
	g_MeshBg.nNumIdxMeshBg = IDX;								//�C���f�b�N�X��
	g_MeshBg.nNumPolygonMeshBg = POLYGON;						//�|���S����

	//���_���
	MakeVertexMeshBg(pDevice);
}
//=============================================================================
// �I������
//=============================================================================
void UninitMeshBg(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureMeshBg != NULL)
	{
		g_pTextureMeshBg->Release();
		g_pTextureMeshBg = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshBg != NULL)
	{
		g_pVtxBuffMeshBg->Release();
		g_pVtxBuffMeshBg = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshBg != NULL)
	{
		g_pIdxBuffMeshBg-> Release();
		g_pIdxBuffMeshBg = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshBg(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshBg.mtxWorldMeshBg);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshBg.rotMeshBg.y, g_MeshBg.rotMeshBg.x, g_MeshBg.rotMeshBg.z);

	D3DXMatrixMultiply(&g_MeshBg.mtxWorldMeshBg, &g_MeshBg.mtxWorldMeshBg, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshBg.posMeshBg.x, g_MeshBg.posMeshBg.y, g_MeshBg.posMeshBg.z);

	D3DXMatrixMultiply(&g_MeshBg.mtxWorldMeshBg, &g_MeshBg.mtxWorldMeshBg, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshBg.mtxWorldMeshBg);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshBg, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshBg);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshBg);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0 , POLYGON,0, g_MeshBg.nNumPolygonMeshBg);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshBg(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntCorss;
	int nCntVertical;
	int nCntIdx;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		MESHWALL_TEXTURE_NAME,
		&g_pTextureMeshBg
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_MeshBg.nNumVertexMeshBg,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshBg,
		NULL
	);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * g_MeshBg.nNumIdxMeshBg,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshBg,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD * pIdx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMeshBg->Lock(0, 0, (void**)&pVtx, 0);

	//�����_�ݒ�
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
		 //�~��
			//pVtx[���_�ԍ�].x,,z = sinf((3.14�̉~���@�����-������ƁA�J�����O�������t�ɂȂ�@* (�J�E���g�̉񐔁@* �w�肵�������v�Z���Ċp�x����)))* ���a;
			pVtx[0].pos.x = sinf((-D3DX_PI * (nCntCorss * ANGLE)))* 5000.0f;
			//pVtx[���_�ԍ�].y = �c�̃J�E���g�񐔁@* �c�̕�
			pVtx[0].pos.y = nCntVertical * 5000.0f;
			pVtx[0].pos.z = cosf((-D3DX_PI * (nCntCorss * ANGLE)))* 5000.0f;

			//�@��
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(nCntCorss * 1.0f, nCntVertical * 1.0f);

			//���炵
			pVtx += 1;
		}
	}

	//���C���f�b�N�X��
#if 0
	//���_�o�b�t�@�̃A�����b�N����
	g_pVtxBuffMeshBg->Unlock();

	//for (nCntVertical = 0; nCntVertical < VERTICAL; nCntVertical++)
	//{//�c��
	//	for (nCntCorss = 0; nCntCorss < CORSS + 1; nCntCorss++)
	//	{//����
	//	    //pVtx[���ẴJ�E���g���@* (���̃u���b�N�� * �|���S����) �܂�Ԃ����y+ �J�E���g�� * �|���S�����z+ ���̃J�E���g * �|���S���� + ���_�ԍ�]
	//		//                                                   .pos = D3DXVECTOR3(���J�E���g * �u���b�N�̕�,Y���͂O,�c�̃J�E���g * �u���b�N�̍��� - �u���b�N�̍���)
	//		//                                                  .pos = D3DXVECTOR3(���J�E���g * �u���b�N�̕�,Y���͂O,�c�̃J�E���g * �u���b�N�̍���)
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

	//for (nCntNorCol = 0; nCntNorCol < g_g_MeshBg.nNumVertexMeshBg; nCntNorCol++)
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
	g_pIdxBuffMeshBg->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�̎�
	for (nCntVertical = 0, nCntIdx = 0; nCntVertical < VERTICAL; nCntVertical++)
	{//�c���J�E���g
		for (nCntCorss = 0; nCntCorss < CORSS + 1; nCntCorss++, nCntIdx++)
		{//�����J�E���g
		 //pIdx[�ԍ�] = (�w�肵���� + �P�i���̂P�͂O����X�^�[�g�������ɂP����Ȃ�����j + �C���f�b�N�X�̉�)
			pIdx[0] = (CORSS + 1) + nCntIdx;
			pIdx[1] = 0 + nCntIdx;

			//�Q���_���炵
			pIdx += 2;

			if (nCntVertical < VERTICAL - 1 && nCntCorss == CORSS)
			{//�w�肵���c-1�ɍs�����Ƃ��Ɖ����w�肵�����܂ōs�����Ƃ�
				pIdx[0] = 0 + nCntIdx;
				pIdx[1] = (CORSS + 1) + nCntIdx + 1;

				//�Q���_�����炷
				pIdx += 2;
			}
		}
	}

	//�C���f�b�N�X�̃o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshBg->Unlock();

}

