//=============================================================================
//
// �������� [explosion.h]
// Author :�����ʉ�
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXCOLOR col;									//�F
	int nCounterAnim;								//�A�j���[�V�����J�E���^�[
	int nPatternAnim;								//�A�j���[�V����No.
	D3DXMATRIX mtxWorldBullet;			//���[���h�}�g���b�N�X
	int nIdxShadow;
	bool bUse;											//�g�p���Ă��邩�ǂ���
} Explosion;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos,D3DXCOLOR col);	//�\���ʒu�A�F

#endif