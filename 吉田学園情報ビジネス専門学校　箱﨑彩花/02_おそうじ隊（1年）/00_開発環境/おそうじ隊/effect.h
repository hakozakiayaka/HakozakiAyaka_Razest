//=============================================================================
//
// �G�t�F�N�g���� [	effect.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// �G�t�F�N�g�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXCOLOR col;									// �F
	D3DXMATRIX mtxWorldEffect;			//���[���h�}�g���b�N�X
	float fRadius;										// ���a(�傫��)
	int nLife;												// �\������(����)
	bool bUse;											//�r���{�[�h���g���Ă��邩�ǂ���
} Effect;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife);
void DeleteEffect(int nCntEffect);

#endif