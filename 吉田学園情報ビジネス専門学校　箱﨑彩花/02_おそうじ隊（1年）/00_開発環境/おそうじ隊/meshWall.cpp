//=============================================================================
//
// ���b�V���E�H�[������ [meshWall.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "meshWall.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEX		"data/TEXTURE/kabegami.jpg"		//�ǂݍ��ރe�N�X�`��
#define MESHFIELD_TEX2		"data/TEXTURE/kabegami.jpg"		//�ǂݍ��ރe�N�X�`��
#define MESHFIELD_TEX3		"data/TEXTURE/kabegami.jpg"		//�ǂݍ��ރe�N�X�`��
#define MESHFIELD_TEX4		"data/TEXTURE/kabegami.jpg"		//�ǂݍ��ރe�N�X�`��
#define MESHFIELD_TEX5		"data/TEXTURE/window.jpg"			//�ǂݍ��ރe�N�X�`��

#define MAX_WALL				(6)													//�ǂ̐�
#define MAX_TEX					(5)													//�ǂݍ��ރe�N�X�`���̖���
#define WIDTH						(10)													//�ǂ̕�������
#define HEIGHT						(6)													//�ǂ̍���������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall[MAX_WALL] = {};			//���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshWall[MAX_TEX] = {};					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall[MAX_WALL] = {};			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MESHWALL g_aMeshWall[MAX_WALL];

