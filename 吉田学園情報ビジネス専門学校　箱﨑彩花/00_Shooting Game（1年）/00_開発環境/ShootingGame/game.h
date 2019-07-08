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
//�}�N����`
//===============================================================================
#define ENEMY_HEIGHT			(120)
#define ENEMY_HEIGHT2			(170)
#define ENEMY_HEIGHT3			(220)
#define ENEMY_HEIGHT4			(280)

#define ENEMY_WIDE				(250)
#define ENEMY_WIDE2				(370)
#define ENEMY_WIDE3				(450)
#define ENEMY_WIDE4				(570)
#define ENEMY_WIDE5				(650)
#define ENEMY_WIDE6				(770)
#define ENEMY_WIDE7				(850)
#define ENEMY_WIDE8				(1000)

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