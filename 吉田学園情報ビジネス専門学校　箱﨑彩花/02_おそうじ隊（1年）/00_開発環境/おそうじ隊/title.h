#pragma once
//===============================================================================
//
// �^�C�g����� [title.h]
// Author : �����ʉ�
//
//===============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//===============================================================================
//�\���̂̒�`
//===============================================================================
typedef enum
{
	TITLESTATE_NONE = 0,
	TITLESTATE_NORMAL,
	TITLESTATE_RANKING,
	TITLESTATE_MAX
} TitleState;

typedef struct
{
	TitleState state;			//�^�C�g���̏��
	D3DXVECTOR3 pos;	//�ʒu
	int nCnt;
	float fFlash;
	D3DXCOLOR col;
	bool bUse;					//�g�p���Ă��邩�ǂ���
} Title;

//===============================================================================
//�v���g�^�C�v�錾
//===============================================================================
void InitTitle(void);			//�^�C�g����ʏ���������
void UninitTitle(void);		//�^�C�g����ʏI������
void UpdateTitle(void);	//�^�C�g����ʍX�V����
void DrawTitle(void);		//�^�C�g����ʕ`�揈��

#endif