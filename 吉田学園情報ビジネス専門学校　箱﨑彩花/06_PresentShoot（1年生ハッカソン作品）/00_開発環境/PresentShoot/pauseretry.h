//=============================================================================
//
// �|�[�Y���g���C���� [pauseretry.h]
// Author : ���������@Sato_Aumi
//
//=============================================================================
#ifndef _PAUSERETRY_H_
#define _PAUSERETRY_H_

#include "main.h"

//=============================================================================
// ���g���C�̏�Ԃ̎��
//=============================================================================
typedef enum
{
	RETRYSTATE_NORMAL = 0,
	RETRYSTATE_SELECT,
	RETRYSTATE_MAX,
}RETRYSTATE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPauseRetry(void);
void UninitPauseRetry(void);
void UpdatePauseRetry(void);
void DrawPauseRetry(void);

void SetPauseRetry(RETRYSTATE state);
#endif
