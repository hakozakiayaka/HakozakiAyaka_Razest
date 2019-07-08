//=============================================================================
//
// ���f������ [model.h]
// Author : 
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
	LPD3DXBUFFER pBuffMatModel = NULL;		//�}�e���A���̏��ւ̃|�C���^
	DWORD nNumMatModel = 0;					//�}�e���A���̏��
	D3DXMATRIX mtxWorldModel;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
}Model;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model *GetModel(void);

#endif
