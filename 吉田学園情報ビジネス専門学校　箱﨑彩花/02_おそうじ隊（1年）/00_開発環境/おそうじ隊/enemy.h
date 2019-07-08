//=============================================================================
//
// �G�l�~�[���� [	enemy.h]
// Author : �����ʉ�
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMY	(256)

//*****************************************************************************
// �G�l�~�[�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 rot;								//����
	D3DXMATRIX mtxWorldEnemy;			//���[���h�}�g���b�N�X
	int nIdxEnemyShadow;						//�e���g���Ă��邩�ǂ���
	int nTexType;										//�e�N�X�`���̃^�C�v
	int nCntAnim;										//�J�E���^�[�A�j���[�V����
	int nPatternAnim;								//�p�^�[���A�j���[�V����
	bool bUse;											//�r���{�[�h���g���Ă��邩�ǂ���
} Enemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int TexType);
void DeleteEnemy(int nCntEnemy);
Enemy *GetEnemy(void);
#endif