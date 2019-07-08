//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �L�n�@���u�@���@����
//
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS		//scanf�G���[����
#include <stdio.h>					//stdio
#include "player2.h"				//�v���C���[
#include "input.h"					//�L�[�{�[�h
#include "camera.h"					//�J����
#include "shadow.h"					//�e
#include "bullet.h"					//�e
#include "effect.h"					//�G�t�F�N�g
#include "object.h"					//�I�u�W�F�N�g
#include "sound.h"					//�T�E���h
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define MODEL_NAME			"data\\MODEL\\airplane000.x"	//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME			"data\\MODEL\\00_body.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME2			"data\\MODEL\\01_head.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME3			"data\\MODEL\\02_armR.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME4			"data\\MODEL\\03_handR.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME5			"data\\MODEL\\04_armL.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME6			"data\\MODEL\\05_handL.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME7			"data\\MODEL\\06_legR.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME8			"data\\MODEL\\07_footR.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME9			"data\\MODEL\\08_legL.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME10			"data\\MODEL\\09_footL.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define PLAYER2_SPEED			(5.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Player2		g_Player2;							//�v���C���[
int			g_nCntTimePlayer2;					//�v���C���[�J�E���^�[

//=============================================================================
// ����������
//=============================================================================
void InitPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C���̃|�C���^
	FILE *pFile;
	//�v���C���[�J�E���^�[
	int nCntPlayer2;

	// �ʒu�E�����̏����ݒ�
	g_Player2.pos = D3DXVECTOR3(200, 20, 40);
	g_Player2.rot = D3DXVECTOR3(0, 0, 0);
	g_Player2.move = D3DXVECTOR3(0, 0, 0);
	g_Player2.bUse = true;
	g_Player2.bLand = true;
	g_Player2.nCntPlayer2 = 1;

	//�t�@�C���ݒ�
	pFile = fopen(FILE_NAME_PLAYER2, "r");

	//�v���C���[�́��e�L�X�g�f�[�^�̓ǂݍ���
	if (pFile != NULL)
	{
		//�g���p�[�c��
		fscanf(pFile, "%d", &g_Player2.nMaxPartsNum);	//�ǂݍ���
		//�t�@�C����
		for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
		{
			fscanf(pFile, "%s", &g_Player2.aModelPlayer2[nCntPlayer2].FileName[0]); //�ǂݍ���
		}

		for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
		{//�����l�ƌ���
			fscanf(pFile, "%d", &g_Player2.aModelPlayer2[nCntPlayer2].nIdxModelPlayer2Parent);	//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitPos.x);				//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitPos.y);				//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitPos.z);				//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitRot.x);				//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitRot.y);				//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitRot.z);				//�ǂݍ���
		}

		//�t�@�C���ǂݍ���
		fscanf(pFile, "%d", &g_Player2.nMaxAnimNum);

		for (int nCntPlayer2Anim = 0; nCntPlayer2Anim < g_Player2.nMaxPartsNum; nCntPlayer2Anim++)
		{
			//�t���[����
			fscanf(pFile, "%d", &g_Player2.nAnimloop[nCntPlayer2Anim]);
			//�L�[��
			fscanf(pFile, "%d", &g_Player2.nAnimKey[nCntPlayer2Anim]);

			for (int nCntPlayer2AnimKey = 0; nCntPlayer2AnimKey < g_Player2.nAnimKey[nCntPlayer2Anim]; nCntPlayer2AnimKey++)
			{
				fscanf(pFile, "%d", &g_Player2.nAnimfram[nCntPlayer2Anim][nCntPlayer2AnimKey]);//�ǂݍ���

				for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
				{
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].posAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].x);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].posAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].y);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].posAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].z);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].rotAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].x);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].rotAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].y);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].rotAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].z);		//�ǂݍ���
				}
			}
		}

		fclose(pFile);	//�t�@�C�������
	}
	else
	{
		MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s!", "�x��", MB_ICONWARNING);
	}

	//x�t�@�C���̓ǂݍ���
	for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX
		(
			&g_Player2.aModelPlayer2[nCntPlayer2].FileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player2.aModelPlayer2[nCntPlayer2].pBuffMatModelPlayer2,
			NULL,
			&g_Player2.aModelPlayer2[nCntPlayer2].nNumMatModelPlayer2,
			&g_Player2.aModelPlayer2[nCntPlayer2].pMeshModelPlayer2
		);
	}

	//�e�̏������ݒ�
	g_Player2.nIdxShadow2 = SetShadow(g_Player2.pos,g_Player2.rot,15,15);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer2(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// ���b�V���̊J��
		if (g_Player2.aModelPlayer2[nCount].pMeshModelPlayer2 != NULL)
		{
			g_Player2.aModelPlayer2[nCount].pMeshModelPlayer2->Release();
			g_Player2.aModelPlayer2[nCount].pMeshModelPlayer2 = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// �}�e���A���̊J��
		if (g_Player2.aModelPlayer2[nCount].pBuffMatModelPlayer2 != NULL)
		{
			g_Player2.aModelPlayer2[nCount].pBuffMatModelPlayer2->Release();
			g_Player2.aModelPlayer2[nCount].pBuffMatModelPlayer2 = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer2(void)
{
	//�J�����̏��
	Camera *pCamera = GetCamera();

	//�S�̎擾
	Enemy *pEnemy = GetEnemy();

	//�t���[���J�E���g
	g_nCntTimePlayer2++;

	//�O��̈ʒu��ۑ�
	g_Player2.posOld = g_Player2.pos;

	float nSpeed = 5.0f;	//���x
	//float fDiffAngle;

	//�ǂ̂����蔻��
	if (g_Player2.pos.z >= 200)
	{//��
		g_Player2.pos.z = 200;
	}
	if (g_Player2.pos.z <= -4200)
	{//��
		g_Player2.pos.z = -4200;
	}
	if (g_Player2.pos.x >= 4200)
	{//�E
		g_Player2.pos.x = 4200;
	}
	if (g_Player2.pos.x <= -200)
	{//��
		g_Player2.pos.x = -200;
	}

	//�ړ�����
	if (GetKeyboardPress(DIK_U) == true)
	{//���̏�							����ړ�
		if (GetKeyboardPress(DIK_K) == true)
		{
			g_Player2.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player2.rot.y = ((D3DX_PI * -0.75f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
		else if (GetKeyboardPress(DIK_H) == true)
		{
			g_Player2.move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player2.rot.y = ((D3DX_PI * 0.75f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
		else
		{
			g_Player2.move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player2.rot.y = ((D3DX_PI * -1.0f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
	}
	else if (GetKeyboardPress(DIK_J) == true)
	{//���̉�							 ����ړ�
		if (GetKeyboardPress(DIK_K) == true)
		{
			g_Player2.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player2.rot.y = ((D3DX_PI * -0.25f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
		else if (GetKeyboardPress(DIK_H) == true)
		{
			g_Player2.move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player2.rot.y = ((D3DX_PI * 0.25f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
		else
		{
			g_Player2.move.x += sinf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player2.rot.y = ((D3DX_PI * 0.0f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
	}
	else if (GetKeyboardPress(DIK_K) == true)
	{//���̉E							�� �E�ړ�
		g_Player2.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player2.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* MODEL_SPEED;
		//���̕����Ɍ���
		g_Player2.rot.y = ((D3DX_PI * -0.5f) + pCamera->rot.y);

		if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
		{
			g_Player2.nAnimnow = PLAYER2ANIM_WALK;
			g_nCntTimePlayer2 = 0;
			g_Player2.nAnimKeynow = 0;
		}
	}
	else if (GetKeyboardPress(DIK_H) == true)
	{//���̍�							 �� ���ړ�
		g_Player2.move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player2.move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		//���̕����Ɍ���
		g_Player2.rot.y = ((D3DX_PI * 0.5f) + pCamera->rot.y);

		if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
		{
			g_Player2.nAnimnow = PLAYER2ANIM_WALK;
			g_nCntTimePlayer2 = 0;
			g_Player2.nAnimKeynow = 0;
		}
	}
	else if (GetJoyPadPress(DIJS_BUTTON_10, 1) == true || GetJoyPadPress(DIJS_BUTTON_11, 1) == true || GetJoyPadPress(DIJS_BUTTON_12, 1) == true || GetJoyPadPress(DIJS_BUTTON_13, 1) == true)
	{//�W���C�R��
		g_Player2.pos.x -= sinf(pCamera->fAngle - GetJotPadRightStick(1)) * PLAYER2_SPEED;
		g_Player2.pos.z -= cosf(pCamera->fAngle - GetJotPadRightStick(1)) * PLAYER2_SPEED;

		g_Player2.rot.y = pCamera->fAngle - GetJotPadRightStick(1);

		if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
		{
			g_Player2.nAnimnow = PLAYER2ANIM_WALK;
			g_nCntTimePlayer2 = 0;
			g_Player2.nAnimKeynow = 0;
		}
	}
	else
	{
		if (g_Player2.nAnimnow != PLAYER2ANIM_NEUTRAL)
		{
			g_Player2.nAnimnow = PLAYER2ANIM_NEUTRAL;
			g_nCntTimePlayer2 = 0;
			g_Player2.nAnimKeynow = 0;
		}
	}

	//�ʒu���ړ��ɑ��
	g_Player2.pos += g_Player2.move;

	//����������
	g_Player2.move.x += (0.0f - g_Player2.move.x) * 0.2f;
	g_Player2.move.z += (0.0f - g_Player2.move.z) * 0.2f;

	//�e�����Ă���
	SetPositionShadow(g_Player2.nIdxShadow2, g_Player2.pos,g_Player2.rot);

	//�����蔻��
	CollisionObject(&g_Player2.pos, &g_Player2.posOld, &g_Player2.move);
	CollisionEnemy2(&g_Player2.pos, &g_Player2.posOld, &g_Player2.move);

	//�����̃��[�J���ϐ�
	float fDes;
	float frac;


	//�L�[��i�߂�I
	if (g_nCntTimePlayer2 % g_Player2.nAnimfram[g_Player2.nAnimnow][g_Player2.nAnimKeynow] == 0)
	{
		g_nCntTimePlayer2 = 0;
		g_Player2.nAnimKeynow = (g_Player2.nAnimKeynow + 1) % g_Player2.nAnimKey[g_Player2.nAnimnow];
	}

	//�����̌v�Z
	frac = (g_Player2.nAnimfram[g_Player2.nAnimnow][g_Player2.nAnimKeynow] - g_nCntTimePlayer2) * 1.0f;

	//�A�j���[�V����
	for (int nCntPlayer2Anim = 0; nCntPlayer2Anim < g_Player2.nMaxPartsNum; nCntPlayer2Anim++)
	{
		//===================
		// X�̊p�x
		//===================

		//�ړI�̊p�x������ׂ�
		g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest = g_Player2.aModelPlayer2[nCntPlayer2Anim].rotAnim[g_Player2.nAnimnow][g_Player2.nAnimKeynow];

		//x�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.x > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.x -= D3DX_PI * 2.0f;
		}
		//x�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.x < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.x += D3DX_PI * 2.0f;
		}

		//
		fDes = g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.x - g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x;

		//�����̒���
		if (fDes > D3DX_PI)
		{
			fDes -= D3DX_PI * 2.0f;
		}
		if (fDes > D3DX_PI)
		{
			fDes += D3DX_PI * 2.0f;
		}

		//���݂̌����̐ݒ�
		g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x += fDes / frac;

		//x�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x -= D3DX_PI * 2.0f;
		}
		//x�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x += D3DX_PI * 2.0f;
		}


		//===================
		// Y�̊p�x
		//===================

		//y�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.y > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.y -= D3DX_PI * 2.0f;
		}
		//y�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.y < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.y += D3DX_PI * 2.0f;
		}

		//
		fDes = g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.y - g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y;

		//�����̒���
		if (fDes > D3DX_PI)
		{
			fDes -= D3DX_PI * 2.0f;
		}
		if (fDes > D3DX_PI)
		{
			fDes += D3DX_PI * 2.0f;
		}

		//���݂̌����̐ݒ�
		g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y += fDes / frac;

		//x�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y -= D3DX_PI * 2.0f;
		}
		//x�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y += D3DX_PI * 2.0f;
		}

		//===================
		// Z�̊p�x
		//===================

		//z�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.z > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.z -= D3DX_PI * 2.0f;
		}
		//z�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.z < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.z += D3DX_PI * 2.0f;
		}

		//
		fDes = g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.z - g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z;

		//�����̒���
		if (fDes > D3DX_PI)
		{
			fDes -= D3DX_PI * 2.0f;
		}
		if (fDes > D3DX_PI)
		{
			fDes += D3DX_PI * 2.0f;
		}

		//���݂̌����̐ݒ�
		g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z += fDes / frac;

		//x�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z -= D3DX_PI * 2.0f;
		}
		//x�ړI�̈ʒu�̒���
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z += D3DX_PI * 2.0f;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;						//

	{//�v���C���[
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player2.mtxWorldPlayer2);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player2.rot.y, g_Player2.rot.x, g_Player2.rot.z);
		D3DXMatrixMultiply(&g_Player2.mtxWorldPlayer2, &g_Player2.mtxWorldPlayer2, &mtxRot);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player2.pos.x, g_Player2.pos.y, g_Player2.pos.z);
		D3DXMatrixMultiply(&g_Player2.mtxWorldPlayer2, &g_Player2.mtxWorldPlayer2, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player2.mtxWorldPlayer2);
	}
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player2.aModelPlayer2[nCntParts].nIdxModelPlayer2Parent < 0)
		{//�e���f��
			mtxParent = g_Player2.mtxWorldPlayer2;
		}
		else
		{//�q���f��
			mtxParent = g_Player2.aModelPlayer2[g_Player2.aModelPlayer2[nCntParts].nIdxModelPlayer2Parent].mtxWorldModelPlayer2;
		}
		{//�e���f��
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_Player2.aModelPlayer2[nCntParts].InitRot.y,
				g_Player2.aModelPlayer2[nCntParts].InitRot.x,
				g_Player2.aModelPlayer2[nCntParts].InitRot.z
			);
			D3DXMatrixMultiply
			(
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&mtxRot
			);
			// �ʒu�𔽉f
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_Player2.aModelPlayer2[nCntParts].InitPos.x,
				g_Player2.aModelPlayer2[nCntParts].InitPos.y,
				g_Player2.aModelPlayer2[nCntParts].InitPos.z
			);
			D3DXMatrixMultiply
			(
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&mtxTrans
			);

			D3DXMatrixMultiply
			(
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&mtxParent
			);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player2.aModelPlayer2[nCntParts].pBuffMatModelPlayer2->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player2.aModelPlayer2[nCntParts].nNumMatModelPlayer2; nCntMat++)
			{
				if (g_Player2.bUse == true)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`����NULL�ɂ���
					pDevice->SetTexture(0, NULL);

					//pDevice->SetTexture(0, g_Player2.nNumMatPlayer2);

					// �v���C���[(�p�[�c)�̕`��
					g_Player2.aModelPlayer2[nCntParts].pMeshModelPlayer2->DrawSubset(nCntMat);
				}
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=========================================================================================================================
// �v���C���[�̎擾����
//=========================================================================================================================
Player2 *GetPlayer2(void)
{
	return &g_Player2;
}
