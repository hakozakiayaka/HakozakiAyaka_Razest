//=============================================================================
//
// �A�C�e������ [item.h]
// Author :�����ʉ�
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "game.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;				//�F
	int nCounterAnim;			//�A�j���[�V�����J�E���^�[
	int nPatternAnim;			//�A�j���[�V����No.
	int nType;							//�A�C�e���̎��
	bool bUse;						//�g�p���Ă��邩�ǂ���
} Item;

//=============================================================================
// �A�C�e�����̍\���̒�`
//=============================================================================
typedef struct
{	//�I�����
	D3DXVECTOR3 pos;		//�A�C�e���̈ʒu
	float fWidth;						//�A�C�e���̕�
	float fHeight;					//�A�C�e���̍���
	int nType;							//�A�C�e���̎��
} ItemInfoStageSelect;

typedef struct
{	//���ɂ���@�X�e�[�W1
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
} ItemInfoStage1;

typedef struct
{	//�s�[�}���@�X�e�[�W2
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
} ItemInfoStage2;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeught, int nType);		//�\���ʒu�A���A�����A�A�C�e���̎��
void CollisionItem(int nType);																				//�A�C�e���̓����蔻��
void DeleteItem(int nCntItem);																			//�A�C�e������������
#endif