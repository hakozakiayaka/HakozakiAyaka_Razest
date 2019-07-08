//=============================================================================
//
// �|���S������ [billboord.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _BILLBOORD_H_
#define _BILLBOORD_H_

#include "main.h"

//*****************************************************************************
// �ǂ̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3		posBillBoord;		//�ʒu
	D3DXVECTOR3		rotBillBoord;		//����
	D3DXMATRIX		mtxWorldBillBoord;	//���[���h�}�g���b�N�X
	int				nType;				//���
	int				nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int				nPatteunAnim;		//�A�j���[�V�����p�^�[��No.
	int				nIdxShadow;
	bool			bUse;				//�g�p���Ă邩�ǂ���
}BillBoord;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBillBoord(void);
void UninitBillBoord(void);
void UpdateBillBoord(void);
void DrawBillBoord(void);

void SetBillBoord(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nType);
void DeleteBillBoord(int nCntBillBoord);
void CollisionBillBoord(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove);

#endif
