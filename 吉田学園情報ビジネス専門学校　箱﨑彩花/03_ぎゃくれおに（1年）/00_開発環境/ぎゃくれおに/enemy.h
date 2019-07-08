//=============================================================================
//
// �S���� [enemy.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �S�̍\����
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMeshEnemy = NULL;			//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMatEnemy = NULL;		//�}�e���A���̏��ւ̃|�C���^
	DWORD nNumMatEnemy = 0;					//�}�e���A���̏��
	D3DXMATRIX mtxWorldEnemy;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 move;						//����
	D3DXVECTOR3	posOld;						//�ߋ��̈ʒu
	D3DXVECTOR3 vtxMinModel;				//�S�̍ŏ��l
	D3DXVECTOR3 vtxMaxModel;				//�S�̍ő�l
	int nCntPlayer;							//�v���C���[
	bool bUse;								//�g�p���Ă�����
}Enemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
Enemy *GetEnemy(void);

bool CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3  * pPosOld, D3DXVECTOR3  * pMove);
bool CollisionEnemy2(D3DXVECTOR3 * pPos, D3DXVECTOR3  * pPosOld, D3DXVECTOR3  * pMove);

#endif
