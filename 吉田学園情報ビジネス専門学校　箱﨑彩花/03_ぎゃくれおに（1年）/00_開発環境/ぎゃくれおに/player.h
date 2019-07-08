//=============================================================================
//
// ���f������ [player.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _PLAYERL_H_
#define _PLAYERL_H_

#include "main.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
#define MAX_TEXT_NAME			(255)							//�t�@�C�����̖��O�̍ő吔
#define FILE_NAME				"data\\TEXT\\Player1.txt"		//�ǂݍ���txt�t�@�C���̖��O
#define MAX_PARTS				(15)							//�p�[�c��
#define MODEL_SPEED				(1.0f)							//�v���C���[�X�s�[�h
#define MAX_PLAYERANIM			(8)								//�A�j���[�V������
#define MAX_PLAYERKEY			(8)								//�L�[�t���[����

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef enum
{
	PLAYERANIM_NEUTRAL = 0,		//�j���[�g�������[�V����
	PLAYERANIM_WALK,			//�������[�V����
	PLAYERANIM_ATTACK,			//�U�����[�V����
	PLALYER_MAX					//���[�V�����̍ő吔
}PlayerAnim;

typedef struct
{
	char			FileName[MAX_TEXT_NAME];						//X�t�@�C����
	LPD3DXMESH		pMeshModel = NULL;								//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatModel = NULL;							//�}�e���A���̏��ւ̃|�C���^
	DWORD			nNumMatModel = 0;								//�}�e���A���̏��
	D3DXMATRIX		mtxWorldModel;									//���[���h�}�g���b�N�X
	D3DXVECTOR3		posModel;										//�ʒu
	D3DXVECTOR3		InitPos;										//�����ʒu
	D3DXVECTOR3		posAnim[MAX_PLAYERANIM][MAX_PLAYERKEY];			//�A�j���[�V����pos
	D3DXVECTOR3		rotModel;										//����
	D3DXVECTOR3		InitRot;										//��������
	D3DXVECTOR3		rotAnim[MAX_PLAYERANIM][MAX_PLAYERKEY];			//�A�j���[�V����rot
	D3DXVECTOR3		rotDest;										//�ړI�̈ʒu
	int				nIdxModelParent = 0;							//�e���f���̃C���f�b�N�X�@-1���e
}Model;

typedef struct
{
		
	D3DXMATRIX		mtxWorldPlayer;									//���[���h�}�g���b�N�X
	LPD3DXMESH		pMeshPlayer = NULL;								//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatPlayer = NULL;							//�}�e���A���̏��ւ̃|�C���^
	DWORD			nNumMatPlayer = 0;								//�}�e���A���̏��
	D3DXVECTOR3		posOld;											//�ߋ��̈ʒu
	D3DXVECTOR3		pos;											//�ʒu
	D3DXVECTOR3		move;											//�ړ�
	D3DXVECTOR3		rot;											//����
	int				nMaxPartsNum;									//�p�[�c�̍ő吔
	Model			aModel[MAX_PARTS];								//[�Z]�����ɂ̓p�[�c��������
	int				nMaxAnimNum;									//�A�j���[�V�����̍ő吔
	int				nAnimloop[MAX_PLAYERANIM];						//���[�v
	int				nAnimKey[MAX_PLAYERANIM];						//�L�[��
	int				nAnimfram[MAX_PLAYERANIM][MAX_PLAYERKEY];		//�t���[����
	PlayerAnim		nAnimnow;										//���݂̃A�j���[�V����
	int				nAnimKeynow;									//���݂̃L�[
	bool			bAttack;										//�g�p���Ă��邩�ǂ���
	bool			bUse;											//�g�p���Ă��邩�ǂ���
	bool			bLand;											//�߂܂��Ă��邩�ǂ���
	int				nIdxShadow;									//�ǂ̉e���g���Ă��邩
	int				nCntPlayer;
}Player;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);

#endif
