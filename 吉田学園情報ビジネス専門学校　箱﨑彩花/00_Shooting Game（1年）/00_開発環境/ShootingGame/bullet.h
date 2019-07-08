//=============================================================================
//
// �e���� [bullet.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//�v���C���[�̒e
	BULLETTYPE_ENEMY,			//�G�̒e
	BULLETTYPE_MAX
} BULLETTYPE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type);		//���ˈʒu�A�ړ��ʁA���

#endif