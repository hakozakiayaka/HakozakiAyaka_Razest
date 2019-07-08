//=========================================================================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �L�n�@���u�@���@���R
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "game.h"			//�Q�[��
#include "player.h"			//�v���C���[
#include "fade.h"			//�t�F�[�h	
#include "input.h"			//�L�[�{�[�h����
#include "pause.h"			//�|�[�Y
#include "explosion.h"		//����
#include "meshbg.h"			//���b�V���V�����_�[
#include "meshfield.h"		//���b�V���t�B�[���h
#include "wall.h"			//��
#include "shadow.h"			//�e
#include "object.h"			//�I�u�W�F�N�g
#include "billboord.h"		//�r���{�[�h
#include "bullet.h"			//�o���b�g
#include "effect.h"			//�G�t�F�N�g
#include "light.h"			//���C�g
#include "camera.h"			//�J����
#include "sound.h"			//�T�E���h
#include "time.h"			//�^�C��
#include "camera.h"			//�J����
#include "player2.h"		//�v���C���[�Q
#include "frame.h"			//�g
#include "length.h"
#include "item.h"
#include "possession.h"
#include "wall.h"
#include "objectnot.h"
#include "enemy.h"			//�S

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
GAMESTATE g_gameState;			//�Q�[�����
int g_nCounterGameState;		//��ԃJ�E���^�[
bool g_bPause;					//�|�[�Y
bool g_bMenu;					//���j���[

