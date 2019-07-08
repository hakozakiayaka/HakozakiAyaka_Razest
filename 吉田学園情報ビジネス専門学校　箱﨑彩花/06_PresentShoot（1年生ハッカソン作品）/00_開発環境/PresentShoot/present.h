//=============================================================================
//
// �v���[���g�̏��� [present.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _PRESENT_H_
#define _PRESENT_H_

#include "main.h"

//=============================================================================
// ��ނ̐ݒ�
//=============================================================================
typedef enum
{
	PRESENTTYPE_BAG = 0,
	PRESENTTYPE_L,
	PRESENTTYPE_M,
	PRESENTTYPE_S,
	PRESENTTYPE_MAX
}PRESENTTYPE;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct 
{
	D3DXVECTOR3		pos;		//���S���W
	D3DXVECTOR3		OldPos;		//�O��̈ʒu
	D3DXVECTOR3		move;		//�ړ���
	float			fGravity;	//�d��
	int				nTexNum;	//�e�N�X�`���̔ԍ�
	PRESENTTYPE		Type;		//�^�C�v�̐ݒ�
	bool			bUse;		//�g�p���Ă��邩�ǂ���
}Present;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPresent(void);
void UninitPresent(void);
void UpdatePresent(void);
void DrawPresent(void);

void SetPresent(int nTexNum, D3DXVECTOR3 pos);
void DeletePresent(int nCntPresent, PRESENTTYPE type);
#endif