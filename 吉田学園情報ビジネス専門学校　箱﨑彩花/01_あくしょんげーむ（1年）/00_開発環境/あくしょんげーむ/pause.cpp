//===============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"pausemenu.h"
#include "continu.h"
#include "retry.h"
#include "quit.h"
#include "pause.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
PAUSEATATE g_Pause;		//�|�[�Y�̏��
int g_nSelect;						//�I������

//===============================================================================
//�|�[�Y����������
//===============================================================================
void InitPause(void)
{
	//������
	g_nSelect = 0;

	InitPauseMenu();
	InitContinu();
	InitRetry();
	InitQuit();
}

//===============================================================================
//�|�[�Y�I������
//===============================================================================
void UninitPause(void)
{
	UninitPauseMenu();
	UninitContinu();
	UninitRetry();
	UninitQuit();
}

//===============================================================================
//�|�[�Y�X�V����
//===============================================================================
void UpdatePause(void)
{
	FADE g_fade;
	g_fade = GetFade();

	if (GetKeyboardTrigger(DIK_S) == true)
	{	//���iS�j�L�[�������ꂽ
		g_nSelect = (g_nSelect + 1) % 3;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	if (GetKeyboardTrigger(DIK_W) == true)
	{	//��iW�j�������ꂽ
		g_nSelect = (g_nSelect + 2) % 3;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (g_nSelect == 0)
	{
		SetContinue(CONTUNUESTATE_SELECT);
		SetRetry(RETRYSTATE_NONE);
		SetQuit(QUITSTATE_NONE);

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_fade != FADE_OUT)
			{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
				g_Pause = PAUSESTATE_CONTINU;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}
	if (g_nSelect == 1)
	{
		SetContinue(CONTINUESTATE_NONE);
		SetRetry(RETRYSTATE_SELECT);
		SetQuit(QUITSTATE_NONE);

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
			if (g_fade != FADE_OUT)
			{
				g_Pause = PAUSESTATE_RETRY;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}
	if (g_nSelect == 2)
	{
		SetContinue(CONTINUESTATE_NONE);
		SetRetry(RETRYSTATE_NONE);
		SetQuit(QUITSTATE_SELECT);

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_fade != FADE_OUT)
			{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
				g_Pause = PAUSESTATE_QUIT;
				PlaySound(SOUND_LABEL_SE_DECIDE);
			}
		}
	}

	switch (g_Pause)
	{
	case PAUSESTATE_CONTINU:
		g_Pause = PAUSESTATE_NONE;
		SetPause(false);
		break;

	case PAUSESTATE_RETRY:
		g_Pause = PAUSESTATE_NONE;
		SetFade(MODE_GAME);
		break;

	case PAUSESTATE_QUIT:
		g_Pause = PAUSESTATE_NONE;
		SetFade(MODE_TITLE);
		break;
	}

	UpdatePauseMenu();
	UpdateContinu();
	UpdateRetry();
	UpdateQuit();
}

//===============================================================================
//�|�[�Y�`�揈��
//===============================================================================
void DrawPause(void)
{
	DrawPauseMenu();
	DrawContinu();
	DrawRetry();
	DrawQuit();
}