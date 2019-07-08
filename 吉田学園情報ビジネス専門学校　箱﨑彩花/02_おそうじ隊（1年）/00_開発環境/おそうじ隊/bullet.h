//=============================================================================
//
// �e���� [bullet.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// �e�̃r���{�[�h�̍\����
//*****************************************************************************
typedef enum
{
	BULLETTYPE_ENEMY = 0,			//�G�̒e
	BULLETTYPE_MAX
} BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 move;							//�ړ���
	D3DXMATRIX mtxWorldBullet;			//���[���h�}�g���b�N�X
	int nIdxBulletShadow;							//�e
	bool bUse;											//�r���{�[�h���g���Ă��邩�ǂ���
	D3DXVECTOR3 vecA;							//��
	D3DXVECTOR3 vecC;							//aPos����Bullet.pos�܂ł̋���
	BULLETTYPE type;								//�e�̎��
} Bullet;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type);

#endif