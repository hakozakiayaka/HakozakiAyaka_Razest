#pragma once
//===============================================================================
//
// ���S�ݒ� [logo.h]
// Author : �����ʉ�
//
//===============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"

//===============================================================================
//�\���̂̒�`
//===============================================================================
typedef enum
{
	LOGOSTATE_NONE = 0,
	LOGOSTATE_LOGO,			//�^�C�g���A�N���A�A�Q�[���I�[�o�[�̃��S
	LOGOSTATE_ENTER,				//�v���X�G���^�[
	LOGOSTATE_RANKING,			//�����L���O�̃��S
	LOGOSTATE_MAX
} LogoState;

typedef struct
{
	D3DXVECTOR3 pos;
	int nTexType;
	LogoState state;
	bool bUse;
} Logo;

//===============================================================================
//�v���g�^�C�v�錾
//===============================================================================
void InitLogo(void);			//���S����������
void UninitLogo(void);		//���S��ʏI������
void UpdateLogo(void);	//���S��ʍX�V����
void DrawLogo(void);		//���S��ʕ`�揈��
void SetLogo(D3DXVECTOR3 pos, int nTexType, LogoState state);		//���S��ݒ�
#endif