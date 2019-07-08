//=============================================================================
//
// ���f������ [player2.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _PLAYERL2_H_
#define _PLAYERL2_H_

#include "main.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
#define MAX_TEXT_NAME			(255)							//�t�@�C�����̖��O�̍ő吔
#define FILE_NAME_PLAYER2		"data\\TEXT\\Player2.txt"		//�ǂݍ���txt�t�@�C���̖��O
#define MAX_PARTS				(15)							//�p�[�c��
#define MODEL_SPEED				(1.0f)							//�v���C���[�X�s�[�h
#define MAX_PLAYER2ANIM			(8)								//�A�j���[�V������
#define MAX_PLAYER2KEY			(8)								//�L�[�t���[����

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef enum
{
	PLAYER2ANIM_NEUTRAL = 0,
	PLAYER2ANIM_WALK,
	PLAYER2ANIM_ATTACK,
	PLAYER2_MAX
}Player2Anim;

typedef struct
{
	char			FileName[MAX_TEXT_NAME];						//X�t�@�C����
	LPD3DXMESH		pMeshModelPlayer2 = NULL;						//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatModelPlayer2 = NULL;					//�}�e���A���̏��ւ̃|�C���^
	DWORD			nNumMatModelPlayer2 = 0;						//�}�e���A���̏��
	D3DXMATRIX		mtxWorldModelPlayer2;							//���[���h�}�g���b�N�X
	D3DXVECTOR3		posModelPlayer2;								//�ʒu
	D3DXVECTOR3		InitPos;										//�����ʒu
	D3DXVECTOR3		posAnim[MAX_PLAYER2ANIM][MAX_PLAYER2KEY];		//�A�j���[�V����pos
	D3DXVECTOR3		rotModelPlayer2;								//����
	D3DXVECTOR3		InitRot;										//��������
	D3DXVECTOR3		rotAnim[MAX_PLAYER2ANIM][MAX_PLAYER2KEY];		//�A�j���[�V����rot
	D3DXVECTOR3		rotDest;										//�ړI�̈ʒu
	int				nIdxModelPlayer2Parent = 0;						//�e���f���̃C���f�b�N�X�@-1���e
}ModelPlayer2;

typedef struct
{
		
	D3DXMATRIX		mtxWorldPlayer2;								//���[���h�}�g���b�N�X
	LPD3DXMESH		pMeshPlayer2 = NULL;							//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatPlayer2 = NULL;							//�}�e���A���̏��ւ̃|�C���^
	DWORD			nNumMatPlayer2 = 0;								//�}�e���A���̏��
	D3DXVECTOR3		posOld;											//�ߋ��̈ʒu
	D3DXVECTOR3		pos;											//�ʒu
	D3DXVECTOR3		move;											//�ړ�
	D3DXVECTOR3		rot;											//����
	int				nMaxPartsNum;									//�p�[�c�̍ő吔
	ModelPlayer2	aModelPlayer2[MAX_PARTS];						//[�Z]�����ɂ̓p�[�c��������
	int				nMaxAnimNum;									//�A�j���[�V�����̍ő吔
	int				nAnimloop[MAX_PLAYER2ANIM];						//���[�v
	int				nAnimKey[MAX_PLAYER2ANIM];						//�L�[��
	int				nAnimfram[MAX_PLAYER2ANIM][MAX_PLAYER2KEY];		//�t���[����
	Player2Anim		nAnimnow;										//���݂̃A�j���[�V����
	int				nAnimKeynow;									//���݂̃L�[
	bool			bAttack;										//�g�p���Ă��邩�ǂ���
	bool			bUse;											//�g�p���Ă��邩�ǂ���
	bool			bLand;											//�߂܂��Ă��邩�ǂ���
	int				nIdxShadow2;									//�ǂ̉e���g���Ă��邩
	int				nCntPlayer2;
}Player2;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer2(void);
void UninitPlayer2(void);
void UpdatePlayer2(void);
void DrawPlayer2(void);
Player2 *GetPlayer2(void);

#endif
