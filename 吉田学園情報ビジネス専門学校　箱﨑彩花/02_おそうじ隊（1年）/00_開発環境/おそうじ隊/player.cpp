//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "player.h"			//�v���C���[
#include "input.h"			//�L�[�{�[�h
#include "camera.h"		//�J����
#include "shadow.h"		//�e
#include "bullet.h"			//�e
#include "score.h"			//�X�R�A
#include "meshField.h"	//���b�V���t�B�[���h
#include "model.h"			//���f��
#include "life.h"				//���C�t
#include "explosion.h"		//����
#include "game.h"			//�Q�[��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME			"data\\MODEL\\j_body.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME2			"data\\MODEL\\j_head.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME3			"data\\MODEL\\j_arm_Right.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME4			"data\\MODEL\\j_hand_Right.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME5			"data\\MODEL\\j_arm_Left.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME6			"data\\MODEL\\j_hand_Left.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME7			"data\\MODEL\\j_thigh_Right.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME8			"data\\MODEL\\j_shin_Right.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME9			"data\\MODEL\\j_foot_Right.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME10		"data\\MODEL\\j_thigh_Left.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME11		"data\\MODEL\\j_shin_Left.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME12		"data\\MODEL\\j_foot_Left.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME13		"data\\MODEL\\zoukin.x"			//�ǂݍ��ރe�N�X�`���t�@�C��

