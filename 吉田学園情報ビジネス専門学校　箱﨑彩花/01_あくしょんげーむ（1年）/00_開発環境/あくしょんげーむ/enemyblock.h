//=============================================================================
//
// �G�u���b�N���� [enemyblock.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _ENEMYBLOCK_H_
#define _ENEMYBLOCK_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	ENEMYBLOCKSTATE_NORMAL = 0,
	ENEMYBLOCKSTATE_DAMADE,
	ENEMYBLOCKSTATE_MAX				//�G�u���b�N�̎�ނ̑���
} ENEMYBLOCKSATATE;

typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	bool bUse;									//�g�p���Ă��邩�ǂ���
	ENEMYBLOCKSATATE state;		//�G�u���b�N�̏��
	int nCounterState;						//��ԊǗ��̃J�E���^�[
	float fWidth;
	float fHeight;
} ENEMYBLOCK;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitEnemyBlock(void);
void UninitEnemyBlock(void);
void UpdateEnemyBlock(void);
void DrawEnemyBlock(void);
void SetEnemyBlock(D3DXVECTOR3 pos, float fWidth, float fHight);
void CollisionEnemyBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld,
	D3DXVECTOR3 * pMove, float fWidth, float fHeight);

#endif