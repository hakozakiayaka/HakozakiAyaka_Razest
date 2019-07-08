//=============================================================================
//
// ���f������ [Object.cpp]
// Author : �L�n ���u�@���@���R�@���@����
//
//=============================================================================
#include "object.h"		//�I�u�W�F�N�g
#include "input.h"		//�L�[�{�[�h
#include "camera.h"		//�J����
#include "shadow.h"		//�e
#include "player.h"		//�v���C���[

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBJECT_NAME			"data\\MODEL\\�r��200.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME1		"data\\MODEL\\�r��400.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME2		"data\\MODEL\\�r��600.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME3		"data\\MODEL\\�M��(��).x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME4		"data\\MODEL\\�X��(��).x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME5		"data\\MODEL\\�_���{�[��.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME6		"data\\MODEL\\�g���b�N.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME7		"data\\MODEL\\��(��).x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME8		"data\\MODEL\\���̋@.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME9		"data\\MODEL\\�S�~��.x"			//�ǂݍ��ރe�N�X�`���t�@�C�������.x
#define OBJECT_NAME10		"data\\MODEL\\�����.x"			//�ǂݍ��ރe�N�X�`���t�@�C�������.x
#define MAX_TEX				(40)							//�I�u�W�F�N�g�̃e�N�X�`���ő吔
#define MAX_OBJECT			(427)							//�I�u�W�F�N�g�̍ő吔
#define MAX_VARIATION		(11)							//�I�u�W�F�N�g�̎��
#define PULS				(20)							//�����蔽t�J		
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Object g_Object[MAX_OBJECT];

//=============================================================================
// ����������
//=============================================================================
void InitObject(void)
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
		&g_Object[0].pBuffMatObject,
		NULL, &g_Object[0].nNumMatObject,
		&g_Object[0].pMeshObject
	);
	// X�t�@�C���̓ǂݍ���	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[1].pBuffMatObject,
		NULL,
		&g_Object[1].nNumMatObject,
		&g_Object[1].pMeshObject
	);
	// X�t�@�C���̓ǂݍ���	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[2].pBuffMatObject,
		NULL, &g_Object[2].nNumMatObject,
		&g_Object[2].pMeshObject
	);
	// X�t�@�C���̓ǂݍ���	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[3].pBuffMatObject,
		NULL, &g_Object[3].nNumMatObject,
		&g_Object[3].pMeshObject
	);
	// X�t�@�C���̓ǂݍ���	OBJECT_NAME5
	D3DXLoadMeshFromX
	(
		OBJECT_NAME4,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[4].pBuffMatObject,
		NULL, &g_Object[4].nNumMatObject,
		&g_Object[4].pMeshObject
	);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		OBJECT_NAME5,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[5].pBuffMatObject,
		NULL, &g_Object[5].nNumMatObject,
		&g_Object[5].pMeshObject
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		OBJECT_NAME6,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[6].pBuffMatObject,
		NULL, &g_Object[6].nNumMatObject,
		&g_Object[6].pMeshObject
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		OBJECT_NAME7,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[7].pBuffMatObject,
		NULL, &g_Object[7].nNumMatObject,
		&g_Object[7].pMeshObject
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		OBJECT_NAME8,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[8].pBuffMatObject,
		NULL, &g_Object[8].nNumMatObject,
		&g_Object[8].pMeshObject
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		OBJECT_NAME9,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[9].pBuffMatObject,
		NULL, &g_Object[9].nNumMatObject,
		&g_Object[9].pMeshObject
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		OBJECT_NAME10,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[10].pBuffMatObject,
		NULL, &g_Object[10].nNumMatObject,
		&g_Object[10].pMeshObject
	);
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 *pMatDef;

	//�e�N�X�`��������
	for (int nCount = 0; nCount < MAX_VARIATION; nCount++)
	{
		pMat = (D3DXMATERIAL*)g_Object[nCount].pBuffMatObject->GetBufferPointer();
		pMatDef = new D3DMATERIAL9[g_Object[nCount].nNumMatObject];
		g_Object[nCount].pMeshTextures = new LPDIRECT3DTEXTURE9[g_Object[nCount].nNumMatObject];

		for (DWORD tex = 0; tex < g_Object[nCount].nNumMatObject; tex++)
		{
			pMatDef[tex] = pMat[tex].MatD3D;
			pMatDef[tex].Ambient = pMatDef[tex].Diffuse;
			g_Object[nCount].pMeshTextures[tex] = NULL;
			if (pMat[tex].pTextureFilename != NULL &&
				lstrlen(pMat[tex].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(pDevice,
					pMat[tex].pTextureFilename,
					&g_Object[nCount].pMeshTextures[tex])))
				{
					//MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
				}
			}
		}
	}

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		g_Object[nCntObject].VtxMinObject = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_Object[nCntObject].VtxMaxObject = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_Object[nCntObject].pos = D3DXVECTOR3(0, 0, 0);
		g_Object[nCntObject].rot = D3DXVECTOR3(0, 0, 0);
		g_Object[nCntObject].bUse = false;
	}

	int nNumVtx;			//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g7�̃T�C�Y
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

	for (int nCount = 0; nCount < MAX_VARIATION; nCount++)
	{
		//���_�����擾
		nNumVtx = g_Object[nCount].pMeshObject->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Object[nCount].pMeshObject->GetFVF());

		//���_�o�b�t�@�����b�N
		g_Object[nCount].pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W�̑��

													   //�͈͎w��
													   //�ő�l
			if (vtx.x < g_Object[nCount].VtxMinObject.x)
			{
				g_Object[nCount].VtxMinObject.x = vtx.x;
			}
			if (vtx.z < g_Object[nCount].VtxMinObject.z)
			{
				g_Object[nCount].VtxMinObject.z = vtx.z;
			}
			if (vtx.y < g_Object[nCount].VtxMinObject.y)
			{
				g_Object[nCount].VtxMinObject.y = vtx.y;
			}
			//�ŏ��l
			if (vtx.x > g_Object[nCount].VtxMaxObject.x)
			{
				g_Object[nCount].VtxMaxObject.x = vtx.x;
			}
			if (vtx.z > g_Object[nCount].VtxMaxObject.z)
			{
				g_Object[nCount].VtxMaxObject.z = vtx.z;
			}
			if (vtx.y > g_Object[nCount].VtxMaxObject.y)
			{
				g_Object[nCount].VtxMaxObject.y = vtx.y;
			}
			pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_Object[nCount].pMeshObject->UnlockVertexBuffer();
	}

	//�I�u�W�F�N�g�̑��
	for (int nPotaCountObject = 11; nPotaCountObject < MAX_OBJECT; nPotaCountObject++)
	{
		if (nPotaCountObject < 100)
		{//�I�u�W�F�N�g�r���Q�O�O
			g_Object[nPotaCountObject] = g_Object[0];
		}
		else if (nPotaCountObject < 110)
		{//�I�u�W�F�N�g�r���S�O�O
			g_Object[nPotaCountObject] = g_Object[1];
		}
		else if (nPotaCountObject < 114)
		{//�I�u�W�F�N�g�r���U�O�O
			g_Object[nPotaCountObject] = g_Object[2];
		}
		else if (nPotaCountObject < 117)
		{//�I�u�W�F�N�g�M��(��)
			g_Object[nPotaCountObject] = g_Object[3];
		}
		else if (nPotaCountObject < 163)
		{//�I�u�W�F�N�g�M��(��)
			g_Object[nPotaCountObject] = g_Object[4];
		}
		else if (nPotaCountObject < 291)
		{//�_���{�[��
			g_Object[nPotaCountObject] = g_Object[5];
		}
		else if (nPotaCountObject < 293)
		{//�I�u�W�F�N�g�M��(��)
			g_Object[nPotaCountObject] = g_Object[6];
		}
		else if (nPotaCountObject < 404)
		{//�I�u�W�F�N�g�M��(��)
			g_Object[nPotaCountObject] = g_Object[7];
		}
		else if (nPotaCountObject < 415)
		{//���̋@
			g_Object[nPotaCountObject] = g_Object[8];
		}
		else if (nPotaCountObject < 426)
		{//���̋@
			g_Object[nPotaCountObject] = g_Object[9];
		}
		else if (nPotaCountObject < 427)
		{//���̋@
			g_Object[nPotaCountObject] = g_Object[10];
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_VARIATION; nCntObject++)
	{
		// ���b�V���̊J��
		if (g_Object[nCntObject].pMeshObject != NULL)
		{
			g_Object[nCntObject].pMeshObject->Release();
			g_Object[nCntObject].pMeshObject = NULL;
		}
		// �}�e���A���̊J��
		if (g_Object[nCntObject].pBuffMatObject != NULL)
		{
			g_Object[nCntObject].pBuffMatObject->Release();
			g_Object[nCntObject].pBuffMatObject = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObject(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCount2 = 0; nCount2 < MAX_OBJECT; nCount2++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Object[nCount2].mtxWorldObject);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object[nCount2].rot.y, g_Object[nCount2].rot.x, g_Object[nCount2].rot.z);

		D3DXMatrixMultiply(&g_Object[nCount2].mtxWorldObject, &g_Object[nCount2].mtxWorldObject, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Object[nCount2].pos.x, g_Object[nCount2].pos.y, g_Object[nCount2].pos.z);

		D3DXMatrixMultiply(&g_Object[nCount2].mtxWorldObject, &g_Object[nCount2].mtxWorldObject, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCount2].mtxWorldObject);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Object[nCount2].pBuffMatObject->GetBufferPointer();

		for (int nCntMat = 0; nCntMat<(int)g_Object[nCount2].nNumMatObject; nCntMat++)
		{
			if (g_Object[nCount2].bUse == true)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Object[nCount2].pMeshTextures[nCntMat]);
				// ���f��(�p�[�c)�̕`��
				g_Object[nCount2].pMeshObject->DrawSubset(nCntMat);
			}
		}
		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// �Z�b�g���f��
