//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : ��������	SatoAsumi
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//=============================================================================
// �G�t�F�N�g�̎��
//=============================================================================
typedef enum
{
	EFFECTTYPE_SANTA = 0, 
	EFFECTTYPE_TITLE,
	EFFECTTYPE_MAX
}EFFECTTYPE;

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;			// �F
	float fRadius;			// ���a(�傫��)
	float fChngeRadius;		// ���a�̕ω���
	float fRadiusCnt;		// �ω��ʃJ�E���^�[
	float fGravity;			// �d��
	float fAngle;			// �p�x
	int nLife;				// �\������(����)
	int nTexType;			// �e�N�X�`���̃^�C�v�ݒ�
	bool bAngle;			// �p�x
	bool bUse;				// �g�p���Ă��邩�ǂ���
	EFFECTTYPE type;
} EFFECT;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int TexType);
#endif