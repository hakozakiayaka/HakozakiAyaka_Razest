//=============================================================================
//
// ���b�V���t�B�[���h���� [meshbg.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _MESHBG_H_
#define _MESHBG_H_

#include "main.h"

//*****************************************************************************
// �ǂ̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3		posMeshBg;							//�ʒu
	D3DXVECTOR3		rotMeshBg;							//����
	D3DXVECTOR3		moveMeshBg;							//����
	D3DXMATRIX		mtxWorldMeshBg;						//���[���h�}�g���b�N�X
	int				nNumVertexMeshBg;					//���_��
	int				nNumIdxMeshBg;						//�C���f�b�N�X��
	int				nNumPolygonMeshBg;					//�|���S����
	bool			bUse;								//�g�p���Ă邩�ǂ���
}MeshBg;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshBg(void);
void UninitMeshBg(void);
void UpdateMeshBg(void);
void DrawMeshBg(void);

#endif
