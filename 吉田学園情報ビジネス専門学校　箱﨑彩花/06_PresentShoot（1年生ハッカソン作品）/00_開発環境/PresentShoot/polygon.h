//=============================================================================
//
// �w�i���� [polygon.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

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
}Polygon;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);

void SetPolygon(int nTexNum, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHight);
void DeletePolygon();
#endif