//=========================================================================================================================
// �w�i����������
//=========================================================================================================================
void InitGame(void)
{
	//�J�����̂ۂ��񂽁@
	Camera *pCamera = GetCamera();
	StopSound();
	g_gameState = GAMESTATE_NONE;	//�Q�[�����
	g_nCounterGameState = 0;

	// �|���S���̏���������
	//InitPolygon();

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	//�w�i�̏���������
	InitMeshBg();

	//���b�V���t�B�[���h�̏���������
	InitMeshField();

	//�ǂ̏���������
	InitWall();

	//�e�̏���������
	InitShadow();

	//���f���̏���������
	InitPlayer();

	//�v���C���[�Q�̏�����
	InitPlayer2();

	//�S�̏���������
	InitEnemy();

	//�I�u�W�F�N�g�̏���������
	InitObject();

	InitObjectNot();

	//�r���{�[�h�̏���������
	InitBillBoord();

	//�e�̏���������
	InitBullet();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�����̏���������
	InitExplosion();

	InitTime();

	InitLength();

	//��ʂɏo���摜�̏���������
	InitFrame();

	//�|�[�Y�̏���������
	InitPause();

#if 1
	//================================================================================
	//�����蔻��̂���I�u�W�F�N�g
	//================================================================================
	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//400
	SetObject(D3DXVECTOR3(1000.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//600
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�M��(��)
	SetObject(D3DXVECTOR3(1200.0f, 0.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�X��
	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�_���{�[��
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	//�g���b�N
	SetObject(D3DXVECTOR3(4200.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//��
	SetObject(D3DXVECTOR3(0.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//���̋@
	SetObject(D3DXVECTOR3(1400.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�S�~��
	SetObject(D3DXVECTOR3(1220.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�����
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(500.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------5---------------

	SetObject(D3DXVECTOR3(900.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//------------10---------------

	//200
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------15---------------

	//200
	SetObject(D3DXVECTOR3(-100.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------20---------------

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(-100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------25---------------

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------30---------------

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------35---------------

	//200
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(-100.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------40---------------

	//200
	SetObject(D3DXVECTOR3(2300.0f, 0.0f, -2300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -4100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -4100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------45---------------

	//200
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------50---------------

	//200
	SetObject(D3DXVECTOR3(2300.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------55---------------

	//200
	SetObject(D3DXVECTOR3(2700.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------60---------------

	//200
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -4100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------65---------------

	//200
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------69---------------


	//------------73---------------

	//400

	//------------81---------------

	//200
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -2300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------85---------------

	//200
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------90---------------

	//200
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------95---------------

	//200
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, -1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -1300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------100---------------


	//200
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------105---------------

	//200
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------107---------------

	//400
	SetObject(D3DXVECTOR3(200.0f, 0.0f, -1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.0f, -2600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4000.0f, 0.0f, -2600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3800.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3000.0f, 0.0f, -1800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2600.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2600.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1800.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1800.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	//600
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�M��(��)
	SetObject(D3DXVECTOR3(1200.0f, 0.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1600.0f, 0.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1600.0f, 0.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�X��
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(400.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�X��
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(400.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	//�_���{�[��
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1350.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, -0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1450.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, -0.0f, 0.0f));

	SetObject(D3DXVECTOR3(100.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.1f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(550.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.4f, 0.0f));
	SetObject(D3DXVECTOR3(750.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.3f, 0.0f));
	SetObject(D3DXVECTOR3(950.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.6f, 0.0f));
	SetObject(D3DXVECTOR3(1300.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1950.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2150.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.1f, -3300.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -3300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.1f, -3250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.1f, -3200.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1800.0f, 0.1f, -3300.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -3750.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -3800.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -3750.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(300.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -2750.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2750.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -1150.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -1150.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -200.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 1.2f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));

	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 1.2f, 0.0f));
	SetObject(D3DXVECTOR3(2550.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.4f, 0.0f));
	SetObject(D3DXVECTOR3(2550.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));

	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(2900.0f, 0.1f, -1500.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.1f, -1450.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2950.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2950.0f, 0.1f, -1450.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2950.0f, 0.1f, -1500.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	//
	SetObject(D3DXVECTOR3(4100.0f, 0.1f, -3900.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(4150.0f, 0.1f, -3900.0f), D3DXVECTOR3(0.0f, 0.4f, 0.0f));
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -4100.0f), D3DXVECTOR3(0.0f, 1.2f, 0.0f));

	SetObject(D3DXVECTOR3(900.0f, 0.1f, -4100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));//�P�̔z�u
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));//�P�̔z�u
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));//�P�̔z�u
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(750.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(300.0f, 0.1f, -1100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -1100.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(250.0f, 0.1f, -1150.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -1450.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(3350.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3400.0f, 0.1f, -1250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3200.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3250.0f, 0.1f, -1400.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2200.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(2200.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -4100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2250.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));
	SetObject(D3DXVECTOR3(2050.0f, 0.1f, -3650.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));//�_���{�[����Ŏg��
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));//�d�˒u����
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -2600.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));//
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));//
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -2600.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));//

	SetObject(D3DXVECTOR3(2500.0f, 50.0f, -300.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2520.0f, 20.0f, -300.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 80.0f, -300.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 20.0f, -340.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 50.1f, -340.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	//�g���b�N
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));//�d�˒u����

																				   //��(��)
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(250.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(650.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(750.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(950.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1950.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2650.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2850.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3050.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(3150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3250.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3450.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3650.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(650.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(750.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2150.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(950.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1950.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2650.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2850.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3050.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(3150.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3450.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3650.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	SetObject(D3DXVECTOR3(1550.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//-----------------------------------------------------�������ꂠ
	SetObject(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	SetObject(D3DXVECTOR3(2200.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2600.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//--------------------
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�؂����˂������イ
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//-------------------

																				 //���̋@
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -900.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -800.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1200.0f, 0.1f, -3250.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(50.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.1f, -2810.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -2810.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(200.0f, 0.1f, -2810.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -1500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObject(D3DXVECTOR3(4000.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//�S�~��
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObject(D3DXVECTOR3(2220.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3020.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(330.0f, 0.1f, -3120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1520.0f, 0.1f, -3120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4020.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1820.0f, 0.1f, -3620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(320.0f, 0.1f, -4120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3520.0f, 0.1f, -1120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3520.0f, 0.1f, 80.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2220.0f, 0.1f, -620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//================================================================================
	//�����蔻��̂Ȃ��I�u�W�F�N�g
	//================================================================================
	//
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�M��
	SetObjectNot(D3DXVECTOR3(1600.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	//�X��
	SetObjectNot(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	//��
	SetObjectNot(D3DXVECTOR3(0.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	//����
	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	//�ԓ�
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -975.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -1625.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2275.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2925.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));// -3575.0f


	SetObjectNot(D3DXVECTOR3(325.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(975.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1625.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2275.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2925.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3700.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//����

	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -1325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -3620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2025.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2375.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(325.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(780.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(780.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2020.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2675.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3700.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//�M��
	SetObjectNot(D3DXVECTOR3(1200.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1600.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1200.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	//�X��
	SetObjectNot(D3DXVECTOR3(100.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3300.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3600.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3900.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	//�X��
	SetObjectNot(D3DXVECTOR3(100.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3300.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3600.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3900.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	//��
	SetObjectNot(D3DXVECTOR3(150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(250.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1750.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(650.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(750.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(950.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1950.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2350.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2650.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2850.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3050.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(3150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3250.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3450.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3650.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3950.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(250.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1750.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(650.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(750.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2150.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(950.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1950.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1150.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2350.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2650.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2850.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3050.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(3150.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3250.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3450.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3650.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3950.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//-----------------------------------------------------�������ꂠ
	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2200.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2300.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2400.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2500.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2600.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2500.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//--------------------
	SetObjectNot(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�؂����˂������イ
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//-------------------

																					//����
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));


	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2250.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2350.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2550.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2250.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2350.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2550.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
#endif

	//�ǂ̔z�u
	//��
	SetWall(D3DXVECTOR3(2000, 0, 250), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f));
	//�E
	SetWall(D3DXVECTOR3(4250, 0, -2000), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f));
	//��
	SetWall(D3DXVECTOR3(2000, 0, -4250), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f));
	//��
	SetWall(D3DXVECTOR3(-250, 0, -2000), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f));

	//�A�C�e���̐ݒu
	//SetItem(D3DXVECTOR3(-1000, 70, -300), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEM_GASOLINE, 0);

	g_gameState = GAMESTATE_NORMAL;		//�ʏ��Ԃɐݒ�

	//�|�[�Y���g�p���ĂȂ���Ԃɂ���
	g_bPause = false;
	
	g_bMenu = false;
}

//=========================================================================================================================
// �w�i�I������
//=========================================================================================================================
void UninitGame(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	//�����̏I������
	UninitExplosion();

	// �|���S���̏I������
	//UninitPolygon();

	//�w�i�̏I������
	UninitMeshBg();

	//���b�V���t�B�[���h�̏I������
	UninitMeshField();

	//�ǂ̏I������
	UninitWall();

	//���f���̏I������
	UninitPlayer();

	//�S�̏I������
	UninitEnemy();

	//�v���C���[�Q�̏�����
	UninitPlayer2();

	//�I�u�W�F�N�g�̏I������
	UninitObject();

	UninitObjectNot();

	//�e�̏I������
	UninitShadow();

	//�e�̏I������
	UninitBullet();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�r���{�[�h�̏I������
	UninitBillBoord();

	//�����̏I������
	UninitExplosion();

	//���o�̏I������
	UninitLength();

	//���Ԃ̏I������
	UninitTime();

	//��ʂɏo���摜�̏I������
	UninitFrame();

	//�|�[�Y�̏I������
	UninitPause();
}
//=========================================================================================================================
// �w�i�X�V����
//=========================================================================================================================
void UpdateGame(void)
{
	//�|�[�Y�̏���
	if (GetKeyboardTrigger(DIK_P) == true)
	{//P�L�[�������ꂽ��
		g_bPause = g_bPause ? false : true;

		if (g_bPause == false)
		{//�J����
			PlaySound(SOUND_LABEL_SE_OPEN000);
		}
		else
		{//���艹
			PlaySound(SOUND_LABEL_SE_DOWN000);
		}
	}
	if (g_bPause == false && g_bMenu == false)
	{//���i��false�ɂ��Ă���
		/*if (GetKeyboardTrigger(DIK_H) == true)
		{
			SetFade(MODE_RESULT);
		}*/
		//�J�����̍X�V����
		UpdateCamera();

		//���C�g�̍X�V����
		UpdateLight();

		//�����̍X�V����
		UpdateExplosion();

		// �|���S���̍X�V����
		//UpdatePolygon();

		//�w�i�̍X�V����
		UpdateMeshBg();

		//���b�V���t�B�[���h�̍X�V����
		UpdateMeshField();

		//�ǂ̍X�V����
		UpdateWall();

		//���f���̍X�V����
		UpdatePlayer();

		//�v���C���[�Q�̏�����
		UpdatePlayer2();

		//�S�̏���������
		UpdateEnemy();

		//�I�u�W�F�N�g�̍X�V����
		UpdateObject();

		//�����蔻��̂Ȃ��I�u�W�F�N�g�̍X�V����
		UpdateObjectNot();

		//�e�̍X�V����
		UpdateShadow();

		//�r���{�[�h�̍X�V����
		UpdateBillBoord();

		//�e�̍X�V����
		UpdateBullet();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�����̍X�V����
		UpdateExplosion();

		//�^�C���̍X�V����
		UpdateTime();
		
		//���o�̍X�V����
		UpdateLength();
	
		//��ʂɏo���摜�̍X�V����
		UpdateFrame();
	}
	else if (g_bPause == true)
	{//true�ɂȂ�����|�[�Y���X�V����
		//�|�[�Y�̍X�V����
		UpdatePause();
	}
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_CLEAR:
		
	case GAMESTATE_OVER:
		g_nCounterGameState++;

		if (g_nCounterGameState <= 60)
		{
			// = GAMESTATE_NONE;
			//��ʁi���[�h�j�̐ݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//=========================================================================================================================
// �w�i�`�揈��
//=========================================================================================================================
void DrawGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//��ʂ̃N���A
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(210, 210, 255, 0), 1.0f, 0);

	//�r���[�|�[�g�̎擾
	D3DVIEWPORT9 ViewPortDef;
	pDevice->GetViewport(&ViewPortDef);

	for (int nCount = 0; nCount < 4; nCount++)
	{
		// �J�����̐ݒ�
		SetCamera(CAMERA_TYPE_GAME, nCount);

		//�w�i�̕`�揈��
		DrawMeshBg();

		//���b�V���t�B�[���h�̕`�揈��
		DrawMeshField();

		//�ǂ̕`�揈��
		DrawWall();

		//���f���̕`�揈��
		DrawPlayer();
		
		//�v���C���[�Q�̕`�揈��
		DrawPlayer2();

		if (nCount != 3)
		{
			//�S�̕`�揈��
			DrawEnemy();
		}

		//�I�u�W�F�N�g�̕`�揈��
		DrawObject();

		//�����蔻��̂Ȃ��I�u�W�F�N�g�̕`�揈��
		DrawObjectNot();

		//�e�̕`�揈��
		DrawShadow();

		//�r���{�[�h�̕`�揈��
		DrawBillBoord();

		//�e�̕`�揈��
		DrawBullet();

		//�G�t�F�N�g�̕`�揈��
		DrawEffect();

		//�����̕`�揈��
		DrawExplosion();

		//��ʂɏo���摜�̕`�揈��
		DrawFrame();

		DrawLength();
	}
	//�߂�
	pDevice->SetViewport(&ViewPortDef);


	if (g_bPause == true)
	{//�|�[�Y��true��������
		//�|�[�Y�̕`�揈��
		DrawPause();
	}
}
//=========================================================================================================================
// �Q�[����Ԃ̐ݒ�
//=========================================================================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
}
//=========================================================================================================================
// �Q�[����Ԃ̐ݒ�
//=========================================================================================================================
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}
//=========================================================================================================================
// �Q�[����Ԃ̐ݒ�
//=========================================================================================================================
void SetMenuState(bool bMenu)
{
	g_bMenu = bMenu;
}
//=========================================================================================================================
// �Q�[����Ԃ̎擾
//=========================================================================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}