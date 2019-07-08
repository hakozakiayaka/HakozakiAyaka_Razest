//===============================================================================
//
// �Q�[����� [game.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include"bg.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "game.h"
#include "score.h"
#include "effect.h"
#include "fade.h"
#include "input.h"
#include "pause.h"
#include "time.h"
#include "life.h"
#include "sound.h"

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;	//�Q�[���̏��
int g_nCounterGameState;											//��ԊǗ��̃J�E���^�[
bool g_bPause;															//�|�[�Y�����ǂ���

//===============================================================================
//�Q�[����ʏ���������
//===============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NORMAL;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
	g_bPause = false;

	//�w�i����������
	InitBG();
	//	�v���C���[��������������
	InitPlayer();
	//�e�̔��˂̏���������
	InitBullet();
	//�����̔��˂̏���������
	InitExplosion();
	//�X�R�A�̏���������
	InitScore();
	//�G�t�F�N�g�̏���������
	InitEffect();
	//�|�[�Y�̏���������
	InitPause();
	//�^�C���̏���������
	InitTime();
	//���C�t�̏���������
	InitLife();
	//�G�̏�������������
	InitEnemy();
	//�ォ�����
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE2, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE3, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE4, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE5, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE6, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE7, ENEMY_HEIGHT, 0.0f), 0,2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE8, ENEMY_HEIGHT, 0.0f), 0,2);

	//����
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE2, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE3, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE4, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE5, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE6, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE7, ENEMY_HEIGHT2, 0.0f), 1,-1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE8, ENEMY_HEIGHT2, 0.0f), 1,-1);

	//�O���
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE2, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE3, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE4, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE5, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE6, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE7, ENEMY_HEIGHT3, 0.0f), 2,1);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE8, ENEMY_HEIGHT3, 0.0f), 2,1);

	//�l���
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE2, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE3, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE4, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE5, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE6, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE7, ENEMY_HEIGHT4, 0.0f), 3,-2);
	SetEnemy(D3DXVECTOR3(ENEMY_WIDE8, ENEMY_HEIGHT4, 0.0f), 3,-2);

}

//===============================================================================
//�Q�[����ʏI������
//===============================================================================
void UninitGame(void)
{
	//�w�i�I������
	UninitBG();
	//�v���C���[�����I������
	UninitPlayer();
	//�e�̔��ˏ���
	UninitBullet();
	//�����̔��ˏ���
	UninitExplosion();
	//�X�R�A�̏I������
	UninitScore();
	//�G�t�F�N�g�̏I������
	UninitEffect();
	//�G�̏I������
	UninitEnemy();
	//�|�[�Y�̏I������
	UninitPause();
	//�^�C���̏I������
	UninitTime();
	//���C�t�̏I������
	UninitLife();
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

		//�w�i�X�V����
		UpdateBG();
		//�v���C���[�����X�V����
		UpdatePlayer();
		//�e�̔��ˏ���
		UpdateBullet();
		//�����̔��ˏ���
		UpdateExplosion();
		//�X�R�A�̍X�V����
		UpdateScore();
		//�G�t�F�N�g�̍X�V����
		UpdateEffect();
		//�G�̍X�V����
		UpdateEnemy();
		//�^�C���̍X�V����
		UpdateTime();
		//���C�t�̍X�V����
		UpdateLife();
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
	//�w�i�`�揈��
	DrawBG();
	//�v���C���[�̕`�揈��
	DrawPlayer();
	//�e�̔��ˏ���
	DrawBullet();
	//�����̔��ˏ���
	DrawExplosion();
	//�X�R�A�̕`�揈��
	DrawScore();
	//�G�t�F�N�g�̕`�揈��
	DrawEffect();
	//�G�̕`�揈��
	DrawEnemy();
	//�^�C���̕`�揈��
	DrawTime();
	//���C�t�̕`�揈��
	DrawLife();

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
//�|�[�Y��Ԃ̎擾
//===============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}