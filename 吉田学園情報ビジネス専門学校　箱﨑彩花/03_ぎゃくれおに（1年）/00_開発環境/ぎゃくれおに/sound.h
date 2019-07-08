//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �L�n�@���u
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
	SOUND_LABEL_PLANEBGM001,			// �^�C�g��
	SOUND_LABEL_PLANEBGM002,			// �Q�[����
	SOUND_LABEL_PLANEBGM003,			// ���U���g
	SOUND_LABEL_PLANEBGM004,			// �Z���N�g
	SOUND_LABEL_SE_DOWN000,				// ����
	SOUND_LABEL_SE_OPEN000,				// �J��
	SOUND_LABEL_SE_DECIDE,				// ���艹
	SOUND_LABEL_SE_UPDWON,				// ���j���[�ړ�
	SOUND_LABEL_SE_CHICEN,				// �j���g��
	SOUND_LABEL_SE_BUTUKARU,			// �Ԃ���
	SOUND_LABEL_SE_HENNSIN,

	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label); //�Q�[���̏������߂��@
void StopSound(SOUND_LABEL label);	  //�������O�������ăX�g�b�v��������
void StopSound(void);

#endif
