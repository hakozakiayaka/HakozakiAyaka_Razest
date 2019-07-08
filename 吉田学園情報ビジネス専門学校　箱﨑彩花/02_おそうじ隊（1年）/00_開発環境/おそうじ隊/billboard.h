//=============================================================================
//
// �r���{�[�h���� [	billboard.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//*****************************************************************************
// �r���{�[�h�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 rot;								//����
	D3DXMATRIX mtxWorldBillboard;		//���[���h�}�g���b�N�X
	int nIdxBillboardShadow;					//�e���g���Ă��邩�ǂ���
	int nTexType;										//�e�N�X�`���̃^�C�v
	bool bUse;											//�r���{�[�h���g���Ă��邩�ǂ���
} Billboard;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int TexType);
void DeleteBillboard(int nCntBillboard);

#endif