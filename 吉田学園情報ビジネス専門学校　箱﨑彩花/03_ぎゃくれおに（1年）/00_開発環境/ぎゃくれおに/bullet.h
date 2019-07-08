//=============================================================================
//
// �|���S������ [bullet.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// �ǂ̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3		posBullet;		//�ʒu
	D3DXVECTOR3		moveBullet;		//����
	D3DXVECTOR3		rotBullet;		//����
	D3DXMATRIX		mtxWorldBullet;	//���[���h�}�g���b�N�X
	int				nIdxShadow;		//�e�̔ԍ�
	bool			bUse;			//�g�p���Ă邩�ǂ���
}Bullet;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);
Bullet *GetBullet(void);

#endif
