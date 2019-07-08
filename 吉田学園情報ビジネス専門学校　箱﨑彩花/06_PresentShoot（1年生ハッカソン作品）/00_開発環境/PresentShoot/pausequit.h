//=============================================================================
//
// �|�[�Y�N���C�G�b�g���� [pausequit.h]
// Author : ���������@Sato_Aumi
//
//=============================================================================
#ifndef _PAUSEQUIT_H_
#define _PAUSEQUIT_H_

#include "main.h"

//=============================================================================
// �N���C�G�b�g�̏�Ԃ̎��
//=============================================================================
typedef enum
{
	QUITSTATE_NORMAL = 0,
	QUITSTATE_SELECT,
	QUITSTATE_MAX,
}QUITSTATE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPauseQuit(void);
void UninitPauseQuit(void);
void UpdatePauseQuit(void);
void DrawPauseQuit(void);

void SetPauseQuit(QUITSTATE state);
#endif
