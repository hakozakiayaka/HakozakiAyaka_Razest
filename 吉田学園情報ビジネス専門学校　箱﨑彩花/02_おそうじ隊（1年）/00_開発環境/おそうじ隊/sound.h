//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// title BGM
	SOUND_LABEL_BGM001,				// tutorial BGM1
	SOUND_LABEL_BGM002,				// stageselect BGM2
	SOUND_LABEL_BGM003,				// stage1 BGM3
	SOUND_LABEL_BGM004,				// stage2 BGM4
	SOUND_LABEL_BGM005,				// game_over BGM5
	SOUND_LABEL_BGM006,				// game_clear BGM6
	SOUND_LABEL_SE_HIT000,				// �q�b�g
	SOUND_LABEL_SE_SHOT000,				// �V���b�g
	SOUND_LABEL_SE_DECIDE,			// ���艹
	SOUND_LABEL_SE_PAUSE,			// �|�[�Y
	SOUND_LABEL_SE_SELECT,			// �I����
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