//=============================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == false)
		{
			g_Object[nCntObject].pos = pos;
			g_Object[nCntObject].rot = rot;
			g_Object[nCntObject].bUse = true;
			break;
		}
	}
}
//=============================================================================
// ���f���̓����蔻��
//=============================================================================
bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	int nCount;
	bool bLand = false;
	Player * pPlayer = GetPlayer();

	for (nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		if (pPos->x > g_Object[nCount].pos.x + g_Object[nCount].VtxMinObject.x - PULS && pPos->x < g_Object[nCount].pos.x + g_Object[nCount].VtxMaxObject.x + PULS)
		{	//X�͈̔�
			if (pPosold->z >= g_Object[nCount].pos.z + g_Object[nCount].VtxMaxObject.z + PULS && pPos->z < g_Object[nCount].pos.z + g_Object[nCount].VtxMaxObject.z + PULS)
			{
				pPos->z = g_Object[nCount].pos.z + g_Object[nCount].VtxMaxObject.z + PULS;
				pPos->z = pPosold->z;
			}
			else if (pPosold->z <= g_Object[nCount].pos.z + g_Object[nCount].VtxMinObject.z - PULS && pPos->z > g_Object[nCount].pos.z + g_Object[nCount].VtxMinObject.z - PULS)
			{
				pPos->z = g_Object[nCount].pos.z + g_Object[nCount].VtxMinObject.z - PULS;
				pPos->z = pPosold->z;
			}
		}
		if (pPos->z > g_Object[nCount].pos.z + g_Object[nCount].VtxMinObject.z - PULS && pPos->z < g_Object[nCount].pos.z + g_Object[nCount].VtxMaxObject.z + PULS)
		{	//Z�͈̔�
			if (pPosold->x >= g_Object[nCount].pos.x + g_Object[nCount].VtxMaxObject.x + PULS && pPos->x < g_Object[nCount].pos.x + g_Object[nCount].VtxMaxObject.x + PULS)
			{
				pPos->x = g_Object[nCount].pos.x + g_Object[nCount].VtxMaxObject.x + PULS;
				pPos->x = pPosold->x;
			}
			else if (pPosold->x <= g_Object[nCount].pos.x + g_Object[nCount].VtxMinObject.x - PULS && pPos->x > g_Object[nCount].pos.x + g_Object[nCount].VtxMinObject.x - PULS)
			{
				pPos->x = g_Object[nCount].pos.x + g_Object[nCount].VtxMinObject.x - PULS;
				pPos->x = pPosold->x;
			}
		}
	}
	return bLand;
}
//=========================================================================================================================
// �I�u�W�F�N�g�̎擾����
//=========================================================================================================================
Object *GetObject(void)
{
	return &g_Object[0];
}