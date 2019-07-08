//=============================================================================
//
// �|���S������ [explosion.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "explosion.h"		//����
#include "shadow.h"			//�e

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EXPLOSION_TEXTURE_NAME		"data\\TEXTURE\\explosion000.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define EXPLOSION_TEXTURE_SPEED		(5)										//�e�N�X�`���A�j���[�V�����X�s�[�h
#define EXPLOSION_TEXTURE_PATTERN	(8)										//�e�N�X�`���A�j���[�V�����p�^�[����
#define EXPLOSION_TEXTURE_UV_U		(0.125f)								//�e�N�X�`���A�j���[�V����U�͈�
#define EXPLOSION_TEXTURE_UV_V		(1.0f)									//�e�N�X�`���A�j���[�V����V�͈�
#define MAX_EXPLOSION				(100)									//�����̍ő吔
	
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	//���_�o�b�t�@
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	//�e�N�X�`���ւ̃|�C���^
Explosion g_Explosion[MAX_EXPLOSION];				//�����̏��

//=============================================================================
// ����������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{//�S�J�E���g����
		g_Explosion[nCount].rotExplosion = D3DXVECTOR3(0, 0, 0);	//����
		g_Explosion[nCount].posExplosion = D3DXVECTOR3(0, 0, 0);	//�ʒu
		g_Explosion[nCount].nCounterAnim = 0;						//�J�E���^�[�����l�ݒ�
		g_Explosion[nCount].nPatteunAnim = 0;						//�p�^�[��No.�����l�ݒ�
		g_Explosion[nCount].bUse = false;							//�g�p���Ă��邩�ǂ���
	}

	//���_���
	MakeVertexExplosion(pDevice);

}
//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	for (int nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureExplosion != NULL)
		{
			g_pTextureExplosion->Release();
			g_pTextureExplosion = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	//�����J�E���g
	int nCntExplosion;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;	

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{//�������J�E���g
		if (g_Explosion[nCntExplosion].bUse == true)
		{//�e���g�p����Ă���
			g_Explosion[nCntExplosion].nCounterAnim++;		//�J�E���^�[���Z

			if ((g_Explosion[nCntExplosion].nCounterAnim % EXPLOSION_TEXTURE_SPEED) == 0)
			{//�A�j���[�V�������x
				g_Explosion[nCntExplosion].nPatteunAnim = (g_Explosion[nCntExplosion].nPatteunAnim + 1) % EXPLOSION_TEXTURE_PATTERN;		//�p�^�[��No.�X�V

				//�e�N�X�`���ݒ�
				pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCntExplosion].nPatteunAnim, 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCntExplosion].nPatteunAnim + EXPLOSION_TEXTURE_UV_U, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCntExplosion].nPatteunAnim, EXPLOSION_TEXTURE_UV_V);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCntExplosion].nPatteunAnim + EXPLOSION_TEXTURE_UV_U, EXPLOSION_TEXTURE_UV_V);

				if (g_Explosion[nCntExplosion].nPatteunAnim == EXPLOSION_TEXTURE_PATTERN - 1)
				{//�A�j���[�V�������Ō�܂ł������ꍇ
					g_Explosion[nCntExplosion].bUse = false;		//�g�p���Ă��Ȃ����
				}
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans,mtxView;		//�v�Z�p�}�g���b�N�X

	//�A���t�@�e�X�g����
	//�f�t�H���g�̏ꍇFALSE�ɂȂ��Ă��邩��TRUE�ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�����̎��͎Q�Ƃ��Ӗ����A�Q�Ƃ����l����l�ɒu��������
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	//�����̎��͏������Ӗ����A��r����Ƃ�����
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//�f�t�H���g�̏ꍇFALSE�ɂȂ��Ă��邩��TRUE�ɂ���
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//��r���@�i���傫���j�j

	//�|���S���̕`��
	for (int nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{//�������J�E���g
		if (g_Explosion[nCount].bUse == true)
		{//����������ꍇ

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Explosion[nCount].mtxWorldExplosion);

			//����
			pDevice->GetTransform
			(
				D3DTS_VIEW,
				&mtxView
			);

			//�t�s���ݒ�
			g_Explosion[nCount].mtxWorldExplosion._11 = mtxView._11;
			g_Explosion[nCount].mtxWorldExplosion._12 = mtxView._21;
			g_Explosion[nCount].mtxWorldExplosion._13 = mtxView._31;
			g_Explosion[nCount].mtxWorldExplosion._21 = mtxView._12;
			g_Explosion[nCount].mtxWorldExplosion._22 = mtxView._22;
			g_Explosion[nCount].mtxWorldExplosion._23 = mtxView._32;
			g_Explosion[nCount].mtxWorldExplosion._31 = mtxView._13;
			g_Explosion[nCount].mtxWorldExplosion._32 = mtxView._23;
			g_Explosion[nCount].mtxWorldExplosion._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Explosion[nCount].posExplosion.x, g_Explosion[nCount].posExplosion.y, g_Explosion[nCount].posExplosion.z);

			D3DXMatrixMultiply(&g_Explosion[nCount].mtxWorldExplosion, &g_Explosion[nCount].mtxWorldExplosion, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCount].mtxWorldExplosion);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureExplosion);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//�A���t�@�e�X�g����
	//�f�t�H���g�̏ꍇFALSE�ɂȂ��Ă��邩��TRUE�ɂ���
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//��r���@�i���傫���j�j

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		EXPLOSION_TEXTURE_NAME,
		&g_pTextureExplosion
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{//�S�J�E���g����
	 //���_��
		pVtx[0].pos = D3DXVECTOR3(-10, 10, 0);
		pVtx[1].pos = D3DXVECTOR3(10, 10, 0);
		pVtx[2].pos = D3DXVECTOR3(-10, -10, 0);
		pVtx[3].pos = D3DXVECTOR3(10, -10, 0);
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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
//=============================================================================
// �����̍쐬
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (int nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		if (g_Explosion[nCount].bUse == false)
		{
			g_Explosion[nCount].posExplosion = pos;			//pos�l���
			g_Explosion[nCount].rotExplosion = rot;			//rot�l���
			g_Explosion[nCount].nCounterAnim = 0;			//�J�E���^�[�����l�ݒ�
			g_Explosion[nCount].nPatteunAnim = 0;			//�p�^�[��No.�����l�ݒ�
			g_Explosion[nCount].bUse = true;				//�g�p���Ă����Ԃɂ���

			//�e�N�X�`���ݒ�
			pVtx[nCount * 4].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCount].nPatteunAnim, 0.0f);
			pVtx[nCount * 4 + 1].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCount].nPatteunAnim + EXPLOSION_TEXTURE_UV_U, 0.0f);
			pVtx[nCount * 4 + 2].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCount].nPatteunAnim, EXPLOSION_TEXTURE_UV_V);
			pVtx[nCount * 4 + 3].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCount].nPatteunAnim + EXPLOSION_TEXTURE_UV_U, EXPLOSION_TEXTURE_UV_V);

			//�e������
			//SetShadow(g_Explosion[nCount].posExplosion, g_Explosion[nCount].rotExplosion, 10.0f, 10.0f);
			break;
		}
	}
	//���_�o�b�t�@�̃A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
