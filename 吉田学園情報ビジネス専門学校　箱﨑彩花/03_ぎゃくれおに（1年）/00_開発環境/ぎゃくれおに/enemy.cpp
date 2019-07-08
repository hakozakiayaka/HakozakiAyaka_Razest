//=============================================================================
//
// �G���� [enemy.cpp]
// Author : �L�n ���u�@���@����
//
//=============================================================================
#include "enemy.h"		//�G
#include "input.h"		//�L�[�{�[�h
#include "camera.h"		//�J����
#include "shadow.h"		//�e
#include "bullet.h"		//�e
#include "object.h"		//�I�u�W�F�N�g
#include "player.h"		//�v���C���[
#include "player2.h"	//�v���C���[�Q
#include "fade.h"		//�t�F�[�h
#include "effect.h"		//�G�t�F�N�g
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME		"data\\MODEL\\�I�j_�X��.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME1		"data\\MODEL\\�I�j_�_���{�[��.x"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME2		"data\\MODEL\\�I�j_�S�~��.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define ENEMYMODEL_SPEED (1.1f)								//�G�X�s�[�h
#define ENEMY_SPEED		(5.5f)								//�G�̃X�s�[�h
#define MAX_ENEMY_TYPE	(3)									//�G�̎��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Enemy g_Enemy[MAX_ENEMY_TYPE];			//�G
float g_fJoyStickAngle;

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(//�X��
		MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy[0].pBuffMatEnemy,
		NULL,
		&g_Enemy[0].nNumMatEnemy,
		&g_Enemy[0].pMeshEnemy
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(//�i�{�[��
		MODEL_NAME1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy[1].pBuffMatEnemy,
		NULL,
		&g_Enemy[1].nNumMatEnemy,
		&g_Enemy[1].pMeshEnemy
	);
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(//�S�~��
		MODEL_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy[2].pBuffMatEnemy,
		NULL,
		&g_Enemy[2].nNumMatEnemy,
		&g_Enemy[2].pMeshEnemy
	);

	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE * pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	for (int nCount = 0; nCount < MAX_ENEMY_TYPE; nCount++)
	{
		g_Enemy[nCount].posOld = D3DXVECTOR3(0, 0, 0);
		g_Enemy[nCount].nCntPlayer = 2;
		g_Enemy[nCount].pos = D3DXVECTOR3(2000, 20, -4100);
		g_Enemy[nCount].rot = D3DXVECTOR3(0, 0, 0);
		g_Enemy[nCount].move = D3DXVECTOR3(0, 0, 0);
		g_Enemy[nCount].bUse = false;

		//�ő�l�ƍŏ��l
		g_Enemy[nCount].vtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
		g_Enemy[nCount].vtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);

		//���_�����擾
		nNumVtx = g_Enemy[nCount].pMeshEnemy->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y
		sizeFVF = D3DXGetFVFVertexSize(g_Enemy[nCount].pMeshEnemy->GetFVF());

		//���_�t�H�[�}�b�g�����b�N
		g_Enemy[nCount].pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{	//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

			//�ŏ��l
			if (vtx.x < g_Enemy[nCount].vtxMinModel.x)
			{
				g_Enemy[nCount].vtxMinModel.x = vtx.x;
			}
			if (vtx.z < g_Enemy[nCount].vtxMinModel.z)
			{
				g_Enemy[nCount].vtxMinModel.z = vtx.z;
			}

			//�ő�l
			if (vtx.x > g_Enemy[nCount].vtxMaxModel.x)
			{
				g_Enemy[nCount].vtxMaxModel.x = vtx.x;
			}
			if (vtx.z > g_Enemy[nCount].vtxMaxModel.z)
			{
				g_Enemy[nCount].vtxMaxModel.z = vtx.z;
			}

			pVtxBuff += sizeFVF;		//�T�C�Y���|�C���^��i�߂�
		}

		//���_�o�b�t�@���A�����b�N
		g_Enemy[nCount].pMeshEnemy->UnlockVertexBuffer();
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY_TYPE; nCount++)
	{
		// ���b�V���̊J��
		if (g_Enemy[nCount].pMeshEnemy != NULL)
		{
			g_Enemy[nCount].pMeshEnemy->Release();
			g_Enemy[nCount].pMeshEnemy = NULL;
		}
		// �}�e���A���̊J��
		if (g_Enemy[nCount].pBuffMatEnemy != NULL)
		{
			g_Enemy[nCount].pBuffMatEnemy->Release();
			g_Enemy[nCount].pBuffMatEnemy = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	//�J�����̏��
	Camera *pCamera = GetCamera();

	//�v���C���[�̎擾
	Player * pPlayer = GetPlayer();

	//�v���C���[2�̎擾
	Player2 * pPlayer2 = GetPlayer2();

	//�t�F�[�h���擾
	FADE pFade = GetFade();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (int nCount = 0; nCount < MAX_ENEMY_TYPE; nCount++)
	{
		if (GetKeyboardTrigger(DIK_NUMPAD7) == true || GetJoyPadTrigger(0, 2) == true)
		{
			//�G�t�F�N�g
			SetParticleEffect(g_Enemy[nCount].pos, EFFECTTYPE_EXPLOSION2, 50, 30, 5, 0);

			PlaySound(SOUND_LABEL_SE_HENNSIN);
			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX
			(
				MODEL_NAME,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCount].pBuffMatEnemy,
				NULL,
				&g_Enemy[nCount].nNumMatEnemy,
				&g_Enemy[nCount].pMeshEnemy
			);
		}
		else if (GetKeyboardTrigger(DIK_NUMPAD8) == true || GetJoyPadTrigger(1, 2) == true)
		{
			//�G�t�F�N�g
			SetParticleEffect(g_Enemy[nCount].pos, EFFECTTYPE_EXPLOSION2, 50, 30, 5, 0);

			PlaySound(SOUND_LABEL_SE_HENNSIN);
			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX
			(
				MODEL_NAME1,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCount].pBuffMatEnemy,
				NULL,
				&g_Enemy[nCount].nNumMatEnemy,
				&g_Enemy[nCount].pMeshEnemy
			);
		}
		else if (GetKeyboardTrigger(DIK_NUMPAD9) == true || GetJoyPadTrigger(2, 2) == true)
		{
			//�G�t�F�N�g
			SetParticleEffect(g_Enemy[nCount].pos, EFFECTTYPE_EXPLOSION2, 50, 30, 5, 0);

			PlaySound(SOUND_LABEL_SE_HENNSIN);
			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX
			(
				MODEL_NAME2,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCount].pBuffMatEnemy,
				NULL,
				&g_Enemy[nCount].nNumMatEnemy,
				&g_Enemy[nCount].pMeshEnemy
			);
		}
		
		//�O��̈ʒu��ۑ�
		g_Enemy[nCount].posOld = g_Enemy[nCount].pos;

		//�ǂ̂����蔻��
		if (g_Enemy[nCount].pos.z >= 200)
		{//��
			g_Enemy[nCount].pos.z = 200;
		}
		if (g_Enemy[nCount].pos.z <= -4200)
		{//��
			g_Enemy[nCount].pos.z = -4200;
		}
		if (g_Enemy[nCount].pos.x >= 4200)
		{//�E
			g_Enemy[nCount].pos.x = 4200;
		}
		if (g_Enemy[nCount].pos.x <= -200)
		{//��
			g_Enemy[nCount].pos.x = -200;
		}

		//�ړ�����
		if (GetKeyboardPress(DIK_UP) == true)
		{//���̏�							����ړ�
			if (GetKeyboardPress(DIK_RIGHT) == true)
			{
				g_Enemy[nCount].move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//���̕����Ɍ���
				g_Enemy[nCount].rot.y = ((D3DX_PI * -0.75f) + pCamera->rot.y);
			}
			else if (GetKeyboardPress(DIK_LEFT) == true)
			{
				g_Enemy[nCount].move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//���̕����Ɍ���
				g_Enemy[nCount].rot.y = ((D3DX_PI * 0.75f) + pCamera->rot.y);
			}
			else
			{
				g_Enemy[nCount].move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//���̕����Ɍ���
				g_Enemy[nCount].rot.y = ((D3DX_PI * -1.0f) + pCamera->rot.y);
			}
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//���̉�							 ����ړ�
			if (GetKeyboardPress(DIK_RIGHT) == true)
			{
				g_Enemy[nCount].move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//���̕����Ɍ���
				g_Enemy[nCount].rot.y = ((D3DX_PI * -0.25f) + pCamera->rot.y);
			}
			else if (GetKeyboardPress(DIK_LEFT) == true)
			{
				g_Enemy[nCount].move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//���̕����Ɍ���
				g_Enemy[nCount].rot.y = ((D3DX_PI * 0.25f) + pCamera->rot.y);
			}
			else
			{
				g_Enemy[nCount].move.x += sinf((-D3DX_PI * 1.0f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((-D3DX_PI * 1.0f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//���̕����Ɍ���
				g_Enemy[nCount].rot.y = ((D3DX_PI * 0.0f) + pCamera->rot.y);
			}
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{//���̉E							�� �E�ړ�
			g_Enemy[nCount].move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
			g_Enemy[nCount].move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* ENEMYMODEL_SPEED;
			//���̕����Ɍ���
			g_Enemy[nCount].rot.y = ((D3DX_PI * -0.5f) + pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{//���̍�							 �� ���ړ�
			g_Enemy[nCount].move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
			g_Enemy[nCount].move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
			//���̕����Ɍ���
			g_Enemy[nCount].rot.y = ((D3DX_PI * 0.5f) + pCamera->rot.y);
		}
		else if (GetJoyPadPress(DIJS_BUTTON_10, 2) == true || GetJoyPadPress(DIJS_BUTTON_11, 2) == true || GetJoyPadPress(DIJS_BUTTON_12, 2) == true || GetJoyPadPress(DIJS_BUTTON_13, 2) == true)
		{//�W���C�R��
			g_Enemy[nCount].pos.x -= sinf(pCamera->fAngle - GetJotPadRightStick(2)) * ENEMY_SPEED;
			g_Enemy[nCount].pos.z -= cosf(pCamera->fAngle - GetJotPadRightStick(2)) * ENEMY_SPEED;

			g_Enemy[nCount].rot.y = pCamera->fAngle - GetJotPadRightStick(2);
		}

		//�ʒu���ړ��ɑ��
		g_Enemy[nCount].pos += g_Enemy[nCount].move;

		//����������
		g_Enemy[nCount].move.x += (0.0f - g_Enemy[nCount].move.x) * 0.2f;
		g_Enemy[nCount].move.z += (0.0f - g_Enemy[nCount].move.z) * 0.2f;

		//�����蔻��
		CollisionObject(&g_Enemy[nCount].pos, &g_Enemy[nCount].posOld, &g_Enemy[nCount].move);

		//�I�u�W�F�N�g�̂����蔻��
		CollisionObject(&g_Enemy[nCount].pos, &g_Enemy[nCount].posOld, &g_Enemy[nCount].move);


		if (pPlayer->nCntPlayer <= 0 && pPlayer2->nCntPlayer2 <= 0)
		{	//�v���C���[1�ƃv���C���[2���߂܂�����Q�[���I�[�o�[
			if (pFade != FADE_OUT)
			{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
				//���[�h�ݒ�
				SetGameState(GAMESTATE_OVER);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�m�Ԓ�kk��
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCount = 0; nCount < MAX_ENEMY_TYPE; nCount++)
	{
		if (nCount == 0)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[nCount].mtxWorldEnemy);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCount].rot.y, g_Enemy[nCount].rot.x, g_Enemy[nCount].rot.z);

			D3DXMatrixMultiply(&g_Enemy[nCount].mtxWorldEnemy, &g_Enemy[nCount].mtxWorldEnemy, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCount].pos.x, g_Enemy[nCount].pos.y, g_Enemy[nCount].pos.z);

			D3DXMatrixMultiply(&g_Enemy[nCount].mtxWorldEnemy, &g_Enemy[nCount].mtxWorldEnemy, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐�3��
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCount].mtxWorldEnemy);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Enemy[nCount].pBuffMatEnemy->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCount].nNumMatEnemy; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`����NULL�ɂ���
				pDevice->SetTexture(0, NULL);

				//pDevice->SetTexture(0, g_Enemy[].nNumMatEnemy);

				// �G(�p�[�c)�̕`��
				g_Enemy[nCount].pMeshEnemy->DrawSubset(nCntMat);
			}
		}
	}
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}
//=============================================================================
// �v���C���[�̓����蔻��	 �i�v���C���[1�j
//=============================================================================
bool CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3  * pPosOld, D3DXVECTOR3  * pMove)
{
	//�v���C���[�̎擾
	Player *pPlayer = GetPlayer();

	bool bLand = false;						//�ŏ��͕߂܂��ĂȂ����

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY_TYPE; nCntEnemy++)
	{
		if (pPlayer->bUse == true)
		{
			bLand = false;

			if (g_Enemy[nCntEnemy].pos.x > pPlayer->pos.x - 20
				&& g_Enemy[nCntEnemy].pos.x < pPlayer->pos.x + 20
				&& g_Enemy[nCntEnemy].pos.z > pPlayer->pos.z - 20
				&& g_Enemy[nCntEnemy].pos.z < pPlayer->pos.z + 20)
			{
				pPlayer->nCntPlayer -= 1;
				bLand = true;								//�߂܂�����Ԃɂ���
				pPlayer->bUse = false;
				//�g���Ă���e��false
				DeleteShadow(pPlayer->nIdxShadow);

				PlaySound(SOUND_LABEL_SE_BUTUKARU);
				//�G�t�F�N�g
				SetParticleEffect(pPlayer->pos, EFFECTTYPE_EXPLOSION, 200, 10, 5, 0);
				break;										//�߂܂�����if��������
			}
		}
	}

	return bLand;
}

