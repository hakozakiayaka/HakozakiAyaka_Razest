//=============================================================================
//
// ���f������ [model.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMeshModel = NULL;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel = NULL;	//�}�e���A���̏��ւ̃|�C���^
	DWORD nNumMatModel = NULL;					//�}�e���A���̏��
	D3DXVECTOR3 pos;										//�ʒu
	D3DXVECTOR3 rot;											//����
	D3DXMATRIX mtxWorld;									//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMinModel;						//���f���̍ŏ��l
	D3DXVECTOR3 vtxMaxModel;						//���f���̍ő�l
	int nIdxModelShadow;										//�e�̔ԍ�
	float fShadowWidth;										//�e�̕�
	float fShadowHeight;										//�e�̍���

	bool bUse;														//���f�����g�p����Ă��邩�ǂ���
} Model;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model * GetModel(void);
void CollisionModel(D3DXVECTOR3 * pPos, D3DXVECTOR3  * pPosOld);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCntModel, float fShadowWidth, float fShadowHeight);
#endif
