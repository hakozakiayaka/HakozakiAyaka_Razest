//=============================================================================
//
// �G���� [enemy.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_ENEMY	(256)	// �G�̍ő吔

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMADE,
	ENEMYSTATE_MAX				//�G�̎�ނ̑���
} ENEMYSATATE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	int nType;							//���
	int nLife;							//�̗�
	bool bUse;						//�g�p���Ă��邩�ǂ���
	ENEMYSATATE state;		//�G�̏��
	int nCounterState;			//��ԊǗ��̃J�E���^�[
	int nCntAnim;					//�A�j���[�V�����J�E���^�[
	int nPatternAnim;			//�A�j���[�V�����̃p�^�[����
	int nCntMove;					//�G�̈ړ��J�E���^�[
	int nChangeMove;			//�G�̈ړ���
} Enemy;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType, int ChangeMove);
Enemy * GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);

#endif