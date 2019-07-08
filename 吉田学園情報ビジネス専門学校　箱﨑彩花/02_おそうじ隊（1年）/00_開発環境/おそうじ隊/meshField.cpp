//=============================================================================
//
// ���b�V���t�B�[���h���� [meshField.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "meshField.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEX "data/TEXTURE/jyutan1.jpg"		//�ǂݍ��ރe�N�X�`��
#define MAX_MESHFIELD	(1)										//�t�B�[���h�̍ő吔[�g��������]
#define WIDTH					(10)
#define HEIGHT					(10)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField[MAX_MESHFIELD] = {};	//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;										//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField[MAX_MESHFIELD] = {};		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MESHFIELD g_aMeshField[MAX_MESHFIELD];

//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		g_aMeshField[nCntMeshField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
		g_aMeshField[nCntMeshField].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
		g_aMeshField[nCntMeshField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
		g_aMeshField[nCntMeshField].nWidth = 0;														//�������H
		g_aMeshField[nCntMeshField].nHeight = 0;														//���������H
		g_aMeshField[nCntMeshField].bUse = false;
	}

	//���b�V���t�B�[���h�̐ݒu
	SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WIDTH, HEIGHT);

	// ���_���̍쐬
	MakeVertexMeshField(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	// ���_�o�b�t�@�̊J��
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_pVtxBuffMeshField[nCntMeshField] != NULL)
		{
			g_pVtxBuffMeshField[nCntMeshField]->Release();
			g_pVtxBuffMeshField[nCntMeshField] = NULL;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_pIdxBuffMeshField[nCntMeshField] != NULL)
		{
			g_pIdxBuffMeshField[nCntMeshField]->Release();
			g_pIdxBuffMeshField[nCntMeshField] = NULL;
		}
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;							//�v�Z�p�}�g���b�N�X

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMeshField[nCntMeshField].mtxWorldMeshField);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshField[nCntMeshField].rot.y, g_aMeshField[nCntMeshField].rot.x, g_aMeshField[nCntMeshField].rot.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorldMeshField, &g_aMeshField[nCntMeshField].mtxWorldMeshField, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aMeshField[nCntMeshField].pos.x, g_aMeshField[nCntMeshField].pos.y, g_aMeshField[nCntMeshField].pos.z);
			D3DXMatrixMultiply(&g_aMeshField[nCntMeshField].mtxWorldMeshField, &g_aMeshField[nCntMeshField].mtxWorldMeshField, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshField[nCntMeshField].mtxWorldMeshField);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshField[nCntMeshField], 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshField[nCntMeshField]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshField);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aMeshField[nCntMeshField].nNumVertexMeshField, 0, g_aMeshField[nCntMeshField].nNumPolygonMeshField);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//���_���̃|�C���^
	WORD * pIdx;					//�C���f�b�N�X�ւ̃|�C���^
	int nCntY;						//�c
	int nCntX;						//��

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX, &g_pTextureMeshField);

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshField[nCntMeshField].nNumVertexMeshField * MAX_MESHFIELD,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMeshField[nCntMeshField],
			NULL);

		//�C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshField[nCntMeshField].nNumIndexMeshField * MAX_MESHFIELD ,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIdxBuffMeshField[nCntMeshField],
			NULL);

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffMeshField[nCntMeshField]->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntY = 0; nCntY <= g_aMeshField[nCntMeshField].nHeight; nCntY++)
		{	//�c
			for (nCntX = 0; nCntX <= g_aMeshField[nCntMeshField].nWidth; nCntX++)
			{	//��
				//���_���̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(-100.0f + (100.0f * nCntX), 0.0f, 100.0f - (100.0f * nCntY));

				//�@���x�N�g���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntY));

				pVtx += 1;
			}
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffMeshField[nCntMeshField]->Unlock();

		int nCntIdx = 0;						//�C���f�b�N�X�̃J�E���^�[

		//�C���f�b�N�X�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pIdxBuffMeshField[nCntMeshField]->Lock(0, 0, (void**)&pIdx, 0);

		for (nCntY = 0; nCntY < g_aMeshField[nCntMeshField].nHeight; nCntY++)
		{
			for (nCntX = 0; nCntX <= g_aMeshField[nCntMeshField].nWidth; nCntX++, nCntIdx++)
			{
				pIdx[0] = (g_aMeshField[nCntMeshField].nWidth + 1) + nCntIdx;
				pIdx[1] = nCntIdx;
				pIdx += 2;																	//�C���f�b�N�X��i�߂�

				if (nCntX == g_aMeshField[nCntMeshField].nWidth && nCntY < g_aMeshField[nCntMeshField].nHeight - 1)
				{
					pIdx[0] = nCntIdx;
					pIdx[1] = (g_aMeshField[nCntMeshField].nWidth + 1) + nCntIdx + 1;	//��̂�Ɠ���ւ�
					pIdx += 2;
				}
			}
		}

		//���_�o�b�t�@���A�����b�N����
		g_pIdxBuffMeshField[nCntMeshField]->Unlock();
	}
}

//=============================================================================
// ���b�V���t�B�[���h�̎擾
//=============================================================================
MESHFIELD * GetMeshField(void)
{
	return &g_aMeshField[0];
}

//=============================================================================
// ���b�V���t�B�[���h�̐ݒ�
//=============================================================================
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight)
{
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		if (g_aMeshField[nCntMeshField].bUse == false)
		{
			g_aMeshField[nCntMeshField].pos = pos;
			g_aMeshField[nCntMeshField].rot = rot;
			g_aMeshField[nCntMeshField].nWidth = nWidth;
			g_aMeshField[nCntMeshField].nHeight = nHeight;
			g_aMeshField[nCntMeshField].bUse = true;

			//�����v�Z
			g_aMeshField[nCntMeshField].nNumVertexMeshField = (g_aMeshField[nCntMeshField].nHeight + 1) * (g_aMeshField[nCntMeshField].nWidth + 1);
			g_aMeshField[nCntMeshField].nNumIndexMeshField = (g_aMeshField[nCntMeshField].nWidth * g_aMeshField[nCntMeshField].nHeight) * 2 + (4 * (g_aMeshField[nCntMeshField].nHeight - 1)) + 2;
			g_aMeshField[nCntMeshField].nNumPolygonMeshField = (g_aMeshField[nCntMeshField].nWidth * g_aMeshField[nCntMeshField].nHeight) * 2 + (4 * (g_aMeshField[nCntMeshField].nHeight - 1));

			break;
		}
	}
}