//=============================================================================
//
// ���f������ [player.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _PLAYERL_H_
#define _PLAYERL_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_LIFE				(5)									//���C�t

//===============================================================================
//�\���̂̒�`
//===============================================================================
typedef enum
{
	PLAYERSATATE_APPEAR = 0,	//�o�����
	PLAYERSTATE_NORMAL,			//�ʏ���
	PLAYERSTATE_DAMADE,			//�_���[�W���
	PLAYERSTATE_DEATH,				//���S���
	PLAYERSTATE_MAX					//�v���C���[�̎�ނ̑���
} PLAYERSATATE;

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMeshModel = NULL;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel = NULL;	//�}�e���A���̏��ւ̃|�C���^
	DWORD nNumMatModel = 0;						//�}�e���A���̏��
	D3DXMATRIX mtxWorldModel;						//���[���h�}�g���b�N�X
	D3DXVECTOR3 posModel;								//�ʒu
	D3DXVECTOR3 rotModel;								//����
	int nIdxModelParent = 0;								//�e���f���̃C���f�b�N�X�@-1���e
} Model2;

typedef struct
{
	D3DXMATRIX mtxWorldPlayer;							//���[���h�}�g���b�N�X
	LPD3DXMESH pMeshPlayer = NULL;				//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatPlayer = NULL;		//�}�e���A���̏��ւ̃|�C���^
	DWORD nNumMatPlayer = 0;							//�}�e���A���̏��
	D3DXVECTOR3 posOld;										//�ߋ��̈ʒu
	D3DXVECTOR3 pos;											//�ʒu
	D3DXVECTOR3 move;											//�ړ�
	D3DXVECTOR3 rot;												//����
	Model2 aModel[13];											//[�Z]�����ɂ̓p�[�c��������
	D3DXVECTOR3 vtxMaxPlayer;							//�v���C���[�̃p�[�c�̍ő吔
	D3DXVECTOR3 vtxMinPlayer;							//�v���C���[�̃p�[�c�̍ŏ��l
	PLAYERSATATE state;										//�v���C���[�̃X�e�[�g
	D3DXCOLOR col;													//�J���[
	int nLife;																//�v���C���[�̃��C�t
	int nCntState;														//��ԊǗ��̃J�E���^�[
	bool bDisp;															//�\�����邩���Ȃ���
}Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);					//�v���C���[�̓����蔻�菈��
Player *GetPlayer(void);

#endif