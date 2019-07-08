#pragma once
//===============================================================================
//
// �Q�[����� [game .h]
// Author : �����ʉ�
//
//===============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//===============================================================================
//�Q�[���̏��
//===============================================================================
typedef enum
{
	GAMESTATE_NONE = 0,		//�������Ă��Ȃ����
	GAMESTATE_NORMAL,			//�ʏ���
	GAMESTATE_CLEAR,				//�N���A���
	GAMESTATE_OVER,				//�Q�[���I�[�o�[���
	GAMESTATE_MAX
} GAMESTATE;

//===============================================================================
//�v���g�^�C�v�錾
//===============================================================================
void InitGame(void);									//�Q�[����ʏ���������
void UninitGame(void);								//�Q�[����ʏI������
void UpdateGame(void);								//�Q�[����ʍX�V����
void DrawGame(void);								//�Q�[����ʕ`�揈��
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
void SetPause(bool bPause);
#endif