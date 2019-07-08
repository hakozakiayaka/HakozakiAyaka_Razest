//=============================================================================
//
// �v���C���[���� [playrt.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYERSIZE_X	(160)
#define PLAYERSIZE_Y	(80)
#define POSCENTER_X		(PLAYERSIZE_X / 2)
#define POSCENTER_Y		(PLAYERSIZE_Y)
#define PLAYER_POS		(400)					//�v���C���[�̉�ʂ̏ꏊ
#define PLAYER_LIFE		(6)						//�v���C���[�̃��C�t

//=============================================================================
// �v���C���[�̏�Ԃ̎��
//=============================================================================
typedef enum
{//�񋓌^
	PLAYERSTATE_APPEAR = 0,	//�o�����,�i0�j
	PLAYERSTATE_NOMAL,		//�ʏ��ԁi1�j
	PLAYERSTATE_DAMAGE,		//�_���[�W��ԁi2�j
	PLAYERSTATE_DEATH,		//�G�̎��S��ԁi3�j
	PLAYERSTATE_MAX			//�G�̏�Ԃ̑����i4�j
}PLAYERSTATE;

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
	PLAYERSTATE state;		//���
	int nDirectionMove;
	int nCounterAnim;
	int nPatternAnim;
	int nCntstate;			//��Ԃ̃J�E���^�[
	bool bDisp;
}Player;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void HitPlayer(int nDamage);
Player *GetPlayer(void);
#endif