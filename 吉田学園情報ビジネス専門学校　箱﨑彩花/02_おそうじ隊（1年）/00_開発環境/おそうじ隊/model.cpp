//=============================================================================
//
// ���f������ [model.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL1					 "data/MODEL/bed.x"							//���f���̓ǂݍ���[�x�b�h]
#define MODEL2					 "data/MODEL/airplane000.x"			//���f���̓ǂݍ���[��]
#define MODEL3					 "data/MODEL/kuma.x"						//���f���̓ǂݍ���[����]
#define MAX_MODEL	(3)																//���f���̍ő吔

#define MODEL_TEX1		"date/TEXTURE/t.jpg "						//�e�N�X�`���̓ǂݍ���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureModel = NULL;			//�e�N�X�`���ւ̃|�C���^
Model g_aModel[MAX_MODEL];

//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̎擾
	int nNumVtx;															//���_��
	DWORD sizeFVF;													//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;														//���_�o�b�t�@�ւ̃|�C���^

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aModel[0].pBuffMatModel,
		NULL,
		&g_aModel[0].nNumMatModel,
		&g_aModel[0].pMeshModel);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aModel[1].pBuffMatModel,
		NULL,
		&g_aModel[1].nNumMatModel,
		&g_aModel[1].pMeshModel);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_aModel[2].pBuffMatModel,
		NULL,
		&g_aModel[2].nNumMatModel,
		&g_aModel[2].pMeshModel);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// �\���̂̏����ݒ�
		g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntModel].fShadowWidth = 0;
		g_aModel[nCntModel].fShadowHeight = 0;
		g_aModel[nCntModel].bUse = false;

		//�ő�l�ƍŏ��l
		g_aModel[nCntModel].vtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
		g_aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);

		//���_�����擾
		nNumVtx = g_aModel[nCntModel].pMeshModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCntModel].pMeshModel->GetFVF());

		//���_�t�H�[�}�b�g�����b�N
		g_aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{	//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

			//�ŏ��l
			if (vtx.x < g_aModel[nCntModel].vtxMinModel.x)
			{
				g_aModel[nCntModel].vtxMinModel.x = vtx.x;
			}
			if (vtx.z < g_aModel[nCntModel].vtxMinModel.z)
			{
				g_aModel[nCntModel].vtxMinModel.z = vtx.z;
			}

			//�ő�l
			if (vtx.x > g_aModel[nCntModel].vtxMaxModel.x)
			{
				g_aModel[nCntModel].vtxMaxModel.x = vtx.x;
			}
			if (vtx.z > g_aModel[nCntModel].vtxMaxModel.z)
			{
				g_aModel[nCntModel].vtxMaxModel.z = vtx.z;
			}

			pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
		}

		//���_�o�b�t�@���A�����b�N
		g_aModel[nCntModel].pMeshModel->UnlockVertexBuffer();

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, MODEL_TEX1, &g_pTextureModel);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	// ���b�V���̊J��
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].pMeshModel != NULL)
		{
			g_aModel[nCntModel].pMeshModel->Release();
			g_aModel[nCntModel].pMeshModel = NULL;
		}

		if (g_aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_aModel[nCntModel].pBuffMatModel->Release();
			g_aModel[nCntModel].pBuffMatModel = NULL;
		}
	}

	//�e�N�X�`���̊J��
	if (g_pTextureModel != NULL)
	{
		g_pTextureModel->Release();
		g_pTextureModel = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;							//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;										//���݂̃}�g���b�N�X�ۑ��p
	D3DXMATERIAL * pMat;											//�}�e���A���f�[�^�ւ̃|�C���^

	////Z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);

			// �ړ��i�ʒu�j�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aModel[nCntModel].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`����NULL�ɂ���
				pDevice->SetTexture(0, NULL);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureModel);

				// ���f��(�p�[�c)�̕`��
				g_aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);

			////Z�e�X�g�����ɖ߂�
			//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		}
	}
}

