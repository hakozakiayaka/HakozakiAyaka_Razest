//=============================================================================
//
// �J�������� [camera.cpp]
// Author :�@�L�n�@���u�@���@����
//
//=============================================================================
#include "camera.h"		//�J����
#include "input.h"		//�L�[�{�[�h
#include "player.h"		//�v���C���[
#include "player2.h"	//�v���C���[
#include "bullet.h"		//�e
#include "object.h"		//�I�u�W�F�N�g
#include "sound.h"		//�T�E���h
#include "effect.h"		//�G�t�F�N�g
#include "enemy.h"		//�S

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_ANGLE			(0.01f)				//�J�����p�x�̈ړ���
#define MOVE_ANGLE1			(0.001f)			//�J�����p�x�̈ړ���
//#define MOVE_CAMERA			(1200.0f)			//�J�����̋���
#define MOVE_OBJECT			(1000.0f)
#define MOVE_CAMERA			(160.0f)			//�J�����̋���
#define CAMERA_KM			(1200.0f)			//�J�����̕`�拗��
#define MOVE_SPEED			(0.001f)
#define MOVE_ANGLE2			(15.0f)
#define MOVE_ANGLE3			(0.03f)
#define MAX_CAMERA			(5)					//�J�����̍ő吔

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_Camera[MAX_CAMERA];					//�J�����̏��
int g_nCount;									//�b���J�E���g
float g_fCameraAngle = 45.0f;					//�p�x
float g_fRot;

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	//�v���C���[�̏��
	Object pObject = *GetObject();

	//================
	//1�v���C���[�ڂ̃J�����̈ʒu
	//================
	g_Camera[0].posV = D3DXVECTOR3(0.0f, 300.0f, -300.0f);			//���_�̏����l
	g_Camera[0].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	g_Camera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//�@���̌���
	g_Camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	g_Camera[0].fLength = g_Camera[0].posV.z - g_Camera[0].posR.z;	//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	g_Camera[0].nType = CAMERA_TYPE_NONE;							//���
	g_fCameraAngle = 45.0f;											//�p�x
	g_fRot = 0;

	//�r���[�|�[�g�̏���������
	g_Camera[0].ViewPort.X = 0;
	g_Camera[0].ViewPort.Y = 0;
	g_Camera[0].ViewPort.Width = SCREEN_WIDTH / 2;
	g_Camera[0].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[0].ViewPort.MinZ = 0.0f;
	g_Camera[0].ViewPort.MaxZ = 1.0f;

	//================
	// 2�v���C���[�ڂ̃J�����̈ʒu
	//================
	g_Camera[1].posV = D3DXVECTOR3(0.0f, 300.0f, -300.0f);			//���_�̏����l
	g_Camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	g_Camera[1].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	g_Camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	g_Camera[1].fLength = g_Camera[1].posV.z - g_Camera[1].posR.z;	//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	g_Camera[1].nType = CAMERA_TYPE_NONE;							//���
	g_fCameraAngle = 45.0f;											//�p�x
	g_fRot = 0;

	//�r���[�|�[�g�̏���������
	g_Camera[1].ViewPort.X = 0;
	g_Camera[1].ViewPort.Y = SCREEN_HEIGHT / 2;
	g_Camera[1].ViewPort.Width = SCREEN_WIDTH / 2;
	g_Camera[1].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[1].ViewPort.MinZ = 0.0f;
	g_Camera[1].ViewPort.MaxZ = 1.0f;

	//================
	// �S�J�����̈ʒu
	//================
	g_Camera[2].posV = D3DXVECTOR3(0.0f, 400.0f, -400.0f);			//���_�̏����l
	g_Camera[2].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	g_Camera[2].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	g_Camera[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	g_Camera[2].fLength = g_Camera[2].posV.z - g_Camera[2].posR.z;	//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	g_Camera[2].nType = CAMERA_TYPE_NONE;							//���
	g_fCameraAngle = 45.0f;											//�p�x
	g_fRot = 0;

	//�r���[�|�[�g�̏���������
	g_Camera[2].ViewPort.X = SCREEN_WIDTH / 2;
	g_Camera[2].ViewPort.Y = 0;
	g_Camera[2].ViewPort.Width = SCREEN_WIDTH / 2;
	g_Camera[2].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[2].ViewPort.MinZ = 0.0f;
	g_Camera[2].ViewPort.MaxZ = 1.0f;

	//================
	// �Œ�J�����̈ʒu
	//================
	g_Camera[3].posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���_�̏����l
	g_Camera[3].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	g_Camera[3].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	g_Camera[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	g_Camera[3].fLength = g_Camera[3].posV.z - g_Camera[3].posR.z;	//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	g_Camera[3].nType = CAMERA_TYPE_NONE;							//���
	g_fCameraAngle = 45.0f;											//�p�x
	g_fRot = 0;

	//�r���[�|�[�g�̏���������
	g_Camera[3].ViewPort.X = SCREEN_WIDTH / 2;
	g_Camera[3].ViewPort.Y = SCREEN_HEIGHT / 2;
	g_Camera[3].ViewPort.Width = SCREEN_WIDTH / 2;
	g_Camera[3].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[3].ViewPort.MinZ = 0.0f;
	g_Camera[3].ViewPort.MaxZ = 1.0f;

	//================
	// �^�C�g���̃J�����̈ʒu
	//================
	g_Camera[4].posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);			//���_�̏����l
	g_Camera[4].posR = D3DXVECTOR3(0.0f, 200.0f, 0.0f);				//�����_�̏����l
	g_Camera[4].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	g_Camera[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	g_Camera[4].fLength = g_Camera[4].posV.z - g_Camera[4].posR.z;	//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	g_Camera[4].nType = CAMERA_TYPE_NONE;							//���
	g_fCameraAngle = 45.0f;											//�p�x
	g_fRot = 0;

	//�r���[�|�[�g�̏���������
	g_Camera[4].ViewPort.X = 0;
	g_Camera[4].ViewPort.Y = 0;
	g_Camera[4].ViewPort.Width = SCREEN_WIDTH;
	g_Camera[4].ViewPort.Height = SCREEN_HEIGHT;
	g_Camera[4].ViewPort.MinZ = 0.0f;
	g_Camera[4].ViewPort.MaxZ = 1.0f;

	//================
	// �^�C�g���̃J�����̈ʒu
	//================
	g_Camera[5].posV = D3DXVECTOR3(1500.0f, 60.0f, -3600.0f);			//���_�̏����l
	g_Camera[5].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	g_Camera[5].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	g_Camera[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	g_Camera[5].fLength = g_Camera[5].posV.z - g_Camera[5].posR.z;	//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	g_Camera[5].nType = CAMERA_TYPE_NONE;							//���
	g_fCameraAngle = 45.0f;											//�p�x
	g_fRot = 0;

	//�r���[�|�[�g�̏���������
	g_Camera[5].ViewPort.X = 0;
	g_Camera[5].ViewPort.Y = 0;
	g_Camera[5].ViewPort.Width = SCREEN_WIDTH;
	g_Camera[5].ViewPort.Height = SCREEN_HEIGHT;
	g_Camera[5].ViewPort.MinZ = 0.0f;
	g_Camera[5].ViewPort.MaxZ = 1.0f;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera()
{
	//�v���C���[�̏��
	Object *pObject = GetObject();
	Player *pPlayer = GetPlayer();
	Player2 *pPlayer2 = GetPlayer2();
	Enemy *pEnemy = GetEnemy();
	Bullet *pBullet = GetBullet();

	static int nCount = 0;

	////============================
	////��s�@�̌��ɃJ�������s���悤�ɂ��鏈��
	////============================
	for (int nCount = 0; nCount < MAX_CAMERA; nCount++)
	{
		if (g_Camera[nCount].nType == CAMERA_TYPE_GAME)
		{//�Q�[�����J����
			if (nCount != 4 && nCount != 3)
			{
				if (nCount == 0)
				{
					///*if (pPlayer->move.x < 0.01f || pPlayer->move.x > -0.01f || pPlayer->move.z < 0.01f || pPlayer->move.z > -0.01f)
					//{*/
					//	//�񐔂𑫂�
					//	g_nCount++;
					//	//3�b��Ɍ��ɉ�肱��
					//	//if (g_nCount >= 180)
					//	//{//�~�܂��Ă���P�b���
					//		fDiAngle = (pPlayer->rot.y + D3DX_PI) - g_Camera[nCount].fAngle;
					//		if (fDiAngle > D3DX_PI)
					//		{
					//			fDiAngle -= D3DX_PI * 2.0f;
					//		}
					//		if (fDiAngle < -D3DX_PI)
					//		{
					//			fDiAngle += D3DX_PI * 2.0f;
					//		}
					//		//	�J�����̃A���O���ɖړI�̃A���O���𑫂��A���x��������
					//		g_Camera[nCount].fAngle += fDiAngle * 0.05f;

					//		if (g_Camera[nCount].fAngle > D3DX_PI)
					//		{
					//			fDiAngle -= D3DX_PI * 2.0f;
					//		}
					//		if (g_Camera[nCount].fAngle > D3DX_PI)
					//		{
					//			fDiAngle += D3DX_PI * 2.0f;
					//		}
					////	}
					////}
					////else
					////{//�����Ă���Ƃ��́A�O����
					////	g_nCount = 0;
					////}

					////=============================
					////�@ �@�}�E�X�ŃJ��������
					////=============================
					////�����_�ʒu�ύX
					//if (pMouse.lY < 0)
					//{//Y���W
					//	g_Camera[nCount].posR.y -= cosf(D3DX_PI * 0.0f) * (pMouse.lY / 2.0f);
					//}
					//if (pMouse.lY > 0)
					//{//Y���W
					//	g_Camera[nCount].posR.y -= cosf(D3DX_PI * 0.0f) * (pMouse.lY / 2.0f);
					//}
					//if (pMouse.lX < 0)
					//{//X���W
					//	g_Camera[nCount].rot.y += (pMouse.lX / 600.0f);
					//	g_Camera[nCount].posR.x = g_Camera[nCount].posV.x - sinf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;
					//	g_Camera[nCount].posR.z = g_Camera[nCount].posV.z - cosf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;
					//}
					//if (pMouse.lX > 0)
					//{//X���W
					//	g_Camera[nCount].rot.y += (pMouse.lX / 600.0f);
					//	g_Camera[nCount].posR.x = g_Camera[nCount].posV.x - sinf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;
					//	g_Camera[nCount].posR.z = g_Camera[nCount].posV.z - cosf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;
					//}

					////��ʂ��K�N�K�N���Ȃ��悤�ɂ���B
					//g_Camera[nCount].posR.x = g_Camera[nCount].posV.x - sinf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;
					//g_Camera[nCount].posR.z = g_Camera[nCount].posV.z - cosf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;

					//===================================
					//�����_���v���C���[�ɒǏ]�悤�ɂ���
					//===================================
					g_Camera[nCount].posR.x = pPlayer->pos.x;
					g_Camera[nCount].posR.z = pPlayer->pos.z;
					//���_���v���C���[�ɒǏ]�悤�ɂ���
					g_Camera[nCount].posV.x = pPlayer->pos.x - sinf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
					g_Camera[nCount].posV.z = pPlayer->pos.z - cosf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
				}
				if (nCount == 1)
				{
				

					//===================================
					//�����_���v���C���[�ɒǏ]�悤�ɂ���
					//===================================
					g_Camera[nCount].posR.x = pPlayer2->pos.x;
					g_Camera[nCount].posR.z = pPlayer2->pos.z;
					//���_���v���C���[�ɒǏ]�悤�ɂ���
					g_Camera[nCount].posV.x = pPlayer2->pos.x - sinf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
					g_Camera[nCount].posV.z = pPlayer2->pos.z - cosf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
				}
				if (nCount == 2)
				{
					//===================================
					//�����_���v���C���[�ɒǏ]�悤�ɂ���
					//===================================
					for (int nCount1 = 0; nCount1 < 2; nCount1++)
					{
						g_Camera[nCount].posR.x = pEnemy[nCount1].pos.x;
						g_Camera[nCount].posR.z = pEnemy[nCount1].pos.z;
						//���_���v���C���[�ɒǏ]�悤�ɂ���
						g_Camera[nCount].posV.x = pEnemy[nCount1].pos.x - sinf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
						g_Camera[nCount].posV.z = pEnemy[nCount1].pos.z - cosf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
					}
				}
			}
			else if (nCount == 3)
			{//�Œ�J����
				g_Camera[nCount].posV = D3DXVECTOR3(2000.0f, 5600.0f, -2051.0f);	//���_�̏����l
				g_Camera[nCount].posR = D3DXVECTOR3(2000.0f, 0.0f, -2001.0f);		//�����_�̏����l
			}
		}
		else if (g_Camera[nCount].nType == CAMERA_TYPE_DEMO)
		{//�^�C�g���̃J����
			if (nCount == 4)
			{
				g_Camera[nCount].posV = D3DXVECTOR3(0.0f, 50.0f, 0.0f);	//���_�̏����l
				g_Camera[nCount].posR = D3DXVECTOR3(0.0f,0.0f, 0.0f);	//�����_�̏����l
			}
		}
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(CAMERATYPE CameraType, int nIndxCamera)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_Camera[nIndxCamera].nType = CameraType;

	//�r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_Camera[nIndxCamera].ViewPort);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera[nIndxCamera].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	(
		&g_Camera[nIndxCamera].mtxProjection,
		D3DXToRadian(g_fCameraAngle),
		(float)g_Camera[nIndxCamera].ViewPort.Width / (float)g_Camera[nIndxCamera].ViewPort.Height,
		10.0f,
		10000
	);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera[nIndxCamera].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera[nIndxCamera].mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_Camera[nIndxCamera].mtxView,
		&g_Camera[nIndxCamera].posV,
		&g_Camera[nIndxCamera].posR,
		&g_Camera[nIndxCamera].vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera[nIndxCamera].mtxView);

}
//=============================================================================
//	�J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_Camera[0];
}