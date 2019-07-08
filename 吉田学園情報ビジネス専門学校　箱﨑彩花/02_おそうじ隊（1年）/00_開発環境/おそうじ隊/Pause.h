//=============================================================================
//
// �|�[�Y���� [Pausemenu.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _PAUSEMENU_H_
#define _PAUSEMENU_

#include "main.h"

//*****************************************************************************
// �|�[�Y�̏�Ԃ̎��
//*****************************************************************************
typedef enum
{
	PAUSESTATE_NONE = 0,
	PAUSESTATE_CONTINUE,
	PAUSESTATE_RETRY,
	PAUSESTATE_QUIT,
	PAUSESTATE_MAX,
}PAUSESTATE;

typedef enum
{
	PAUSESTATECOLOR_NONE = 0,
	PAUSESTATECOLOR_CONTINUE,
	PAUSESTATECOLOR_RETRY,
	PAUSESTATECOLOR_QUIT,
	PAUSESTATECOLOR_MAX,
}COLORSTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPausemenu(void);
void UninitPausemenu(void);
void UpdatePausemenu(void);
void DrawPausemenu(void);

#endif