//=============================================================================
// ���f���̎擾
//=============================================================================
Model * GetModel(void)
{
	return &g_aModel[0];
}

//=============================================================================
// ���f���̓����蔻��
//=============================================================================
void CollisionModel(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld)
{
	//�v���C���[�̎擾
	Player * pPlayer = GetPlayer();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			if (pPos->x + pPlayer->vtxMinPlayer.x < g_aModel[nCntModel].vtxMaxModel.x + g_aModel[nCntModel].pos.x
				&& pPos->x + pPlayer->vtxMaxPlayer.x > g_aModel[nCntModel].vtxMinModel.x + g_aModel[nCntModel].pos.x)
			{	//X�͈͔̔���
				if (pPosOld->z + pPlayer->vtxMaxPlayer.z <= g_aModel[nCntModel].vtxMinModel.z + g_aModel[nCntModel].pos.z
					&& pPos->z + pPlayer->vtxMaxPlayer.z > g_aModel[nCntModel].vtxMinModel.z + g_aModel[nCntModel].pos.z)
				{	//��O�̔���
					pPos->z = g_aModel[nCntModel].vtxMinModel.z + g_aModel[nCntModel].pos.z - pPlayer->vtxMaxPlayer.z;
				}
				if (pPosOld->z + pPlayer->vtxMinPlayer.z >= g_aModel[nCntModel].vtxMaxModel.z + g_aModel[nCntModel].pos.z
					&& pPos->z + pPlayer->vtxMinPlayer.z < g_aModel[nCntModel].vtxMaxModel.z + g_aModel[nCntModel].pos.z)
				{	//���̔���
					pPos->z = g_aModel[nCntModel].vtxMaxModel.z + g_aModel[nCntModel].pos.z - pPlayer->vtxMinPlayer.z;
				}
			}
			if (pPos->z + pPlayer->vtxMaxPlayer.z < g_aModel[nCntModel].vtxMaxModel.z + g_aModel[nCntModel].pos.z
				&& pPos->z + pPlayer->vtxMaxPlayer.z > g_aModel[nCntModel].vtxMinModel.z + g_aModel[nCntModel].pos.z)
			{	//Z�͈͔̔���
				if (pPosOld->x + pPlayer->vtxMaxPlayer.x <= g_aModel[nCntModel].vtxMinModel.x + g_aModel[nCntModel].pos.x
					&& pPos->x + pPlayer->vtxMaxPlayer.x > g_aModel[nCntModel].vtxMinModel.x + g_aModel[nCntModel].pos.x)
				{	//�E�̔���
					pPos->x = g_aModel[nCntModel].vtxMinModel.x + g_aModel[nCntModel].pos.x - pPlayer->vtxMaxPlayer.x;
				}
				if (pPosOld->x + pPlayer->vtxMinPlayer.x >= g_aModel[nCntModel].vtxMaxModel.x + g_aModel[nCntModel].pos.x
					&& pPos->x + pPlayer->vtxMinPlayer.x < g_aModel[nCntModel].vtxMaxModel.x + g_aModel[nCntModel].pos.x)
				{	//���̔���
					pPos->x = g_aModel[nCntModel].vtxMaxModel.x + g_aModel[nCntModel].pos.x - pPlayer->vtxMinPlayer.x;
				}
			}
		}
	}
}

//=============================================================================
// ���f���̐ݒ�
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCntModel, float fShadowWidth, float fShadowHeight)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == false)
		{
			g_aModel[nCntModel].pos = pos;
			g_aModel[nCntModel].rot = rot;
			g_aModel[nCntModel].bUse = true;
			g_aModel[nCntModel].nIdxModelShadow = SetShadow(g_aModel[nCntModel].pos, g_aModel[nCntModel].rot, fShadowWidth, fShadowHeight);
			break;
		}
	}
}