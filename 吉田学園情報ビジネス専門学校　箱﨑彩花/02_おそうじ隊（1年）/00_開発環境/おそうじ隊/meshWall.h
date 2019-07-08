//=============================================================================
//
// ���b�V���E�H�[������ [meshWall.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 move;									//�ړ���
	D3DXVECTOR3 rot;										//����
	int nWidth;													//��
	int nHeight;													//����
	int nTexType;												//�e�N�X�`���̃^�C�v
	D3DXMATRIX mtxWorldMeshWall;			//���[���h�}�g���b�N�X
	int nNumVertexMeshWall;																	//���_��
	int nNumIndexMeshWall;																	//�C���f�b�N�X��
	int nNumPolygonMeshWall;																//�|���S����
	bool bUse;
} MESHWALL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight, int nTexType);

#endif
