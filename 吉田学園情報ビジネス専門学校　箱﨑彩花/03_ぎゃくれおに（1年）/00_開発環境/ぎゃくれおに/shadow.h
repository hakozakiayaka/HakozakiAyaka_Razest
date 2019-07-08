//=============================================================================
//
// �|���S������ [shadow.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// �e�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3		pos;			//�ʒu
	D3DXVECTOR3		rot;			//����
	D3DXMATRIX		mtxWorld;		//���[���h�}�g���b�N�X
	float			ShadowWidth;	//��
	float			ShadowDepth;	//�[��
	bool			bUse;			//�g�p���Ă��邩�ǂ���
}Shadow;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float ShadowWidth, float ShadowDepth);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos,D3DXVECTOR3 rot);
void DeleteShadow(int nIdxShadow);

#endif
