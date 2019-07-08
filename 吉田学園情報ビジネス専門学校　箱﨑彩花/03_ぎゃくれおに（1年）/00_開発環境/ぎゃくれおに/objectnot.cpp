//=============================================================================
//
// ���f������ [ObjectNot.cpp]
// Author : �L�n ���u�@���@���R
//
//=============================================================================
#include "objectnot.h"		//�I�u�W�F�N�g
#include "input.h"		//�L�[�{�[�h
#include "camera.h"		//�J����
#include "shadow.h"		//�e
#include "player.h"		//�v���C���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBJECT_NAME			"data\\MODEL\\���H.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME1		"data\\MODEL\\����.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME2		"data\\MODEL\\�M��(��).x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME3		"data\\MODEL\\�X��2(��).x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME4		"data\\MODEL\\asd.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME5		"data\\MODEL\\����.x"		//�ǂݍ��ރe�N�X�`���t�@�C��

#define MAX_TEX				(40)							//�I�u�W�F�N�g�̃e�N�X�`���ő吔
#define MAX_OBJECT			(235)							//�I�u�W�F�N�g�̍ő吔
#define MAX_VARIATION		(6)								//�I�u�W�F�N�g�̎��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ObjectNot g_ObjectNot[MAX_OBJECT];

