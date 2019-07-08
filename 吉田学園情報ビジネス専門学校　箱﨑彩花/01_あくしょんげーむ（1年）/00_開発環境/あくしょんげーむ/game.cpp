//===============================================================================
//
// �Q�[����� [game.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include"bg.h"
#include "player.h"
#include "block.h"
#include "item.h"
#include "game.h"
#include "score.h"
#include "input.h"
#include "time.h"
#include "fade.h"
#include "pause.h"
#include "explosion.h"
#include "fadegame.h"
#include "sound.h"

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;	//�Q�[���̏��
GAMESTAGE g_gameStage;										//�Q�[���̃X�e�[�W
int g_nCounterGameState;											//��ԊǗ��̃J�E���^�[
bool g_bPause;															//�|�[�Y�����ǂ���

//===============================================================================
//�Q�[����ʏ���������
//===============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;				//�ʏ��Ԃɐݒ�
	g_gameStage = GAMESTAGE_SELECT;					//�X�e�[�W�I���ɐݒ�
	g_nCounterGameState = 0;
	g_bPause = false;

	//�w�i�̏���������
	InitBG();
	//�v���C���[�̏���������
	InitPlayer();
	//�X�R�A�̏���������
	InitScore();
	//�^�C���̏���������
	InitTime();
	//�|�[�Y�̏���������
	InitPause();
	//�A�C�e���̏���������
	InitItem();
	//�u���b�N�̏���������
	InitBlock();
	//�����̏���������
	InitExplosion();
	//�Q�[���t�F�[�h�̏���������
	InitFadeGame();
}

//===============================================================================
//�Q�[����ʏI������
//===============================================================================
void UninitGame(void)
{
	//�w�i�̏I������
	UninitBG();
	//�v���C���[�̏I������
	UninitPlayer();
	//�X�R�A�̏I������
	UninitScore();
	//�^�C���̏I������
	UninitTime();
	//�A�C�e���̏I������
	UninitItem();
	//�u���b�N�̏I������
	UninitBlock();
	//�|�[�Y�̏I������
	UninitPause();
	//�����̏I������
	UninitExplosion();
	//�Q�[���t�F�[�h�̏I������
	UninitFadeGame();
}

//===============================================================================
//�Q�[����ʍX�V����
//===============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{	//	�|�[�Y�̏���
		PlaySound(SOUND_LABEL_SE_PAUSE);
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			break;

		case GAMESTATE_CLEAR:
			g_nCounterGameState++;
			if (g_nCounterGameState <= 60)
			{
				//���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;

		case GAMESTATE_OVER:
			g_nCounterGameState++;
			if (g_nCounterGameState <= 60)
			{
				//���(���[�h)�̐ݒ�
				SetFade(MODE_RESULT);
			}
			break;
		}

		//�w�i�̍X�V����
		UpdateBG();
		//�v���C���[�̍X�V����
		UpdatePlayer();
		//�X�R�A�̍X�V����
		UpdateScore();
		//�^�C���̍X�V����
		UpdateTime();
		//�A�C�e���̍X�V����
		UpdateItem();
		//�u���b�N�̍X�V����
		UpdateBlock();
		//�����̍X�V����
		UpdateExplosion();
		//�Q�[���t�F�[�h�X�V����
		UpdateFadeGame();
		}
	else
	{
		//�|�[�Y�̍X�V����
		UpdatePause();
	}
}

//===============================================================================
//�Q�[����ʕ`�揈��
//===============================================================================
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();
	//�v���C���[�̕`�揈��
	DrawPlayer();
	//�X�R�A�̕`�揈��
	DrawScore();
	//�^�C���̕`�揈��
	DrawTime();
	//�A�C�e���̕`�揈��
	DrawItem();
	//�u���b�N�̕`�揈��
	DrawBlock();
	//�����̕`�揈��
	DrawExplosion();
	//�Q�[���t�F�[�h�̕`�揈��
	DrawFadeGame();

	if (g_bPause == true)
	{
		//�|�[�Y�̕`�揈��
		DrawPause();
	}
}

//===============================================================================
//�Q�[���̏�Ԑݒ�
//===============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//===============================================================================
//�Q�[����Ԃ̎擾
//===============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//===============================================================================
//�X�e�[�W�̐ݒ�
//===============================================================================
void SetGameStage(GAMESTAGE stage)
{
	//�w�i�̏I������
	UninitBG();
	//�u���b�N�I������
	UninitBlock();
	//�A�C�e���̏I������
	UninitItem();

	StopSound(SOUND_LABEL_BGM002);
	StopSound(SOUND_LABEL_BGM003);

	g_gameStage = stage;

	//�w�i�̏���������
	InitBG();
	//�u���b�N�̏���������
	InitBlock();
	//�A�C�e���̏���������
	InitItem();

	if (stage == GAMESTAGE_SELECT)
	{	//�I�����
		PlaySound(SOUND_LABEL_BGM002);
	}
	else if (stage == GAMESTAGE1 || stage == GAMESTAGE2)
	{	//�X�e�[�W1�ƃX�e�[�W2
		PlaySound(SOUND_LABEL_BGM003);
	}
}

//===============================================================================
//�X�e�[�W�̎擾
//===============================================================================
GAMESTAGE GetGameStage(void)
{
	return g_gameStage;
}

//===============================================================================
//�|�[�Y��Ԃ̎擾
//===============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}