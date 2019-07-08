//=============================================================================
//
// �n�E�X���� [house.h]
// Author : ���舻��
//
//=============================================================================
#ifndef _HOUSE_H_
#define _HOUSE_H_

#include "main.h"

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct 
{
	D3DXVECTOR3		pos;		//���S���W
	D3DXCOLOR		col;		//�F
	float			fWidth;		//��
	float			fHight;		//����
	int				nTexNum;	//�e�N�X�`���̔ԍ�
	int				Num;		//�ԍ�
	int fHalfWidth;				//���̔���
	int fHalfHeght;				//�c�̔���
	bool			bUse;		//�g�p���Ă��邩�ǂ���
} House;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitHouse(void);
void UninitHouse(void);
void UpdateHouse(void);
void DrawHouse(void);

void SetHouse(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHight);
void DeleteHouse();
#endif