//=============================================================================
// ����������
//=============================================================================
void InitObjectNot(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectNot[0].pBuffMatObjectNot,
		NULL, &g_ObjectNot[0].nNumMatObjectNot,
		&g_ObjectNot[0].pMeshObjectNot
	);
	// X�t�@�C���̓ǂݍ���	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectNot[1].pBuffMatObjectNot,
		NULL,
		&g_ObjectNot[1].nNumMatObjectNot,
		&g_ObjectNot[1].pMeshObjectNot
	);
	// X�t�@�C���̓ǂݍ���	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectNot[2].pBuffMatObjectNot,
		NULL, &g_ObjectNot[2].nNumMatObjectNot,
		&g_ObjectNot[2].pMeshObjectNot
	);

	// X�t�@�C���̓ǂݍ���	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectNot[3].pBuffMatObjectNot,
		NULL, &g_ObjectNot[3].nNumMatObjectNot,
		&g_ObjectNot[3].pMeshObjectNot
	);
	// X�t�@�C���̓ǂݍ���	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME4,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectNot[4].pBuffMatObjectNot,
		NULL, &g_ObjectNot[4].nNumMatObjectNot,
		&g_ObjectNot[4].pMeshObjectNot
	);
	// X�t�@�C���̓ǂݍ���	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME5,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_ObjectNot[5].pBuffMatObjectNot,
		NULL, &g_ObjectNot[5].nNumMatObjectNot,
		&g_ObjectNot[5].pMeshObjectNot
	);
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 *pMatDef;

	//�e�N�X�`��������
	for (int nCount = 0; nCount < MAX_VARIATION; nCount++)
	{
		pMat = (D3DXMATERIAL*)g_ObjectNot[nCount].pBuffMatObjectNot->GetBufferPointer();
		pMatDef = new D3DMATERIAL9[g_ObjectNot[nCount].nNumMatObjectNot];
		g_ObjectNot[nCount].pMeshTextures = new LPDIRECT3DTEXTURE9[g_ObjectNot[nCount].nNumMatObjectNot];

		for (DWORD tex = 0; tex < g_ObjectNot[nCount].nNumMatObjectNot; tex++)
		{
			pMatDef[tex] = pMat[tex].MatD3D;
			pMatDef[tex].Ambient = pMatDef[tex].Diffuse;
			g_ObjectNot[nCount].pMeshTextures[tex] = NULL;
			if (pMat[tex].pTextureFilename != NULL &&
				lstrlen(pMat[tex].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(pDevice,
					pMat[tex].pTextureFilename,
					&g_ObjectNot[nCount].pMeshTextures[tex])))
				{
					//MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
				}
			}
		}
	}

	for (int nCntObjectNot = 0; nCntObjectNot < MAX_OBJECT; nCntObjectNot++)
	{
		g_ObjectNot[nCntObjectNot].VtxMinObjectNot = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_ObjectNot[nCntObjectNot].VtxMaxObjectNot = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_ObjectNot[nCntObjectNot].pos = D3DXVECTOR3(0, 0, 0);
		g_ObjectNot[nCntObjectNot].rot = D3DXVECTOR3(0, 0, 0);
		g_ObjectNot[nCntObjectNot].bUse = false;
	}

	int nNumVtx;			//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g7�̃T�C�Y
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

	for (int nCount = 0; nCount < MAX_VARIATION; nCount++)
	{
		//���_�����擾
		nNumVtx = g_ObjectNot[nCount].pMeshObjectNot->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_ObjectNot[nCount].pMeshObjectNot->GetFVF());

		//���_�o�b�t�@�����b�N
		g_ObjectNot[nCount].pMeshObjectNot->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W�̑��

													   //�͈͎w��
													   //�ő�l
			if (vtx.x < g_ObjectNot[nCount].VtxMinObjectNot.x)
			{
				g_ObjectNot[nCount].VtxMinObjectNot.x = vtx.x;
			}
			if (vtx.z < g_ObjectNot[nCount].VtxMinObjectNot.z)
			{
				g_ObjectNot[nCount].VtxMinObjectNot.z = vtx.z;
			}
			if (vtx.y < g_ObjectNot[nCount].VtxMinObjectNot.y)
			{
				g_ObjectNot[nCount].VtxMinObjectNot.y = vtx.y;
			}
			//�ŏ��l
			if (vtx.x > g_ObjectNot[nCount].VtxMaxObjectNot.x)
			{
				g_ObjectNot[nCount].VtxMaxObjectNot.x = vtx.x;
			}
			if (vtx.z > g_ObjectNot[nCount].VtxMaxObjectNot.z)
			{
				g_ObjectNot[nCount].VtxMaxObjectNot.z = vtx.z;
			}
			if (vtx.y > g_ObjectNot[nCount].VtxMaxObjectNot.y)
			{
				g_ObjectNot[nCount].VtxMaxObjectNot.y = vtx.y;
			}
			pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_ObjectNot[nCount].pMeshObjectNot->UnlockVertexBuffer();
	}

	//�I�u�W�F�N�g�̑��
	for (int nPotaCountObjectNot = 6; nPotaCountObjectNot < MAX_OBJECT; nPotaCountObjectNot++)
	{
		if (nPotaCountObjectNot < 17)
		{
			g_ObjectNot[nPotaCountObjectNot] = g_ObjectNot[0];
		}
		else if (nPotaCountObjectNot < 28)
		{
			g_ObjectNot[nPotaCountObjectNot] = g_ObjectNot[1];
		}
		else if (nPotaCountObjectNot < 31)
		{
			g_ObjectNot[nPotaCountObjectNot] = g_ObjectNot[2];
		}
		else if (nPotaCountObjectNot < 77)
		{
			g_ObjectNot[nPotaCountObjectNot] = g_ObjectNot[3];
		}
		else if (nPotaCountObjectNot < 188)
		{
			g_ObjectNot[nPotaCountObjectNot] = g_ObjectNot[4];
		}
		else if (nPotaCountObjectNot < 235)
		{
			g_ObjectNot[nPotaCountObjectNot] = g_ObjectNot[5];
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitObjectNot(void)
{
	for (int nCntObjectNot = 0; nCntObjectNot < MAX_VARIATION; nCntObjectNot++)
	{
		// ���b�V���̊J��
		if (g_ObjectNot[nCntObjectNot].pMeshObjectNot != NULL)
		{
			g_ObjectNot[nCntObjectNot].pMeshObjectNot->Release();
			g_ObjectNot[nCntObjectNot].pMeshObjectNot = NULL;
		}
		// �}�e���A���̊J��
		if (g_ObjectNot[nCntObjectNot].pBuffMatObjectNot != NULL)
		{
			g_ObjectNot[nCntObjectNot].pBuffMatObjectNot->Release();
			g_ObjectNot[nCntObjectNot].pBuffMatObjectNot = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObjectNot(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObjectNot(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCount2 = 0; nCount2 < MAX_OBJECT; nCount2++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_ObjectNot[nCount2].mtxWorldObjectNot);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ObjectNot[nCount2].rot.y, g_ObjectNot[nCount2].rot.x, g_ObjectNot[nCount2].rot.z);

		D3DXMatrixMultiply(&g_ObjectNot[nCount2].mtxWorldObjectNot, &g_ObjectNot[nCount2].mtxWorldObjectNot, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_ObjectNot[nCount2].pos.x, g_ObjectNot[nCount2].pos.y, g_ObjectNot[nCount2].pos.z);

		D3DXMatrixMultiply(&g_ObjectNot[nCount2].mtxWorldObjectNot, &g_ObjectNot[nCount2].mtxWorldObjectNot, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_ObjectNot[nCount2].mtxWorldObjectNot);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_ObjectNot[nCount2].pBuffMatObjectNot->GetBufferPointer();

		for (int nCntMat = 0; nCntMat<(int)g_ObjectNot[nCount2].nNumMatObjectNot; nCntMat++)
		{
			if (g_ObjectNot[nCount2].bUse == true)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_ObjectNot[nCount2].pMeshTextures[nCntMat]);
				// ���f��(�p�[�c)�̕`��
				g_ObjectNot[nCount2].pMeshObjectNot->DrawSubset(nCntMat);
			}
		}
		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// �Z�b�g���f��
//=============================================================================
void SetObjectNot(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntObjectNot;

	for (nCntObjectNot = 0; nCntObjectNot < MAX_OBJECT; nCntObjectNot++)
	{
		if (g_ObjectNot[nCntObjectNot].bUse == false)
		{
			g_ObjectNot[nCntObjectNot].pos = pos;
			g_ObjectNot[nCntObjectNot].rot = rot;
			g_ObjectNot[nCntObjectNot].bUse = true;
			break;
		}
	}
}
//=============================================================================
// ���f���̓����蔻��
//=============================================================================

//=========================================================================================================================
// �I�u�W�F�N�g�̎擾����
//=========================================================================================================================
ObjectNot *GetObjectNot(void)
{
	return &g_ObjectNot[0];
}