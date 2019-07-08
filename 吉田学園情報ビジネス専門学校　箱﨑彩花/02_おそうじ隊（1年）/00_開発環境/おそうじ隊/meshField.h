//=============================================================================
//
// ���b�V���t�B�[���h���� [meshField.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 move;									//�ړ���
	D3DXVECTOR3 rot;										//����
	D3DXMATRIX mtxWorldMeshField;			//���[���h�}�g���b�N�X
	int nWidth;													//��
	int nHeight;													//����
	int nNumVertexMeshField;							//���_��
	int nNumIndexMeshField;							//�C���f�b�N�X��
	int nNumPolygonMeshField;						//�|���S����
	bool bUse;													//�g�p���Ă��邩�ǂ���
} MESHFIELD;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
MESHFIELD * GetMeshField(void);
void SetMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nHeight);
#endif
