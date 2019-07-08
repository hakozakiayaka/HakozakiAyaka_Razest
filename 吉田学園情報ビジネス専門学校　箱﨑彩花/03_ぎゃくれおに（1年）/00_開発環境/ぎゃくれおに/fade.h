//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "Game.h"
//*************************************
// �t�F�[�h�̏��
//*************************************
typedef enum
{
	FADE_NONE = 0,		// �������Ă��Ȃ����
	FADE_IN,			// �t�F�[�h�C�����
	FADE_OUT,			// �t�F�[�h�A�E�g���
	FADE_MAX
} FADE;

typedef enum
{
	MODEFADE_NONE = 0,		// �������Ă��Ȃ����
	MODEFADE_NOLMAL,		
	MODEFADE_GAME,			
	MODEFADE_MODE,
	MODEFADE_MAX
} MODEFADE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitFade(MODE modeNext);		//�t�F�[�h�̏���������
void UninitFade(void);				//�t�F�[�h�̏I������
void UpdateFade(void);				//�t�F�[�h�̍X�V����
void DrawFade(void);				//�t�F�[�h�̕`�揈��

void SetFade(MODE modeNext);
FADE GetFade(void);

#endif
