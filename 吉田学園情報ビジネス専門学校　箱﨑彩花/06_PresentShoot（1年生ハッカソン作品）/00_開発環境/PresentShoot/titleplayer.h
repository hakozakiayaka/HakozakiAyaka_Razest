//=============================================================================
//
// �v���C���[���� [titleplayrt.h]
// Author : �������D
//
//=============================================================================
#ifndef _TITLEPLAYER_H_
#define _TITLEPLAYER_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TITLEPLAYERSIZE_X	(160)
#define TITLEPLAYERSIZE_Y	(80)
#define POSCENTER_X		(TITLEPLAYERSIZE_X / 2)
#define POSCENTER_Y		(TITLEPLAYERSIZE_Y)
#define TITLEPLAYER_POS		(400)					//�v���C���[�̉�ʂ̏ꏊ
#define TITLEPLAYER_LIFE	(1)						//�v���C���[�̃��C�t

//=============================================================================
// �v���C���[�̏�Ԃ̎��
//=============================================================================

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 posMove;
	D3DXVECTOR3 move;
	int nLife;				//���C�t
	int nDirectionMove;
	int nCounterAnim;
	int nPatternAnim;
	bool bDisp;
}TitlePlayer;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitTitlePlayer(void);
void UninitTitlePlayer(void);
void UpdateTitlePlayer(void);
void DrawTitlePlayer(void);

TitlePlayer *GetTitlePlayer(void);
#endif