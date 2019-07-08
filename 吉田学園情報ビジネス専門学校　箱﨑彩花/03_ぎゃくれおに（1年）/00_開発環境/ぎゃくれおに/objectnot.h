//=============================================================================
//
// ���f������ [object.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _OBJECTNOT_H_
#define _OBJECTNOT_H_

#include "main.h"

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef struct
{
	LPD3DXMESH		pMeshObjectNot = NULL;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatObjectNot = NULL;		//�}�e���A���̏��ւ̃|�C���^
	DWORD			nNumMatObjectNot = 0;			//�}�e���A���̏��
	D3DXMATRIX		mtxWorldObjectNot;				//���[���h�}�g���b�N�X
	D3DXVECTOR3		pos;						//�ʒu
	D3DXVECTOR3		rot;						//����
	bool			bUse;						//���
	D3DXVECTOR3		VtxMinObjectNot, VtxMaxObjectNot;	//���f���̍ŏ��l�E�ő�l
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
}ObjectNot;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitObjectNot(void);
void UninitObjectNot(void);
void UpdateObjectNot(void);
void DrawObjectNot(void);
ObjectNot *GetObjectNot(void);
void SetObjectNot(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif
#pragma once
