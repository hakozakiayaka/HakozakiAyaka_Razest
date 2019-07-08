//=============================================================================
//
// �|�[�Y�R���e�B�j���[���� [pousecontinue.h]
// Author : ���������@Sato_Aumi
//
//=============================================================================
#ifndef _PAUSECONTINUE_H_
#define _PAUSECONTINUE_H_

#include "main.h"

//=============================================================================
// �R���e�B�j���[�̏�Ԃ̎��
//=============================================================================
typedef enum
{
	CONTINUESTATE_NORMAL = 0,
	CONTINUESTATE_SELECT,
	CONTINUESTATE_MAX,
}CONTINUESTATE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPauseContinue(void);
void UninitPauseContinue(void);
void UpdatePauseContinue(void);
void DrawPauseContinue(void);

void SetPauseContinue(CONTINUESTATE state);
#endif