//=============================================================================
// ����������
//=============================================================================
void InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	int nCntMeshWall;

	for (nCntMeshWall = 0; nCntMeshWall < MAX_WALL; nCntMeshWall++)
	{
		g_aMeshWall[nCntMeshWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshWall[nCntMeshWall].nWidth = 0;
		g_aMeshWall[nCntMeshWall].nHeight = 0;
		g_aMeshWall[nCntMeshWall].bUse = false;
	}

	//�ǂ̐ݒu
	SetMeshWall(D3DXVECTOR3(0.0f, 250.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WIDTH, HEIGHT, 0);								//��
	SetMeshWall(D3DXVECTOR3(300.0f, 50.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 1, 4);													//��
	SetMeshWall(D3DXVECTOR3(500.0f, 50.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 1, 4);													//��
	SetMeshWall(D3DXVECTOR3(900.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5, 0.0f), WIDTH, HEIGHT, 1);				//�E
	SetMeshWall(D3DXVECTOR3(-100.0f, 250.0f, -800.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5, 0.0f), WIDTH, HEIGHT, 2);	//��
	SetMeshWall(D3DXVECTOR3(800.0f, 250.0f, -900.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WIDTH, HEIGHT, 3);				//��O

	// ���_���̍쐬
	MakeVertexMeshWall(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{
	//�e�N�X�`���̊J��
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_TEX; nCntMeshWall++)
	{
		if (g_pTextureMeshWall[nCntMeshWall] != NULL)
		{
			g_pTextureMeshWall[nCntMeshWall]->Release();
			g_pTextureMeshWall[nCntMeshWall] = NULL;
		}
	}


	// ���_�o�b�t�@�̊J��
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_WALL; nCntMeshWall++)
	{
		if (g_pVtxBuffMeshWall[nCntMeshWall] != NULL)
		{
			g_pVtxBuffMeshWall[nCntMeshWall]->Release();
			g_pVtxBuffMeshWall[nCntMeshWall] = NULL;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	for (int nCntMeshWall = 0; nCntMeshWall < MAX_WALL; nCntMeshWall++)
	{
		if (g_pIdxBuffMeshWall[nCntMeshWall] != NULL)
		{
			g_pIdxBuffMeshWall[nCntMeshWall]->Release();
			g_pIdxBuffMeshWall[nCntMeshWall] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;							//�v�Z�p�}�g���b�N�X
	int nCntMeshWall;

	for (nCntMeshWall = 0; nCntMeshWall < MAX_WALL; nCntMeshWall++)
	{
		if (g_aMeshWall[nCntMeshWall].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMeshWall[nCntMeshWall].mtxWorldMeshWall);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshWall[nCntMeshWall].rot.y, g_aMeshWall[nCntMeshWall].rot.x, g_aMeshWall[nCntMeshWall].rot.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorldMeshWall, &g_aMeshWall[nCntMeshWall].mtxWorldMeshWall, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aMeshWall[nCntMeshWall].pos.x, g_aMeshWall[nCntMeshWall].pos.y, g_aMeshWall[nCntMeshWall].pos.z);
			D3DXMatrixMultiply(&g_aMeshWall[nCntMeshWall].mtxWorldMeshWall, &g_aMeshWall[nCntMeshWall].mtxWorldMeshWall, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshWall[nCntMeshWall].mtxWorldMeshWall);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall[nCntMeshWall], 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall[nCntMeshWall]);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureMeshWall[g_aMeshWall[nCntMeshWall].nTexType]);

				//�|���S���̕`��
				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 4 * nCnt, g_aMeshWall[nCnt].nNumVertexMeshWall, 0, g_aMeshWall[nCnt].nNumPolygonMeshWall);
			}
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshWall(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_3D * pVtx;			//���_���̃|�C���^
	WORD * pIdx;					//�C���f�b�N�X�ւ̃|�C���^
	int nCntY;						//�c
	int nCntX;						//��

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX, &g_pTextureMeshWall[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX2, &g_pTextureMeshWall[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX3, &g_pTextureMeshWall[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX4, &g_pTextureMeshWall[3]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEX5, &g_pTextureMeshWall[4]);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aMeshWall[nCnt].nNumVertexMeshWall * MAX_WALL,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffMeshWall[nCnt],
			NULL);

		//�C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * g_aMeshWall[nCnt].nNumIndexMeshWall * MAX_WALL,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIdxBuffMeshWall[nCnt],
			NULL);

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffMeshWall[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntY = 0; nCntY <= g_aMeshWall[nCnt].nHeight; nCntY++)
		{	//�c
			for (nCntX = 0; nCntX <= g_aMeshWall[nCnt].nWidth; nCntX++)
			{	//��
				//���_���̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(-100.0f + (100.0f * nCntX), 50.0f - (50.0f * nCntY), 0.0f);		//���A����

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
		g_pVtxBuffMeshWall[nCnt]->Unlock();

		int nCntIdx = 0;						//�C���f�b�N�X�̃J�E���^�[

		//�C���f�b�N�X�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pIdxBuffMeshWall[nCnt]->Lock(0, 0, (void**)&pIdx, 0);

		for (nCntY = 0; nCntY < g_aMeshWall[nCnt].nHeight; nCntY++)
		{
			for (nCntX = 0; nCntX <= g_aMeshWall[nCnt].nWidth; nCntX++, nCntIdx++)
			{
				pIdx[0] = (g_aMeshWall[nCnt].nWidth + 1) + nCntIdx;
				pIdx[1] = nCntIdx;
				pIdx += 2;

				if (nCntX == g_aMeshWall[nCnt].nWidth && nCntY < g_aMeshWall[nCnt].nHeight - 1)
				{
					pIdx[0] = nCntIdx;
					pIdx[1] = (g_aMeshWall[nCnt].nWidth + 1) + nCntIdx + 1;
					pIdx += 2;
				}
			}
		}

		//���_�o�b�t�@���A�����b�N����
		g_pIdxBuffMeshWall[nCnt]->Unlock();
	}
}

//=============================================================================
// �ǂ̐ݒ�
//=============================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight, int nTexType)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aMeshWall[nCntWall].bUse == false)
		{
			g_aMeshWall[nCntWall].pos = pos;
			g_aMeshWall[nCntWall].rot = rot;
			g_aMeshWall[nCntWall].nTexType = nTexType;
			g_aMeshWall[nCntWall].nWidth = nWidth;
			g_aMeshWall[nCntWall].nHeight = nHeight;
			g_aMeshWall[nCntWall].bUse = true;

			//�����v�Z
			g_aMeshWall[nCntWall].nNumVertexMeshWall = (g_aMeshWall[nCntWall].nHeight + 1) * (g_aMeshWall[nCntWall].nWidth + 1);
			g_aMeshWall[nCntWall].nNumIndexMeshWall = (g_aMeshWall[nCntWall].nWidth * g_aMeshWall[nCntWall].nHeight) * 2 + (4 * (g_aMeshWall[nCntWall].nHeight - 1)) + 2;
			g_aMeshWall[nCntWall].nNumPolygonMeshWall = (g_aMeshWall[nCntWall].nWidth * g_aMeshWall[nCntWall].nHeight) * 2 + (4 * (g_aMeshWall[nCntWall].nHeight - 1));

			break;
		}
	}
}