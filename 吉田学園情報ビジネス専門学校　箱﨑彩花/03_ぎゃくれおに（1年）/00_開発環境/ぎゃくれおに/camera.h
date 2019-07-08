//=============================================================================
//
// �J�������� [camera.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �J�����̍\����
//*****************************************************************************
typedef enum
{
	CAMERA_TYPE_NONE = 0,
	CAMERA_TYPE_DEMO,
	CAMERA_TYPE_RANKING_DEMO,
	CAMERA_TYPE_GAME,
	CAMERA_TYPE_MAX
}CAMERATYPE;

typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DXVECTOR3 rot;			//�J�����̌���������
	float		fDistance;		//����
	D3DXVECTOR3 vecU;			//������x�N�g��
	D3DXMATRIX	mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	mtxView;		//�r���[�}�g���b�N�X
	float		fAngle;			//�p�x
	float		fLength;		//����
	int			nType;			//���
	D3DVIEWPORT9 ViewPort;
}Camera;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(CAMERATYPE CameraType, int nIndxCamera);
Camera *GetCamera(void);

#endif
