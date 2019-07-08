//=============================================================================
//
// �t�F�[�h���� [fadegame.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _FADEGAME_H_
#define _FADEGAME_H_

#include "main.h"
#include "game.h"

//*************************************
// �t�F�[�h�̏��
//*************************************
typedef enum
{
	FADEGAME_NONE = 0,		// �������Ă��Ȃ����
	FADEGAME_IN,						// �t�F�[�h�C�����
	FADEGAME_OUT,					// �t�F�[�h�A�E�g���
	FADEGAME_MAX
} FADEGAME;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitFadeGame(void);
void UninitFadeGame(void);
void UpdateFadeGame(void);
void DrawFadeGame(void);

void SetFadeGame(GAMESTAGE modeNext);
FADEGAME GetFadeGame(void);

#endif