#define MAX_PARTS				(13)
#define MODEL_SPEED			(1.0f)								//�v���C���[�X�s�[�h
#define DAMAGE_STATE		(7)									//�_���[�W���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Player g_Player;						//�v���C���[
int g_nIdxPlayerShadow;			//�ǂ̉e���g���Ă��邩
int g_nCount1;							//���[�V�����J�E���g

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nNumVtx;															//���_��
	DWORD sizeFVF;													//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;														//���_�o�b�t�@�ւ̃|�C���^

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[0].pBuffMatModel,
		NULL,
		&g_Player.aModel[0].nNumMatModel,
		&g_Player.aModel[0].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[1].pBuffMatModel,
		NULL,
		&g_Player.aModel[1].nNumMatModel,
		&g_Player.aModel[1].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[2].pBuffMatModel,
		NULL,
		&g_Player.aModel[2].nNumMatModel,
		&g_Player.aModel[2].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME4,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[3].pBuffMatModel,
		NULL,
		&g_Player.aModel[3].nNumMatModel,
		&g_Player.aModel[3].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME5,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[4].pBuffMatModel,
		NULL,
		&g_Player.aModel[4].nNumMatModel,
		&g_Player.aModel[4].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME6,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[5].pBuffMatModel,
		NULL,
		&g_Player.aModel[5].nNumMatModel,
		&g_Player.aModel[5].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME7,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[6].pBuffMatModel,
		NULL,
		&g_Player.aModel[6].nNumMatModel,
		&g_Player.aModel[6].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME8,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[7].pBuffMatModel,
		NULL,
		&g_Player.aModel[7].nNumMatModel,
		&g_Player.aModel[7].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME9,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[8].pBuffMatModel,
		NULL,
		&g_Player.aModel[8].nNumMatModel,
		&g_Player.aModel[8].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME10,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[9].pBuffMatModel,
		NULL,
		&g_Player.aModel[9].nNumMatModel,
		&g_Player.aModel[9].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME11,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[10].pBuffMatModel,
		NULL,
		&g_Player.aModel[10].nNumMatModel,
		&g_Player.aModel[10].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME12,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[11].pBuffMatModel,
		NULL,
		&g_Player.aModel[11].nNumMatModel,
		&g_Player.aModel[11].pMeshModel
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		MODEL_NAME13,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Player.aModel[12].pBuffMatModel,
		NULL,
		&g_Player.aModel[12].nNumMatModel,
		&g_Player.aModel[12].pMeshModel
	);

	// �ʒu�E�����̏����ݒ�
	g_Player.pos = D3DXVECTOR3(100, 25, -500);
	g_Player.rot = D3DXVECTOR3(0, 0, 0);
	g_Player.move = D3DXVECTOR3(0, 0, 0);
	g_nCount1 = 0;
	g_Player.vtxMinPlayer = D3DXVECTOR3(10000, 10000, 10000);
	g_Player.vtxMaxPlayer = D3DXVECTOR3(-10000, -10000, -10000);
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.bDisp = true;
	g_Player.nCntState = 0;
	g_Player.nLife = PLAYER_LIFE;
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�̔ԍ�
	g_Player.aModel[0].nIdxModelParent = -1;					//��
	g_Player.aModel[1].nIdxModelParent =  0;					//��
	g_Player.aModel[2].nIdxModelParent =  0;					//�E�r
	g_Player.aModel[3].nIdxModelParent =  2;					//�E��
	g_Player.aModel[4].nIdxModelParent =  0;					//���r
	g_Player.aModel[5].nIdxModelParent =  4;					//����
	g_Player.aModel[6].nIdxModelParent =  0;					//�E����
	g_Player.aModel[7].nIdxModelParent = 6;						//�E����
	g_Player.aModel[8].nIdxModelParent =  7;					//�E��
	g_Player.aModel[9].nIdxModelParent =  0;					//������
	g_Player.aModel[10].nIdxModelParent = 9;					//������
	g_Player.aModel[11].nIdxModelParent =  10;				//����
	g_Player.aModel[12].nIdxModelParent = 3;					//�G��				�E��ɂ���

	//���f���e�ƃR���h��pos�̈ʒu
	g_Player.aModel[0].posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//��
	g_Player.aModel[1].posModel = D3DXVECTOR3(0.0f, 28.0f, 0.0f);			//��
	g_Player.aModel[2].posModel = D3DXVECTOR3(-8.0f, 21.0f, 0.0f);			//�E�r
	g_Player.aModel[3].posModel = D3DXVECTOR3(-20.0f, 0.0f, 0.0f);			//�E��
	g_Player.aModel[4].posModel = D3DXVECTOR3(8.0f, 21.0f, 0.0f); 			//���r
	g_Player.aModel[5].posModel = D3DXVECTOR3(20.0f, 0.0f, 0.0f);			//����
	g_Player.aModel[6].posModel = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);			//�E����
	g_Player.aModel[7].posModel = D3DXVECTOR3(-0.5f, -15.0f, 0.0f);		//�E����
	g_Player.aModel[8].posModel = D3DXVECTOR3(0.0f, -12.0f, 0.0f);			//�E��
	g_Player.aModel[9].posModel = D3DXVECTOR3(4.0f, 0.0f, 0.0f);				//������
	g_Player.aModel[10].posModel = D3DXVECTOR3(0.5f, -15.0f, 0.0f);		//������
	g_Player.aModel[11].posModel = D3DXVECTOR3(0.0f, -12.0f, 0.0f);		//����
	g_Player.aModel[12].posModel = D3DXVECTOR3(1.5f, -12.0f, 0.0f);		//�G��

	//���f���e�ƃR���h��rot�̈ʒu
	g_Player.aModel[0].rotModel = D3DXVECTOR3(-1.94f, -0.19f, 0.0f);			//��
	g_Player.aModel[1].rotModel = D3DXVECTOR3(0.81f, -0.16f, 0.0f);				//��
	g_Player.aModel[2].rotModel = D3DXVECTOR3(2.7f, -0.0f, 1.25f);			//�E�r
	g_Player.aModel[3].rotModel = D3DXVECTOR3(0.0f, -0.12f, 0.0f);				//�E��
	g_Player.aModel[4].rotModel = D3DXVECTOR3(2.7f, 0.0f, -1.56f); 			//���r
	g_Player.aModel[5].rotModel = D3DXVECTOR3(0.0f, 0.02f, 0.0f);				//����
	g_Player.aModel[6].rotModel = D3DXVECTOR3(0.89f, 0.0f, -0.03f);				//�E����
	g_Player.aModel[7].rotModel = D3DXVECTOR3(-0.28f, 0.0f, 0.0f);				//�E����
	g_Player.aModel[8].rotModel = D3DXVECTOR3(0.28f, 0.0f, 0.0f);				//�E��
	g_Player.aModel[9].rotModel = D3DXVECTOR3(2.14f, 0.0f, 0.0f);				//������
	g_Player.aModel[10].rotModel = D3DXVECTOR3(2.04f, -1.29f, 1.45f);			//������
	g_Player.aModel[11].rotModel = D3DXVECTOR3(0.13f, -2.67f, -0.09f);		//����
	g_Player.aModel[12].rotModel = D3DXVECTOR3(0.0f, -2.1f, 1.5f);				//�G��

	//���_�����擾
	nNumVtx = g_Player.aModel[0].pMeshModel->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y
	sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[0].pMeshModel->GetFVF());

	//���_�t�H�[�}�b�g�����b�N
	g_Player.aModel[0].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{	//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

		//�ŏ��l
		if (vtx.x < g_Player.vtxMinPlayer.x)
		{
			g_Player.vtxMinPlayer.x = vtx.x;
		}
		if (vtx.z < g_Player.vtxMinPlayer.z)
		{
			g_Player.vtxMinPlayer.z = vtx.z;
		}

		//�ő�l
		if (vtx.x > g_Player.vtxMaxPlayer.x)
		{
			g_Player.vtxMaxPlayer.x = vtx.x;
		}
		if (vtx.z > g_Player.vtxMaxPlayer.z)
		{
			g_Player.vtxMaxPlayer.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_Player.aModel[0].pMeshModel->UnlockVertexBuffer();

	g_nIdxPlayerShadow = SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30, 30);
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
	MESHFIELD * pMeshField = GetMeshField();

	//�O��̈ʒu��ۑ�
	g_Player.posOld = g_Player.pos;

	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMADE:
		g_Player.nCntState--;
		if (g_Player.nCntState <= 0)
		{
			g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		break;

	case PLAYERSTATE_DEATH:
		g_Player.nCntState--;
		return;
		break;
	}

	float nSpeed = 5.0f;	//���x
	//float fDifrot.y;

	//�ړ��͈͂̔���
	if (g_Player.pos.z > pMeshField->pos.z + 95)			//�v���C���[��pos����ǂ̋���������
	{	//��
		g_Player.pos.z = pMeshField->pos.z + 95;
	}
	if (g_Player.pos.z < pMeshField->pos.z - 895)
	{	//��O
		g_Player.pos.z = pMeshField->pos.z - 895;
	}
	if (g_Player.pos.x > pMeshField->pos.x + 895)
	{	//�E
		g_Player.pos.x = pMeshField->pos.x + 895;
	}
	if (g_Player.pos.x < pMeshField->pos.x - 95)
	{	//��
		g_Player.pos.x = pMeshField->pos.x - 95;
	}

	//fDifrot.y = (pCamera->rot.y + D3DX_PI) - g_Player.rot.y;
	//if (fDifrot.y > D3DX_PI)
	//{
	//	fDifrot.y -= D3DX_PI * 2.0;
	//}
	//else if (fDifrot.y < -D3DX_PI)
	//{
	//	fDifrot.y += D3DX_PI * 2.0;
	//}

	//g_Player.rot.y += fDifrot.y * 0.4f;

	//if (g_Player.rot.y > D3DX_PI)
	//{
	//	fDifrot.y -= D3DX_PI * 2.0;
	//}
	//else if (g_Player.rot.y < -D3DX_PI)
	//{
	//	fDifrot.y += D3DX_PI * 2.0;
	//}

	//�ړ�����
	if (GetKeyboardPress(DIK_UP) == true)
	{//���̏�							����ړ�
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * -0.75f) + pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * 0.75f) + pCamera->rot.y);
		}
		else
		{
			g_Player.move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * -1.0f) + pCamera->rot.y);
		}
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//���̉�							 ����ړ�
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * -0.25f) + pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * 0.25f) + pCamera->rot.y);
		}
		else
		{
			g_Player.move.x += sinf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * 0.0f) + pCamera->rot.y);
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//���̉E							�� �E�ړ�
		g_Player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* MODEL_SPEED;
		//���̕����Ɍ���
		g_Player.rot.y = ((D3DX_PI * -0.5f) + pCamera->rot.y);
	}
	else if (GetKeyboardPress(DIK_LEFT) == true)
	{//���̍�							 �� ���ړ�
		g_Player.move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player.move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		//���̕����Ɍ���
		g_Player.rot.y = ((D3DX_PI * 0.5f) + pCamera->rot.y);
	}
	if (GetKeyboardPress(DIK_T) == true)
	{//��ړ�			
		g_Player.pos.y += 0.3f;
	}
	if (GetKeyboardPress(DIK_G) == true)
	{//���ړ�						
		g_Player.pos.y -= 0.3f;
	}
	//�ʒu���ړ��ɑ��
	g_Player.pos += g_Player.move;

	//����������
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.2f;

	////�e����
	//if (GetKeyboardTrigger(DIK_SPACE) == true)
	//{
	//	SetBullet(g_Player.pos, g_Player.rot, BULLETTYPE_PLAYER);
	//}

	//�����蔻��
	CollisionModel(&g_Player.pos, &g_Player.posOld);

	//�e�̈ʒu�ݒ�
	SetPositionShadow(g_nIdxPlayerShadow, g_Player.pos);
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

	if (g_Player.bDisp == true)
	{
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
					g_Player.aModel[nCntParts].rotModel.y,
					g_Player.aModel[nCntParts].rotModel.x,
					g_Player.aModel[nCntParts].rotModel.z
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
					g_Player.aModel[nCntParts].posModel.x,
					g_Player.aModel[nCntParts].posModel.y,
					g_Player.aModel[nCntParts].posModel.z
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
				// �}�e���A�����f�t�H���g�ɖ߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//=============================================================================
// �v���C���[�̃_���[�W���
//=============================================================================
void HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;
	SetLife(g_Player.nLife);

	if (g_Player.nLife <= 0)
	{	//���C�t��0�ɂȂ�����
		SetExplosion(g_Player.pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_Player.state = PLAYERSTATE_DEATH;
		g_Player.nCntState = 5;
		SetGameState(GAMESTATE_OVER);
	}
	else
	{	//���C�t���c���Ă���
		g_Player.state = PLAYERSTATE_DAMADE;
		g_Player.nCntState = DAMAGE_STATE;					//�_���[�W��Ԃ̎���
		g_Player.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
}

//=========================================================================================================================
// �v���C���[�̎擾����
//=========================================================================================================================
Player * GetPlayer(void)
{
	return &g_Player;
}
