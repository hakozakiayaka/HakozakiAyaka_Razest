//=============================================================================
//
// �e�̏��� [shadow.h]
// Author : �����ʉ�
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
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;							//�e���g���Ă��邩�ǂ���
	int nIdxShadow;					//�e�̃C���f�b�N�X
	float fWidth;							//�e�̕�
	float fHeight;						//�e�̍���
	float fLength;						//�Ίp���̒���
	D3DXVECTOR3 OtherPos;	//4���_�̍��W
} Shadow;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);	//�e�̔ԍ��A�ʒu
void DeleteShadow(int nIdxShadow);
#endif
