//===============================================================================
//
// �Q�[����� [game.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "BG.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "fade.h"
#include "input.h"
#include "billboard.h"
#include "light.h"
#include "camera.h"
#include "meshCylinder.h"
#include "meshField.h"
#include "meshWall.h"
#include "model.h"
#include "shadow.h"
#include "result.h"
#include "score.h"
#include "time.h"
#include "enemy.h"
#include "effect.h"
#include "life.h"
#include "Pause.h"

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
GAMESTATE g_gameState;	//�Q�[���̏��
int g_nCounterGameState;											//��ԊǗ��̃J�E���^�[
bool g_bPause;															//�|�[�Y�����ǂ���

//===============================================================================
//�Q�[����ʏ���������
//===============================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NONE;	//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
	g_bPause = false;

	//�J�����̏���������
	InitCamera();
	//���b�V���t�B�[���h�̏���������
	InitMeshField();
	//���b�V���E�H�[���̏���������
	InitMeshWall();
	//���b�V���V�����_�[�̏���������
	//InitMeshCylinder();
	//�e�̏���������
	InitShadow();
	//�r���{�[�h�̏���������
	//InitBillboard();
	//�G�l�~�[�̏���������
	InitEnemy();
	SetEnemy(D3DXVECTOR3(300.0f, 10.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(450.0f, 10.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(700.0f, 10.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(500.0f, 10.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);

	//���C�g�̏���������
	InitLight();
	//�e�̏���������
	InitBullet();
	//�����̏���������
	InitExplosion();
	//	�v���C���[��������������
	InitPlayer();
	//���f���̏���������
	InitModel();
	SetModel(D3DXVECTOR3(50.0f, 0.0f, -10.0f), D3DXVECTOR3 (0.0f, 0.0f, 0.0f), 0, 60.0f, 20.0f);
	SetModel(D3DXVECTOR3(300.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 30.0f, 30.0f);
	SetModel(D3DXVECTOR3(5.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, -90.0f, 0.0f), 2, 30.0f, 30.0f);

	//�X�R�A�̏���������
	InitScore();
	//�^�C���̏���������
	InitTime();
	//�G�t�F�N�g�̏�����
	InitEffect();
	//���C�t�̏���������
	InitLife();
	//�|�[�Y�̏���������
	InitPausemenu();
}

//===============================================================================
//�Q�[����ʏI������
//===============================================================================
void UninitGame(void)
{
	//�J�����̏I������
	UninitCamera();
	//���b�V���t�B�[���h�̏I������
	UninitMeshField();
	//���b�V���E�H�[���̏I������
	UninitMeshWall();
	//���b�V���V�����_�[�̏I������
	//UninitMeshCylinder();
	//�e�̏I������
	UninitShadow();
	//�r���{�[�h�̏I������
	//UninitBillboard();
	//�G�l�~�[�̏I������
	UninitEnemy();
	//���C�g�̏I������
	UninitLight();
	//�e�̏I������
	UninitBullet();
	//�����̏I������
	UninitExplosion();
	//�v���C���[�����I������
	UninitPlayer();
	//���f���̏I������
	UninitModel();
	//�X�R�A�̏I������
	UninitScore();
	//�^�C���̏I������
	UninitTime();
	//�G�t�F�N�g�̏I������
	UninitEffect();
	//���C�t�̏I������
	UninitLife();
	//�|�[�Y�̏I������
	UninitPausemenu();
}

//===============================================================================
//�Q�[����ʍX�V����
//===============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{	//	�|�[�Y�̏���
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

		////�t�F�[�h�̎擾
		//FADE g_fade = GetFade();

		////����L�[�������ꂽ���ǂ���
		//if (GetKeyboardTrigger(DIK_RETURN) == true)
		//{
		//	if (g_fade != FADE_OUT)
		//	{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
		//		//���[�h�ݒ�
		//		SetFade(MODE_RESULT);
		//	}
		//}

			//�J�����̍X�V����
		UpdateCamera();
		//���b�V���t�B�[���h�̍X�V����
		UpdateMeshField();
		//���b�V���E�H�[���̍X�V����
		UpdateMeshWall();
		//���b�V���V�����_�[�̍X�V����
		//UpdateMeshCylinder();
		//�e�̍X�V����
		UpdateShadow();
		//�r���{�[�h�̍X�V����
		//UpdateBillboard();
		//�G�l�~�[�̍X�V����
		UpdateEnemy();
		//���C�g�̍X�V����
		UpdateLight();
		//�e�̍X�V����
		UpdateBullet();
		//�����̍X�V����
		UpdateExplosion();
		//�v���C���[�����X�V����
		UpdatePlayer();
		//���f���̍X�V����
		UpdateModel();
		//�X�R�A�̍X�V����
		UpdateScore();
		//�^�C���̍X�V����
		UpdateTime();
		//�G�t�F�N�g�̍X�V����
		UpdateEffect();
		//���C�t�̍X�V����
		UpdateLife();
	}
	else
	{
		//�|�[�Y�̍X�V����
		UpdatePausemenu();
	}
}

//===============================================================================
//�Q�[����ʕ`�揈��
//===============================================================================
void DrawGame(void)
{
	//�J�����̐ݒ�
	SetCamera();
	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();
	//���b�V���E�H�[���̕`�揈��
	DrawMeshWall();
	//���b�V���V�����_�[�̕`�揈��
	//DrawMeshCylinder();
	//�e�̕`�揈��
	DrawShadow();
	//�r���{�[�h�̕`�揈��
	//DrawBillboard();
	//�G�l�~�[�̕`�揈��
	DrawEnemy();
	//�e�̕`�揈��
	DrawBullet();
	//�����̕`�揈��
	DrawExplosion();
	//�v���C���[�̕`�揈��
	DrawPlayer();
	//���f���̕`�揈��
	DrawModel();
	//�X�R�A�̕`�揈��
	DrawScore();
	//�^�C���̕`�揈��
	DrawTime();
	//�G�t�F�N�g�̕`�揈��
	DrawEffect();
	//���C�t�̕`�揈��
	DrawLife();

	if (g_bPause == true)
	{
		//�|�[�Y�̕`�揈��
		DrawPausemenu();
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