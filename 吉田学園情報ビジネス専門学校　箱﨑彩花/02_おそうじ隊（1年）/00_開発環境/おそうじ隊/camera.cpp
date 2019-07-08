//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_SPEED	(0.6f)					//�J�����̃X�s�[�h
#define VIEW_Y					(90.0f)				//���_��Y���W
#define VIEW_Z					(210.0f)				//���_��Z���W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_camera;	//�J�����̏��

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	//�\���̂̏�����
	g_camera.posV = D3DXVECTOR3(0.0f, VIEW_Y, -VIEW_Z);		//���_
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�����_
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//������x�N�g��
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//����
	g_camera.distance = VIEW_Z;													//����
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
void UpdateCamera(void)
{
	float fDestAngle = 0;
	float fMoveAngle = 0;

	//���f���̎擾
	Player * pPlayer = GetPlayer();

	//���f���ɃJ�������Ǐ]����
	g_camera.posV.x = pPlayer->pos.x;
	g_camera.posV.z = pPlayer->pos.z - g_camera.distance;

	g_camera.posR.x = g_camera.posV.x + sinf(0.0f + g_camera.rot.y) * g_camera.distance;
	g_camera.posR.z = g_camera.posV.z + cosf(0.0f + g_camera.rot.y) * g_camera.distance;

#if 0
	//�J�����ړ� (W,S,A,D)
	if (GetKeyboardPress(DIK_W) == true)
	{	//W�L�[�������ꂽ
		g_camera.posV.x += sinf(0.0f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posV.z += cosf(0.0f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posR.x = g_camera.posV.x + sinf(0.0f + g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(0.0f + g_camera.rot.y) * g_camera.distance;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{	//S�L�[�������ꂽ
		g_camera.posV.x += sinf(D3DX_PI + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posV.z += cosf(D3DX_PI + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posR.x = g_camera.posV.x + sinf(0.0f + g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(0.0f + g_camera.rot.y) * g_camera.distance;
	}
	if (GetKeyboardPress(DIK_A) == true)
	{	//A�L�[�������ꂽ
		g_camera.posV.x += sinf(D3DX_PI * -0.5f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posV.z += cosf(D3DX_PI * -0.5f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posR.x = g_camera.posV.x + sinf(0.0f + g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(0.0f + g_camera.rot.y) * g_camera.distance;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{	//D�L�[�������ꂽ
		g_camera.posV.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posV.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * CAMERA_SPEED;
		g_camera.posR.x = g_camera.posV.x + sinf(0.0f + g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(0.0f + g_camera.rot.y) * g_camera.distance;
	}
#endif

	//���_���� (Y,N)
	if (GetKeyboardPress(DIK_Y) == true)
	{	//Y�L�[�������ꂽ
		g_camera.posV.x += sinf(0.0f) * CAMERA_SPEED;
		g_camera.posV.y += cosf(0.0f) * CAMERA_SPEED;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{	//N�L�[�������ꂽ
		g_camera.posV.x += sinf(D3DX_PI) * CAMERA_SPEED;
		g_camera.posV.y += cosf(D3DX_PI) * CAMERA_SPEED;
	}

	//�����_���� (T,B)
	if (GetKeyboardPress(DIK_T) == true)
	{	//T�L�[�������ꂽ
		g_camera.posR.x += sinf(0.0f) * CAMERA_SPEED;
		g_camera.posR.y += cosf(0.0f) * CAMERA_SPEED;
	}
	if (GetKeyboardPress(DIK_B) == true)
	{	//B�L�[�������ꂽ
		g_camera.posR.x += sinf(D3DX_PI) * CAMERA_SPEED;
		g_camera.posR.y += cosf(D3DX_PI) * CAMERA_SPEED;
	}

	////���_���� (Z,C)
	//if (GetKeyboardPress(DIK_Z) == true)
	//{	//Z�L�[�������ꂽ
	//	g_camera.rot.y += 0.02f;		//��]�̑���
	//	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y - D3DX_PI) * g_camera.distance;
	//	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y - D3DX_PI) * g_camera.distance;
	//}
	//if (GetKeyboardPress(DIK_C) == true)
	//{	//C�L�[�������ꂽ
	//	g_camera.rot.y -= 0.02f;
	//	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y - D3DX_PI) * g_camera.distance;
	//	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y - D3DX_PI) * g_camera.distance;
	//}

	//�����_����
	if (GetKeyboardPress(DIK_Q) == true)
	{	//Q�L�[�������ꂽ
		g_camera.rot.y -= 0.02f;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.distance;
	}
	if (GetKeyboardPress(DIK_E) == true)
	{	//E�L�[�������ꂽ
		g_camera.rot.y += 0.02f;
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.distance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.distance;
	}


	////�p�x�̏C��
	//g_camera.rot.y = fDestAngle - fMoveAngle;
	//if (g_camera.rot.y > D3DX_PI)
	//{
	//	g_camera.rot.y -= D3DX_PI * 2.0f;
	//}
	//if (g_camera.rot.y < D3DX_PI)
	//{
	//	g_camera.rot.y += D3DX_PI * 2.0f;
	//}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f,10000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//=============================================================================
// �J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}