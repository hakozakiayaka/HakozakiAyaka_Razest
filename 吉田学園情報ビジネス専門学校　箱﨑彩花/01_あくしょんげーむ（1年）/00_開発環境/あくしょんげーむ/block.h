//=============================================================================
//
// �u���b�N���� [block.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef enum
{
	BLOCKTYPE_NORMAL = 0,		//�u���b�N�̒ʏ���
	BLOCKTYPE_WIDTH,					//�u���b�N�������i���E�j
	BLOCKTYPE_MAX						//�u���b�N�̎�ނ̑���
} BLOCKTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	float fWidth;						//��
	float fHeight;					//����
	BLOCKTYPE nType;		//�u���b�N�̎��
	int nCntType;					//�u���b�N�̎�ނ̃J�E���^�[
	int nTexType;					//�u���b�N�e�N�X�`���̎��
	bool bLand;						//�����蔻�肪�g�p����Ă��邩�ǂ���
	bool bUse;						//�g�p���Ă��邩�ǂ���
} Block;

//=============================================================================
// �u���b�N��Ԃ̍\���̂̒�`
//=============================================================================
typedef struct
{	//�I�����
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nTexType;
} BlockInfoSelect;

typedef struct
{	//���ɂ���@�X�e�[�W1
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nTexType;
} BlockInfoStage1;

typedef struct
{	//�s�[�}���@�X�e�[�W2
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nTexType;
} BlockInfoStage2;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nTexType);
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, 
	D3DXVECTOR3 * pMove,float fWidth,float fHeight);		//���݂̈ʒu�A�O��̈ʒu�A�ړ���

#endif