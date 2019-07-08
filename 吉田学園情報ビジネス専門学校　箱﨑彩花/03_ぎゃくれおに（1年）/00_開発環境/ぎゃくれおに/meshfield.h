//=============================================================================
//
// ���b�V���t�B�[���h���� [meshfield.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3		posMeshField;							//�ʒu
	D3DXVECTOR3		rotMeshField;							//����
	D3DXMATRIX		mtxWorldMeshField;						//���[���h�}�g���b�N�X
	int				nNumVertexMeshField;					//���_��
	int				nNumIdxMeshField;						//�C���f�b�N�X��
	int				nNumPolygonMeshField;					//�|���S����
}MeshField;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif
