//=========================================================================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : �L�n�@���u
//
//=========================================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// �\���̒�`
//*************************************************************************************************************************
typedef enum
{
	EFFECTTYPE_NONE = 0,
	EFFECTTYPE_BULLET,
	EFFECTTYPE_EXPLOSION,
	EFFECTTYPE_EXPLOSION2,
	EFFECTTYPE_RESURRECTION, 
	EFFECTTYPE_ERUPTION,
	EFFECTTYPE_SMOKE,
	EFFECTTYPE_SNOW,
	EFFECTTYPE_RAIN,
	EFFECTTYPE_FIRE,
	EFFECTTYPE_POWDER,
	EFFECTTYPE_MAX
}EFFECTTYPE;

typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 posOld;			//�ߋ��̈ʒu
	D3DXVECTOR3 move;			//�ړ��l
	D3DXCOLOR col;				//�F
	EFFECTTYPE Type;			//���
	D3DXVECTOR3 rot;			//�@���x�N�g��
	D3DXMATRIX mtxWorld;		//���_�J���[
	float fRadius;				//���a(�傫��)
	int nIdxShadow;				//�e�̔ԍ�
	int nLife;					//�\������(����)
	int nType;					//���
	bool bUse;					//�g�p���Ă��邩�ǂ���
} EFFECT;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitEffect(void);			// �G�t�F�N�g����������
void UninitEffect(void);		// �G�t�F�N�g�I������
void UpdateEffect(void);		// �G�t�F�N�g�X�V����
void DrawEffect(void);			// �G�t�F�N�g�`�揈��

void SetBulletEffect(D3DXVECTOR3 pos, D3DXCOLOR col, EFFECTTYPE Type, float fRadius, int nLife,int nType);	// �e�G�t�F�N�g�ݒ菈��
void SetParticleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife,int nType);	// �����G�t�F�N�g�ݒ菈��

#endif