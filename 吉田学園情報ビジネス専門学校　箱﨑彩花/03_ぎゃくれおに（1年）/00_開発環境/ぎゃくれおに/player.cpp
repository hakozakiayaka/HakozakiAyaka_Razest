//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �L�n�@���u�@���@����
//
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS		//scanf�G���[����
#include <stdio.h>					//stdio
#include "player.h"					//�v���C���[
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
#define PLAYER1_SPEED			(5.0f)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Player		g_Player;							//�v���C���[
int			g_nCntTimePlayer;					//�v���C���[�J�E���^�[
float		g_fJoyStickAnglePlayer1;			//

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C���̃|�C���^
	FILE *pFile;
	//�v���C���[�J�E���^�[
	int nCntPlayer;

	// �ʒu�E�����̏����ݒ�
	g_Player.pos = D3DXVECTOR3(0, 20, 40);
	g_Player.rot = D3DXVECTOR3(0, 0, 0);
	g_Player.move = D3DXVECTOR3(0, 0, 0);
	g_Player.nCntPlayer = 1;
	g_Player.bUse = true;
	g_Player.bLand = true;

	//�t�@�C���ݒ�
	pFile = fopen(FILE_NAME, "r");

	//�v���C���[�́��e�L�X�g�f�[�^�̓ǂݍ���
	if (pFile != NULL)
	{
		//�g���p�[�c��
		fscanf(pFile, "%d", &g_Player.nMaxPartsNum);	//�ǂݍ���

		//�t�@�C����
		for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
		{
			fscanf(pFile, "%s", &g_Player.aModel[nCntPlayer].FileName[0]); //�ǂݍ���
		}

		for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
		{//�����l�ƌ���
			fscanf(pFile, "%d", &g_Player.aModel[nCntPlayer].nIdxModelParent);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.x);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.y);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.z);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.x);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.y);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.z);//�ǂݍ���
		}

		//�t�@�C���ǂݍ���
		fscanf(pFile, "%d", &g_Player.nMaxAnimNum);

		for (int nCntPlayerAnim = 0; nCntPlayerAnim < g_Player.nMaxPartsNum; nCntPlayerAnim++)
		{
			//�t���[����
			fscanf(pFile, "%d", &g_Player.nAnimloop[nCntPlayerAnim]);

			//�L�[��
			fscanf(pFile, "%d", &g_Player.nAnimKey[nCntPlayerAnim]);

			for (int nCntPlayerAnimKey = 0; nCntPlayerAnimKey < g_Player.nAnimKey[nCntPlayerAnim]; nCntPlayerAnimKey++)
			{
				fscanf(pFile, "%d", &g_Player.nAnimfram[nCntPlayerAnim][nCntPlayerAnimKey]);//�ǂݍ���

				for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
				{
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].x);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].y);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].z);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].x);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].y);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].z);		//�ǂݍ���
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
	for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX
		(
			&g_Player.aModel[nCntPlayer].FileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntPlayer].pBuffMatModel,
			NULL,
			&g_Player.aModel[nCntPlayer].nNumMatModel,
			&g_Player.aModel[nCntPlayer].pMeshModel
		);
	}

	//�e�̏������ݒ�
	g_Player.nIdxShadow = SetShadow(g_Player.pos,g_Player.rot,15,15);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// ���b�V���̊J��
		if (g_Player.aModel[nCount].pMeshModel != NULL)
		{
			g_Player.aModel[nCount].pMeshModel->Release();
			g_Player.aModel[nCount].pMeshModel = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// �}�e���A���̊J��
		if (g_Player.aModel[nCount].pBuffMatModel != NULL)
		{
			g_Player.aModel[nCount].pBuffMatModel->Release();
			g_Player.aModel[nCount].pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	//�J�����̏��
	Camera *pCamera = GetCamera();

	//�S�̎擾
	Enemy *pEnemy = GetEnemy();

	//�t���[���J�E���g
	g_nCntTimePlayer++;

	//�O��̈ʒu��ۑ�
	g_Player.posOld = g_Player.pos;

	float nSpeed = 5.0f;	//���x
	//float fDiffAngle;

	//�ǂ̂����蔻��
	if (g_Player.pos.z >= 200)
	{//��
		g_Player.pos.z = 200;
	}
	if (g_Player.pos.z <= -4200)
	{//��
		g_Player.pos.z = -4200;
	}
	if (g_Player.pos.x >= 4200)
	{//�E
		g_Player.pos.x = 4200;
	}
	if (g_Player.pos.x <= -200)
	{//��
		g_Player.pos.x = -200;
	}

	//�ړ�����
	if (GetKeyboardPress(DIK_W) == true)
	{//���̏�							����ړ�
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * -0.75f) + pCamera->rot.y);

			if (g_Player.nAnimnow != PLAYERANIM_WALK)
			{//�����A�j���[�V����
				g_Player.nAnimnow = PLAYERANIM_WALK;
				g_nCntTimePlayer = 0;
				g_Player.nAnimKeynow = 0;
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * 0.75f) + pCamera->rot.y);

			if (g_Player.nAnimnow != PLAYERANIM_WALK)
			{//�����A�j���[�V����
				g_Player.nAnimnow = PLAYERANIM_WALK;
				g_nCntTimePlayer = 0;
				g_Player.nAnimKeynow = 0;
			}
		}
		else
		{
			g_Player.move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * -1.0f) + pCamera->rot.y);

			if (g_Player.nAnimnow != PLAYERANIM_WALK)
			{//�����A�j���[�V����
				g_Player.nAnimnow = PLAYERANIM_WALK;
				g_nCntTimePlayer = 0;
				g_Player.nAnimKeynow = 0;
			}
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//���̉�							 ����ړ�
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * -0.25f) + pCamera->rot.y);

			if (g_Player.nAnimnow != PLAYERANIM_WALK)
			{//�����A�j���[�V����
				g_Player.nAnimnow = PLAYERANIM_WALK;
				g_nCntTimePlayer = 0;
				g_Player.nAnimKeynow = 0;
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * 0.25f) + pCamera->rot.y);

			if (g_Player.nAnimnow != PLAYERANIM_WALK)
			{//�����A�j���[�V����
				g_Player.nAnimnow = PLAYERANIM_WALK;
				g_nCntTimePlayer = 0;
				g_Player.nAnimKeynow = 0;
			}
		}
		else
		{
			g_Player.move.x += sinf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * 0.0f) + pCamera->rot.y);

			if (g_Player.nAnimnow != PLAYERANIM_WALK)
			{//�����A�j���[�V����
				g_Player.nAnimnow = PLAYERANIM_WALK;
				g_nCntTimePlayer = 0;
				g_Player.nAnimKeynow = 0;
			}
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//���̉E							�� �E�ړ�
		g_Player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* MODEL_SPEED;
		//���̕����Ɍ���
		g_Player.rot.y = ((D3DX_PI * -0.5f) + pCamera->rot.y);

		if (g_Player.nAnimnow != PLAYERANIM_WALK)
		{//�����A�j���[�V����
			g_Player.nAnimnow = PLAYERANIM_WALK;
			g_nCntTimePlayer = 0;
			g_Player.nAnimKeynow = 0;
		}
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{//���̍�							 �� ���ړ�
		g_Player.move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player.move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		//���̕����Ɍ���
		g_Player.rot.y = ((D3DX_PI * 0.5f) + pCamera->rot.y);

		if (g_Player.nAnimnow != PLAYERANIM_WALK)
		{//�����A�j���[�V����
			g_Player.nAnimnow = PLAYERANIM_WALK;
			g_nCntTimePlayer = 0;
			g_Player.nAnimKeynow = 0;
		}
	}
	else if (GetJoyPadPress(DIJS_BUTTON_10,0) == true || GetJoyPadPress(DIJS_BUTTON_11, 0) == true || GetJoyPadPress(DIJS_BUTTON_12, 0) == true || GetJoyPadPress(DIJS_BUTTON_13, 0) == true)
	{//�W���C�R��
		g_Player.pos.x -= sinf(pCamera->fAngle - GetJotPadRightStick(0)) * PLAYER1_SPEED;
		g_Player.pos.z -= cosf(pCamera->fAngle - GetJotPadRightStick(0)) * PLAYER1_SPEED;

		g_Player.rot.y = pCamera->fAngle - GetJotPadRightStick(0);
		
		if (g_Player.nAnimnow != PLAYERANIM_WALK)
		{//�����A�j���[�V����
			g_Player.nAnimnow = PLAYERANIM_WALK;
			g_nCntTimePlayer = 0;
			g_Player.nAnimKeynow = 0;
		}
	}
	else
	{
		if (g_Player.nAnimnow != PLAYERANIM_NEUTRAL)
		{//�ҋ@���[�V����
			g_Player.nAnimnow = PLAYERANIM_NEUTRAL;
			g_nCntTimePlayer = 0;
			g_Player.nAnimKeynow = 0;
		}
	}

	//�ʒu���ړ��ɑ��
	g_Player.pos += g_Player.move;

	//����������
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.2f;

	//�e�����Ă���
	SetPositionShadow(g_Player.nIdxShadow, g_Player.pos,g_Player.rot);

	//�����蔻��
	CollisionObject(&g_Player.pos, &g_Player.posOld, &g_Player.move);
	CollisionEnemy(&g_Player.pos, &g_Player.posOld, &g_Player.move);

	//�����̃��[�J���ϐ�
	float fDes;
	float frac;

	//�L�[��i�߂�I
	if (g_nCntTimePlayer % g_Player.nAnimfram[g_Player.nAnimnow][g_Player.nAnimKeynow] == 0)
	{
		g_nCntTimePlayer = 0;
		g_Player.nAnimKeynow = (g_Player.nAnimKeynow + 1) % g_Player.nAnimKey[g_Player.nAnimnow];
	}

	//�����̌v�Z
	frac = (g_Player.nAnimfram[g_Player.nAnimnow][g_Player.nAnimKeynow] - g_nCntTimePlayer) * 1.0f;

	//�A�j���[�V����
	for (int nCntPlayerAnim = 0; nCntPlayerAnim < g_Player.nMaxPartsNum; nCntPlayerAnim++)
	{
		//===================
		// X�̊p�x
		//===================

		//�ړI�̊p�x������ׂ�
		g_Player.aModel[nCntPlayerAnim].rotDest = g_Player.aModel[nCntPlayerAnim].rotAnim[g_Player.nAnimnow][g_Player.nAnimKeynow];

		//x�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].rotDest.x > D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].rotDest.x -= D3DX_PI * 2.0f;
		}
		//x�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].rotDest.x < -D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].rotDest.x += D3DX_PI * 2.0f;
		}

		//
		fDes = g_Player.aModel[nCntPlayerAnim].rotDest.x - g_Player.aModel[nCntPlayerAnim].InitRot.x;

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
		g_Player.aModel[nCntPlayerAnim].InitRot.x += fDes / frac;

		//x�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].InitRot.x > D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].InitRot.x -= D3DX_PI * 2.0f;
		}
		//x�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].InitRot.x < -D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].InitRot.x += D3DX_PI * 2.0f;
		}

		//===================
		// Y�̊p�x
		//===================

		//y�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].rotDest.y > D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].rotDest.y -= D3DX_PI * 2.0f;
		}
		//y�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].rotDest.y < -D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].rotDest.y += D3DX_PI * 2.0f;
		}

		//
		fDes = g_Player.aModel[nCntPlayerAnim].rotDest.y - g_Player.aModel[nCntPlayerAnim].InitRot.y;

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
		g_Player.aModel[nCntPlayerAnim].InitRot.y += fDes / frac;

		//x�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].InitRot.y > D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].InitRot.y -= D3DX_PI * 2.0f;
		}
		//x�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].InitRot.y < -D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].InitRot.y += D3DX_PI * 2.0f;
		}

		//===================
		// Z�̊p�x
		//===================

		//z�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].rotDest.z > D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].rotDest.z -= D3DX_PI * 2.0f;
		}
		//z�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].rotDest.z < -D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].rotDest.z += D3DX_PI * 2.0f;
		}

		//
		fDes = g_Player.aModel[nCntPlayerAnim].rotDest.z - g_Player.aModel[nCntPlayerAnim].InitRot.z;

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
		g_Player.aModel[nCntPlayerAnim].InitRot.z += fDes / frac;

		//x�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].InitRot.z > D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].InitRot.z -= D3DX_PI * 2.0f;
		}
		//x�ړI�̈ʒu�̒���
		if (g_Player.aModel[nCntPlayerAnim].InitRot.z < -D3DX_PI)
		{
			g_Player.aModel[nCntPlayerAnim].InitRot.z += D3DX_PI * 2.0f;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;						//

	{//�v���C���[
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.mtxWorldPlayer);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxRot);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorldPlayer);
	}
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player.aModel[nCntParts].nIdxModelParent < 0)
		{//�e���f��
			mtxParent = g_Player.mtxWorldPlayer;
		}
		else
		{//�q���f��
			mtxParent = g_Player.aModel[g_Player.aModel[nCntParts].nIdxModelParent].mtxWorldModel;
		}
		{//�e���f��
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorldModel);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_Player.aModel[nCntParts].InitRot.y,
				g_Player.aModel[nCntParts].InitRot.x,
				g_Player.aModel[nCntParts].InitRot.z
			);
			D3DXMatrixMultiply
			(
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&mtxRot
			);
			// �ʒu�𔽉f
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_Player.aModel[nCntParts].InitPos.x,
				g_Player.aModel[nCntParts].InitPos.y,
				g_Player.aModel[nCntParts].InitPos.z
			);
			D3DXMatrixMultiply
			(
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&mtxTrans
			);

			D3DXMatrixMultiply
			(
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&mtxParent
			);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorldModel);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMatModel->GetBufferPointer();

			// �|���S���̕`��
			if (g_Player.bUse == true)
			{
				for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMatModel; nCntMat++)
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// �e�N�X�`����NULL�ɂ���
					pDevice->SetTexture(0, NULL);

					//pDevice->SetTexture(0, g_Player.nNumMatPlayer);

					// �v���C���[(�p�[�c)�̕`��
					g_Player.aModel[nCntParts].pMeshModel->DrawSubset(nCntMat);
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
Player *GetPlayer(void)
{
	return &g_Player;
}
