//===============================================================================
//
// �v���C���[�̐������� [player.h]
// Author : �����ʉ�
//
//===============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//===============================================================================
//�\���̂̒�`
//===============================================================================
typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//�v���C���[�̒ʏ���
	PLAYERSTATE_SIZEUP,				//�L�m�R��������̏��
	PLAYERSTATE_SIZEDOWN,		//�s�[�}����������̏��
	PLAYERSTATE_MAX
} PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posOld;	//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	bool bDisp;						//�\�����邩���Ȃ���
	bool bJump;						//�W�����v���Ă��邩�ǂ���
	bool bUse;						//�g�p���Ă��邩�ǂ���
	bool bLand;						//�����蔻�肪�g�p����Ă��邩�ǂ���
	int nCntAnim;					//�A�j���[�V�����J�E���^�[
	int nPatternAnim;			//�A�j���[�V�����̃p�^�[����
	int DirectionMove;
	int nWidth;						//��
	int nHeight;						//	����
	PLAYERSTATE state;		//�v���C���[�̏��
} Player;

//===============================================================================
//�v���g�^�C�v�錾
//===============================================================================
void InitPlayer(void);								//�v���C���[��������������
void UninitPlayer(void);							//�v���C���[�����I������
void UpdatePlayer(void);							//�v���C���[�����X�V����
void DrawPlayer(void);							//�v���C���[�̕`�揈��
Player * GetPlayer(void);

#endif