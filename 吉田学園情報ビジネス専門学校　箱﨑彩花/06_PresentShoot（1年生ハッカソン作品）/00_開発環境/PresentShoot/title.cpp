//=============================================================================
//
// �^�C�g����� [title.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "start.h"
#include "fade.h"
#include "BG.h"
#include "flontpolygon.h"
#include "StarBG.h"
#include "titleplayer.h"
#include "effect.h"
#include "StarBG.h"

//=============================================================================
// �}�N����`
//=============================================================================


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
int g_nCntTime;												//�G�t�F�N�g�̃J�E���^�[
int g_nCntTimeTitle;										//�^�C�g�����Ԃ̃J�E���^�[

//=============================================================================
// �^�C�g������������
//=============================================================================
void InitTitle(void)
{
	//�ϐ��錾
	g_nCntTime = 0;
	g_nCntTimeTitle = 0;

	//�֐��Ăяo��
	InitStarBG();		//����
	InitStart();		//�X�^�[�g�{�^��
	InitEffect();		//�G�t�F�N�g
	InitTitlePlayer();	//�^�C�g���v���C���[

	//�w�i�̃Z�b�g
	SetBG(6);			

	//�^�C�g�����S�̃Z�b�g
	SetFlontPolygon(0, D3DXVECTOR3(640.0f, 200.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 800.0f, 300.0f);

	//�{�^���̃Z�b�g
	SetEnter(D3DXVECTOR3(630.0f, 650.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitTitle(void)
{
	//�֐��Ăяo��
	UninitStarBG();			//����
	UninitStart();			//�X�^�[�g�{�^��
	UninitEffect();			//�G�t�F�N�g
	UninitTitlePlayer();	//�^�C�g���v���C���[
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateTitle(void)
{
	//���Ԃ����Z����
	g_nCntTime++;
	g_nCntTimeTitle++;

	//�t�F�[�h�����擾����
	FADE fade;
	fade = GetFade();

	//�֐��Ăяo��
	UpdateStarBG();			//����
	UpdateStart();			//�X�^�[�g�{�^��
	UpdateEffect();			//�G�t�F�N�g
	UpdateTitlePlayer();	//�^�C�g���v���C���[
	
	//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//�X�^�[�g�{�^���̐ݒ�
			SetPush(STARTSTRACT_ENTER);

			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_TUTORIAL);
			PlaySound(SOUND_LABEL_SE_ENTER);	//���艹
		}
	}
	if (g_nCntTimeTitle == INTERVAL_TIME)
	{
		//�t�F�[�h���[�h�ݒ�
		SetFade(MODE_TUTORIAL);
	}
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawTitle(void)
{
	//�֐��Ăяo��
	DrawStarBG();		//����
	DrawStart();		//�X�^�[�g�{�^��
	DrawEffect();		//�G�t�F�N�g
	DrawTitlePlayer();	//�^�C�g���v���C���[
}