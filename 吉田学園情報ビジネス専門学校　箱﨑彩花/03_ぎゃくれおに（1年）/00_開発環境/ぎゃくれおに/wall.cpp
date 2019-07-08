//=============================================================================
//
// �|���S������ [wall.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "wall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WALL_TEXTURE_NAME		"data\\TEXTURE\\�ʍs�~��.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_WALL				(4)									//�ǂ̍ő吔
#define	WALL_SPEED				(0.0003f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//���_�o�b�t�@
LPDIRECT3DTEXTURE9		g_pTextureWall = NULL;	//�e�N�X�`���ւ̃|�C���^
Wall g_Wall[MAX_WALL];							//�ǂ̏��

//=============================================================================
// ����������
//=============================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{//�S�J�E���g����
		g_Wall[nCount].rotWall = D3DXVECTOR3(0, 0, 0);	//����
		g_Wall[nCount].posWall = D3DXVECTOR3(0, 0, 0);	//�ʒu

		g_Wall[nCount].moveWall = D3DXVECTOR3(WALL_SPEED, 0.0f, 0.0f);		//�|���S���ړ��l
		g_Wall[nCount].bUse = false;					//�g�p���Ă��邩�ǂ���
	}

	//���_���
	MakeVertexWall(pDevice);
}
//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureWall != NULL)
		{
			g_pTextureWall->Release();
			g_pTextureWall = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{//�S�J�E���g����

		g_Wall[nCount].posWall += g_Wall[nCount].moveWall;	//�ʒu�̍X�V

		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_Wall[nCount].posWall.x, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_Wall[nCount].posWall.x + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_Wall[nCount].posWall.x, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_Wall[nCount].posWall.x + 1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//�|���S���̕`��
	for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{//�u���b�N���J�E���g
		if (g_Wall[nCount].bUse == true)
		{//�u���b�N������ꍇ

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Wall[nCount].mtxWorldWall);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCount].rotWall.y, g_Wall[nCount].rotWall.x, g_Wall[nCount].rotWall.z);

			D3DXMatrixMultiply(&g_Wall[nCount].mtxWorldWall, &g_Wall[nCount].mtxWorldWall, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCount].posWall.x, g_Wall[nCount].posWall.y, g_Wall[nCount].posWall.z);

			D3DXMatrixMultiply(&g_Wall[nCount].mtxWorldWall, &g_Wall[nCount].mtxWorldWall, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCount].mtxWorldWall);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		WALL_TEXTURE_NAME,
		&g_pTextureWall
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{//�S�J�E���g����
	 //���_��
		pVtx[0].pos = D3DXVECTOR3(-2250, 150, 0);
		pVtx[1].pos = D3DXVECTOR3(2250, 150, 0);
		pVtx[2].pos = D3DXVECTOR3(-2250, 30, 0);
		pVtx[3].pos = D3DXVECTOR3(2250, 30, 0);

		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N����
	g_pVtxBuffWall->Unlock();
}
//=============================================================================
// �ǂ̍쐬
//=============================================================================
void SetWall(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	for (int nCount = 0; nCount < MAX_WALL; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		if (g_Wall[nCount].bUse == false)
		{
			g_Wall[nCount].posWall = pos;			//pos�l���
			g_Wall[nCount].rotWall = rot;			//rot�l���
			g_Wall[nCount].bUse = true;				//�g�p���Ă����Ԃɂ���

			break;
		}
	}
}
