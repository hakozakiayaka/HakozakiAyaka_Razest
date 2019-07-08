//=============================================================================
//
// ���b�V���V�����_�[���� [meshCylinder.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 move;									//�ړ���
	D3DXVECTOR3 rot;										//����
	D3DXMATRIX mtxWorldMeshCylinder;			//���[���h�}�g���b�N�X
} MESHCYLINDER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);

#endif