//=============================================================================
// �v���C���[2�̓����蔻��	�i�v���C���[2�j
//=============================================================================
bool CollisionEnemy2(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	//�v���C���[2�̎擾
	Player2 *pPlayer2 = GetPlayer2();

	Enemy *pEnemy = GetEnemy();

	bool bLand = false;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY_TYPE; nCntEnemy++)
	{
		if (pPlayer2->bUse == true)
		{
			if (g_Enemy[nCntEnemy].pos.x > pPlayer2->pos.x - 20
				&& g_Enemy[nCntEnemy].pos.x < pPlayer2->pos.x + 20
				&& g_Enemy[nCntEnemy].pos.z > pPlayer2->pos.z - 20
				&& g_Enemy[nCntEnemy].pos.z < pPlayer2->pos.z + 20)
			{
				pPlayer2->nCntPlayer2 -= 1;
				bLand = true;								//�߂܂�����Ԃɂ���
				pPlayer2->bUse = false;
				//�g���Ă���e��false
				DeleteShadow(pPlayer2->nIdxShadow2);

				PlaySound(SOUND_LABEL_SE_BUTUKARU);
				//�G�t�F�N�g
				SetParticleEffect(pPlayer2->pos, EFFECTTYPE_EXPLOSION, 200, 10, 5, 0);
				break;										//�߂܂�����if��������
			}
		}
	}
	return bLand;

}
//=========================================================================================================================
// �G�̎擾����
//=========================================================================================================================
Enemy *GetEnemy(void)
{
	return &g_Enemy[0];
}
