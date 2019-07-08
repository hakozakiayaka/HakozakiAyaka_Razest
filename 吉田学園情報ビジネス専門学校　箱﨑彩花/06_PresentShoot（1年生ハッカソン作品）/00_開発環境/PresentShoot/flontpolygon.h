//=============================================================================
//
// �|���S������ [flontpolygon.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _FLONTPOLYGON_H_
#define _FLONTPOLYGON_H_

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
	bool			bUse;		//�g�p���Ă��邩�ǂ���
}FlontPolygon;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitFlontPolygon(void);
void UninitFlontPolygon(void);
void UpdateFlontPolygon(void);
void DrawFlontPolygon(void);

void SetFlontPolygon(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHight);
void DeleteFlontPolygon();
#endif