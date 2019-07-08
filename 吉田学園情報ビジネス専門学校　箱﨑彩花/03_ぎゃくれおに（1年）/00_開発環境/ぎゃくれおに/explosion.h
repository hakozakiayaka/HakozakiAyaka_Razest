//=============================================================================
//
// �|���S������ [explosion.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// �ǂ̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3		posExplosion;		//�ʒu
	D3DXVECTOR3		rotExplosion;		//����
	D3DXMATRIX		mtxWorldExplosion;	//���[���h�}�g���b�N�X
	int				nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int				nPatteunAnim;		//�A�j���[�V�����p�^�[��No.
	bool			bUse;				//�g�p���Ă邩�ǂ���
}Explosion;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

void SetExplosion(D3DXVECTOR3 pos,D3DXVECTOR3 rot);

#endif
