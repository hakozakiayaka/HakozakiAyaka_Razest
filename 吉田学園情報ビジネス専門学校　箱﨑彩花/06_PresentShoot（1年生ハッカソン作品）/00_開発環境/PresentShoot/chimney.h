//=============================================================================
//
// ���˂̏��� [chimney.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _CHIMNEY_H_
#define _CHIMNEY_H_

#include "main.h"

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 move;			//�ړ���
	float		fWidth;			//��
	float		fHight;			//����
	int			nCounterMove;	//�ړ��ʂ̃J�E���^�[
	bool	    bIn;			//�����Ă��邩�ǂ���
	bool		bUse;			//�g�p���Ă��邩�ǂ���
}Chimney;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitChimney(void);
void UninitChimney(void);
void UpdateChimney(void);
void DrawChimney(void);

void SetChimney(D3DXVECTOR3 pos, float fWidth, float fHight);
bool CollisionChimney(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fWhidth, float fHeight);
Chimney *GetChimney(void);
#endif