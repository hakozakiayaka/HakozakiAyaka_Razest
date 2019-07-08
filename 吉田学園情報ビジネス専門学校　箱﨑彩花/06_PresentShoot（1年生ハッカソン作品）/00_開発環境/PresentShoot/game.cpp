//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "pause.h"
#include "BG.h"
#include "StarBG.h"
#include "player.h"
#include "present.h"
#include "chimney.h"
#include "score.h"
#include "enemy.h"
#include "life.h"
#include "house.h"
#include "effect.h"
#include "sound.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
GAMESTATE g_gameState = GAMESTATE_NONE;		//�Q�[���̏��
int g_nCounterGameState;					//��ԊǗ��J�E���^�[
int g_nCounterGame;							//�G�l�~�[�o���̃J�E���^�[
bool g_bPause;								//�|�[�Y���g�p���Ă��邩�ǂ���

//=============================================================================
// ����������
//=============================================================================
void InitGame(void)
{
	//�ϐ��̏�����
	g_gameState = GAMESTATE_NORMAL;		//�Q�[���̏��
	g_nCounterGameState = 0;			//��ԊǗ��J�E���^�[
	g_nCounterGame = 0;					//�J�E���^�[
	g_bPause = false;					//�|�[�Y���ǂ���

	//�֐��Ăяo��
	InitPause();					//�|�[�Y����

	//�w�i�̃Z�b�g
	SetBG(6);

	InitStarBG();					//����
	InitPresent();					//�v���[���g
	InitEnemy();					//�G
	InitPlayer();					//�v���C���[
	InitChimney();					//����
	InitHouse();					//�n�E�X
	InitEffect();					//�G�t�F�N�g
	InitScore();					//�X�R�A
	InitLife();						//���C�t

	//�G�̃Z�b�g
	SetEnemy(D3DXVECTOR3(900, 300, 0.0f));
	SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, 200, 0.0f));
	SetEnemy(D3DXVECTOR3(2000, 300, 0.0f));
	SetEnemy(D3DXVECTOR3(2500, 150, 0.0f));
	SetEnemy(D3DXVECTOR3(3500, 200, 0.0f));
	SetEnemy(D3DXVECTOR3(4300, 150, 0.0f));
	SetEnemy(D3DXVECTOR3(5000, 100, 0.0f));
	SetEnemy(D3DXVECTOR3(5800, 300, 0.0f));
	SetEnemy(D3DXVECTOR3(6500, 150, 0.0f));
	SetEnemy(D3DXVECTOR3(7100, 200, 0.0f));
	SetEnemy(D3DXVECTOR3(8000, 300, 0.0f));

	//���˂̃Z�b�g
	SetChimney(D3DXVECTOR3(540.0f, 430.0f, 0.0f), 40, 50);	//1
	SetChimney(D3DXVECTOR3(790.0f, 475.0f, 0.0f), 40, 60);	//2
	SetChimney(D3DXVECTOR3(1100.0f, 480.0f, 0.0f), 40, 90);	//3
	SetChimney(D3DXVECTOR3(1390.0f, 540.0f, 0.0f), 40, 70);	//4
	SetChimney(D3DXVECTOR3(1790.0f, 475.0f, 0.0f), 40, 60);	//5
	SetChimney(D3DXVECTOR3(2100.0f, 480.0f, 0.0f), 40, 90);	//6
	SetChimney(D3DXVECTOR3(2810.0f, 480.0f, 0.0f), 40, 90);	//8
	SetChimney(D3DXVECTOR3(3090.0f, 540.0f, 0.0f), 40, 70);	//9
	SetChimney(D3DXVECTOR3(3450.0f, 430.0f, 0.0f), 40, 50);	//10
	SetChimney(D3DXVECTOR3(4030.0f, 540.0f, 0.0f), 40, 70);	//13
	SetChimney(D3DXVECTOR3(4380.0f, 475.0f, 0.0f), 40, 60);	//14
	SetChimney(D3DXVECTOR3(4840.0f, 480.0f, 0.0f), 40, 90);	//15
	SetChimney(D3DXVECTOR3(5485.0f, 430.0f, 0.0f), 40, 50);	//18
	SetChimney(D3DXVECTOR3(5785.0f, 475.0f, 0.0f), 40, 60);	//19
	SetChimney(D3DXVECTOR3(6095.0f, 480.0f, 0.0f), 40, 90);	//20
	SetChimney(D3DXVECTOR3(6535.0f, 430.0f, 0.0f), 40, 50);	//21
	SetChimney(D3DXVECTOR3(7045.0f, 540.0f, 0.0f), 40, 70);	//23
	SetChimney(D3DXVECTOR3(7345.0f, 475.0f, 0.0f), 40, 60);	//24
	SetChimney(D3DXVECTOR3(8035.0f, 480.0f, 0.0f), 40, 90);	//27
	SetChimney(D3DXVECTOR3(8325.0f, 475.0f, 0.0f), 40, 60);	//28

	//�Ƃ̃Z�b�g
	SetHouse(1, D3DXVECTOR3(500.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 350);		//1��
	SetHouse(2, D3DXVECTOR3(750.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//2��
	SetHouse(0, D3DXVECTOR3(1050.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//3��
	SetHouse(3, D3DXVECTOR3(1350.0f, 640.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 200);		//4��
	SetHouse(2, D3DXVECTOR3(1750.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//5��
	SetHouse(0, D3DXVECTOR3(2050.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//6��
	SetHouse(4, D3DXVECTOR3(2355.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//7�� ��
	SetHouse(0, D3DXVECTOR3(2760.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//8�� 
	SetHouse(3, D3DXVECTOR3(3050.0f, 640.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//9��
	SetHouse(1, D3DXVECTOR3(3410.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 350);		//10��
	SetHouse(4, D3DXVECTOR3(3665.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//11�ځ@��
	SetHouse(4, D3DXVECTOR3(3735.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//12�ځ@��
	SetHouse(3, D3DXVECTOR3(3990.0f, 640.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 200);		//13��
	SetHouse(2, D3DXVECTOR3(4340.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//14��
	SetHouse(0, D3DXVECTOR3(4790.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//15��
	SetHouse(4, D3DXVECTOR3(5054.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//16�� ��
	SetHouse(4, D3DXVECTOR3(5165.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//17�� ��
	SetHouse(1, D3DXVECTOR3(5445.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 350);		//18�� 
	SetHouse(2, D3DXVECTOR3(5745.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//19��
	SetHouse(0, D3DXVECTOR3(6045.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//20�� 
	SetHouse(1, D3DXVECTOR3(6495.0f, 630.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 350);		//21��
	SetHouse(4, D3DXVECTOR3(6725.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//22�� ��
	SetHouse(3, D3DXVECTOR3(7005.0f, 640.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 200);		//23��
	SetHouse(2, D3DXVECTOR3(7305.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//24��
	SetHouse(4, D3DXVECTOR3(7585.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//25�� ��
	SetHouse(4, D3DXVECTOR3(7705.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 110, 250);		//26�� ��
	SetHouse(0, D3DXVECTOR3(7985.0f, 620.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 300);		//27��
	SetHouse(2, D3DXVECTOR3(8285.0f, 675.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 350);		//28��
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	//�֐��Ăяo��
	UninitPause();		//�|�[�Y����
	UninitStarBG();		//����
	UninitPresent();	//�v���[���g
	UninitEnemy();		//�G
	UninitPlayer();		//�v���C���[
	UninitHouse();		//��
	UninitChimney();	//����
	UninitEffect();		//�G�t�F�N�g
	UninitScore();		//�X�R�A
	UninitLife();		//���C�t
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true)
	{//�|�[�YON/OFF
		PlaySound(SOUND_LABEL_SE_PAUSE);
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		UpdateStarBG();		//����
		UpdatePresent();	//�v���[���g
		UpdateEnemy();		//�G
		UpdatePlayer();		//�v���C���[
		UpdateHouse();		//��
		UpdateChimney();	//����
		UpdateEffect();		//�G�t�F�N�g
		UpdateScore();		//�X�R�A
		UpdateLife();		//���C�t
	}
	else
	{
		UpdatePause();					//�|�[�Y����
	}

	//�t�F�[�h�����擾����
	FADE fade;
	fade = GetFade();
	
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;

	case GAMESTATE_END_CLIA:
		g_nCounterGameState++;	//��ԊǗ��J�E���^�[�����Z

		if (g_nCounterGameState >= 60)
		{
			g_gameState = GAMESTATE_NONE;

			//�t�F�[�h���[�h�ݒ�
			if (fade != FADE_OUT)
			{
				SetFade(MODE_RESULT);
			}
		}
		break;

	case GAMESTATE_END_OVER:
		g_nCounterGameState++;	//��ԊǗ��J�E���^�[�����Z

		if (g_nCounterGameState > 60)
		{
			g_gameState = GAMESTATE_NONE;

			//�t�F�[�h���[�h�ݒ�
			if (fade != FADE_OUT)
			{
				SetFade(MODE_RESULTOVER);
			}
		}
		break;
	}

	if (GetKeyboardTrigger(DIK_F1) == true)
	{
		g_gameState = GAMESTATE_END_CLIA;
	}
	if (GetKeyboardTrigger(DIK_F2) == true)
	{
		g_gameState = GAMESTATE_END_OVER;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	DrawStarBG();		//����
	DrawPresent();		//�v���[���g
	DrawEnemy();		//�G
	DrawPlayer();		//�v���C���[
	DrawChimney();		//����
	DrawHouse();		//��
	DrawEffect();		//�G�t�F�N�g
	DrawScore();		//�X�R�A
	DrawLife();			//���C�t

	if (g_bPause == true)
	{
		DrawPause();	//�|�[�Y����
	}
}

//=============================================================================
// �Q�[����Ԃ̐ݒ�
//=============================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//=============================================================================
// �Q�[����Ԃ̎擾
//=============================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=============================================================================
// �|�[�Y��Ԃ̎擾
//=============================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}