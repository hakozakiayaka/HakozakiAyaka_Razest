//=============================================================================
//
// �|�[�Y��� [pause.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "pause.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "game.h"
#include "fade.h"
#include "pausefade.h"
#include "pausestand.h"
#include "pausecontinue.h"
#include "pauseretry.h"
#include "pausequit.h"
#include "BG.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
PAUSESTATE g_PauseMode;		//�|�[�Y�̏��
int g_SelectMode;
int g_PauseMax;				//�|�[�Y��Ԃ̍ő吔
bool g_bPauseDecide;

//=============================================================================
// ����������
//=============================================================================
void InitPause(void)
{
	//�ϐ��̏�����
	g_PauseMode = PAUSESTATE_NONE;
	g_SelectMode = PAUSESTATE_CONTINUE;
	g_PauseMax = PAUSESTATE_MAX;
	g_bPauseDecide = true;

	InitPauseFade();		//��ʂ���������
	InitPauseStand();		//�䎆
	InitPauseContinue();	//�R���e�B�j���[
	InitPauseRetry();		//���g���C
	InitPauseQuit();		//�N���C�G�b�g
}

//=============================================================================
// �I������
//=============================================================================
void UninitPause(void)
{
	UninitPauseFade();		//��ʂ���������
	UninitPauseStand();		//�䎆
	UninitPauseContinue();	//�R���e�B�j���[
	UninitPauseRetry();		//���g���C
	UninitPauseQuit();		//�N���C�G�b�g
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePause(void)
{
	UpdatePauseFade();		//��ʂ���������
	UpdatePauseStand();		//�䎆
	UpdatePauseContinue();	//�R���e�B�j���[
	UpdatePauseRetry();		//���g���C
	UpdatePauseQuit();		//�N���C�G�b�g

	if (GetKeyboardTrigger(DIK_W) == true)
	{
		PlaySound(SOUND_LABEL_SE_KARSOL);
		g_SelectMode = (g_SelectMode + (3 - 1)) % 3;
	}
	if (GetKeyboardTrigger(DIK_S) == true)
	{
		PlaySound(SOUND_LABEL_SE_KARSOL);
		g_SelectMode = (g_SelectMode + 1) % 3;
	}

	if (g_SelectMode == 0)
	{
		SetPauseContinue(CONTINUESTATE_SELECT);
		SetPauseRetry(RETRYSTATE_NORMAL);
		SetPauseQuit(QUITSTATE_NORMAL);

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_ENTER);
			g_PauseMode = PAUSESTATE_CONTINUE;
		}
	}
	else if (g_SelectMode == 1)
	{
		SetPauseContinue(CONTINUESTATE_NORMAL);
		SetPauseRetry(RETRYSTATE_SELECT);
		SetPauseQuit(QUITSTATE_NORMAL);

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_ENTER);
			g_PauseMode = PAUSESTATE_RETRY;
		}
	}
	else if(g_SelectMode == 2)
	{
		SetPauseContinue(CONTINUESTATE_NORMAL);
		SetPauseRetry(RETRYSTATE_NORMAL);
		SetPauseQuit(QUITSTATE_SELECT);

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			PlaySound(SOUND_LABEL_SE_ENTER);
			g_PauseMode = PAUSESTATE_QUIT;
		}
	}

	//�t�F�[�h�����擾����
	FADE fade;
	fade = GetFade();

	switch (g_PauseMode)
	{
	case PAUSESTATE_CONTINUE:
		g_PauseMode = PAUSESTATE_NONE;
		SetPause(false);
		break;

	case PAUSESTATE_RETRY:
		g_PauseMode = PAUSESTATE_NONE;

		if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_GAME);
		}
		break;

	case PAUSESTATE_QUIT:
		g_PauseMode = PAUSESTATE_NONE;

		if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_TITLE);
		}
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPause(void)
{
	DrawPauseFade();		//��ʂ���������
	DrawPauseStand();		//�䎆
	DrawPauseContinue();	//�R���e�B�j���[
	DrawPauseRetry();		//���g���C
	DrawPauseQuit();		//�N���C�G�b�g
}