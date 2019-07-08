//=============================================================================
//
// �|���S������ [billboord.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "billboord.h"		//�r���{�[�h
#include "shadow.h"			//�e
#include "bullet.h"			//�e
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BILLBOORD_TEXTURE_NAME		"data\\TEXTURE\\tree.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define BILLBOORD_TEXTURE_NAME1		"data\\TEXTURE\\tree000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define BILLBOORD_TEXTURE_NAME2		"data\\TEXTURE\\iwa.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define BILLBOORD_TEXTURE_NAME3		"data\\TEXTURE\\tree001.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define BILLBOORD_TEXTURE_NAME4		"data\\TEXTURE\\zonbi.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define BILLBOORD_TEXTURE_UV_U		(0.5f)							//�e�N�X�`���A�j���[�V����U�͈�
#define BILLBOORD_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�
#define BILLBOORD_TEXTURE_SPEED		(10)							//�e�N�X�`���A�j���[�V�����X�s�[�h
#define BILLBOORD_TEXTURE_PATTERN	(2)								//�e�N�X�`���A�j���[�V�����p�^�[����
#define BILLBOORD_ZONBI_WID			(20)							//�]���r�̕�
#define BILLBOORD_ZONBI_HEI			(50)							//�]���r�̍���
#define MAX_BILLBOORD				(2300)							//�r���{�[�h�̍ő吔
#define MAX_BILLBOORD_TEX			(5)								//�ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexBillBoord(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillBoord = NULL;						//���_�o�b�t�@
LPDIRECT3DTEXTURE9		g_pTextureBillBoord[MAX_BILLBOORD_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
BillBoord g_BillBoord[MAX_BILLBOORD];									//�r���{�[�h�̏��

//=============================================================================
// ����������
//=============================================================================
void InitBillBoord(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int nCount = 0; nCount < MAX_BILLBOORD; nCount++)
	{//�S�J�E���g����
		g_BillBoord[nCount].rotBillBoord = D3DXVECTOR3(0, 0, 0);	//����
		g_BillBoord[nCount].posBillBoord = D3DXVECTOR3(0, 0, 0);	//�ʒu
		g_BillBoord[nCount].nCounterAnim = 0;						//�J�E���^�[�����l�ݒ�
		g_BillBoord[nCount].nPatteunAnim = 0;						//�p�^�[��No.�����l�ݒ�
		g_BillBoord[nCount].bUse = false;							//�g�p���Ă��邩�ǂ���
	}

	//���_���
	MakeVertexBillBoord(pDevice);

}
//=============================================================================
// �I������
//=============================================================================
void UninitBillBoord(void)
{
	for (int nCount = 0; nCount < MAX_BILLBOORD_TEX; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureBillBoord[nCount] != NULL)
		{
			g_pTextureBillBoord[nCount] ->Release();
			g_pTextureBillBoord[nCount] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBillBoord != NULL)
	{
		g_pVtxBuffBillBoord->Release();
		g_pVtxBuffBillBoord = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBillBoord(void)
{
	////�f�o�C�X�|�C���^
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	////�e�̃|�C���^
	//Bullet *pBullet = GetBullet();

	////���_�o�b�t�@�����b�N
	//g_pVtxBuffBillBoord->Lock
	//(
	//	0,
	//	0,
	//	(void**)&pVtx,
	//	0
	//);

	//for (int nCount = 0; nCount < MAX_BILLBOORD; nCount++)
	//{
	//	if (g_BillBoord[nCount].bUse == true)
	//	{

	//		if (g_BillBoord[nCount].nType == 4)
	//		{
	//			g_BillBoord[nCount].nCounterAnim++;		//�J�E���^�[���Z
	//			//�e�����Ă���
	//			SetPositionShadow(g_BillBoord[nCount].nIdxShadow, g_BillBoord[nCount].posBillBoord, g_BillBoord[nCount].rotBillBoord);

	//			if ((g_BillBoord[nCount].nCounterAnim % BILLBOORD_TEXTURE_SPEED) == 0 && g_BillBoord[nCount].nType == 4)
	//			{//�A�j���[�V�������x                                                  ���p�^�[�����P�Âi��ł�����(�Q�ɂ���ƂQ���i��)
	//				g_BillBoord[nCount].nPatteunAnim = (g_BillBoord[nCount].nPatteunAnim + 1) % BILLBOORD_TEXTURE_PATTERN;		//�p�^�[��No.�X�V
	//																													//���_�ݒ�
	//				pVtx[nCount * 4].pos = D3DXVECTOR3(g_BillBoord[nCount].posBillBoord.x - BILLBOORD_ZONBI_WID, g_BillBoord[nCount].posBillBoord.y - BILLBOORD_ZONBI_HEI, 0.0f);
	//				pVtx[nCount * 4 + 1].pos = D3DXVECTOR3(g_BillBoord[nCount].posBillBoord.x + BILLBOORD_ZONBI_WID, g_BillBoord[nCount].posBillBoord.y - BILLBOORD_ZONBI_HEI, 0.0f);
	//				pVtx[nCount * 4 + 2].pos = D3DXVECTOR3(g_BillBoord[nCount].posBillBoord.x - BILLBOORD_ZONBI_WID, g_BillBoord[nCount].posBillBoord.y + BILLBOORD_ZONBI_HEI, 0.0f);
	//				pVtx[nCount * 4 + 3].pos = D3DXVECTOR3(g_BillBoord[nCount].posBillBoord.x + BILLBOORD_ZONBI_WID, g_BillBoord[nCount].posBillBoord.y + BILLBOORD_ZONBI_HEI, 0.0f);
	//				//���_�J���[�ݒ�
	//				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				//�e�N�X�`���ݒ�
	//				pVtx[nCount * 4].tex = D3DXVECTOR2(BILLBOORD_TEXTURE_UV_U * g_BillBoord[nCount].nPatteunAnim, 0.0f);
	//				pVtx[nCount * 4 + 1].tex = D3DXVECTOR2(BILLBOORD_TEXTURE_UV_U * g_BillBoord[nCount].nPatteunAnim + BILLBOORD_TEXTURE_UV_U, 0.0f);
	//				pVtx[nCount * 4 + 2].tex = D3DXVECTOR2(BILLBOORD_TEXTURE_UV_U * g_BillBoord[nCount].nPatteunAnim, BILLBOORD_TEXTURE_UV_V);
	//				pVtx[nCount * 4 + 3].tex = D3DXVECTOR2(BILLBOORD_TEXTURE_UV_U * g_BillBoord[nCount].nPatteunAnim + BILLBOORD_TEXTURE_UV_U, BILLBOORD_TEXTURE_UV_V);
	//			}
	//		}
	//	}
	//}
	////���_�o�b�t�@���A�����b�N
	//g_pVtxBuffBillBoord->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBillBoord(void)
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

	//�|���S���̕`��
	for (int nCount = 0; nCount < MAX_BILLBOORD; nCount++)
	{//�r���{�[�h���J�E���g
		if (g_BillBoord[nCount].bUse == true)
		{//�r���{�[�h������ꍇ

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_BillBoord[nCount].mtxWorldBillBoord);

			//�r���{�[�h
			pDevice->GetTransform
			(
				D3DTS_VIEW,
				&mtxView
			);

			//�t�s���ݒ�
			g_BillBoord[nCount].mtxWorldBillBoord._11 = mtxView._11;
			g_BillBoord[nCount].mtxWorldBillBoord._12 = mtxView._21;
			g_BillBoord[nCount].mtxWorldBillBoord._13 = mtxView._31;
			g_BillBoord[nCount].mtxWorldBillBoord._21 = mtxView._12;
			g_BillBoord[nCount].mtxWorldBillBoord._22 = mtxView._22;
			g_BillBoord[nCount].mtxWorldBillBoord._23 = mtxView._32;
			g_BillBoord[nCount].mtxWorldBillBoord._31 = mtxView._13;
			g_BillBoord[nCount].mtxWorldBillBoord._32 = mtxView._23;
			g_BillBoord[nCount].mtxWorldBillBoord._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_BillBoord[nCount].posBillBoord.x, g_BillBoord[nCount].posBillBoord.y, g_BillBoord[nCount].posBillBoord.z);

			D3DXMatrixMultiply(&g_BillBoord[nCount].mtxWorldBillBoord, &g_BillBoord[nCount].mtxWorldBillBoord, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_BillBoord[nCount].mtxWorldBillBoord);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillBoord, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBillBoord[g_BillBoord[nCount].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
	//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexBillBoord(LPDIRECT3DDEVICE9 pDevice)
{
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P����
		pDevice,
		BILLBOORD_TEXTURE_NAME,
		&g_pTextureBillBoord[0]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�Q����
		pDevice,
		BILLBOORD_TEXTURE_NAME1,
		&g_pTextureBillBoord[1]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�R����
		pDevice,
		BILLBOORD_TEXTURE_NAME2,
		&g_pTextureBillBoord[2]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�S����
		pDevice,
		BILLBOORD_TEXTURE_NAME3,
		&g_pTextureBillBoord[3]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�T����
		pDevice,
		BILLBOORD_TEXTURE_NAME4,
		&g_pTextureBillBoord[4]
	);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_BILLBOORD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillBoord,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBillBoord->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_BILLBOORD; nCount++)
	{//�S�J�E���g����
	 //���_��
		pVtx[0].pos = D3DXVECTOR3(-10, 30, 0);
		pVtx[1].pos = D3DXVECTOR3(10, 30, 0);
		pVtx[2].pos = D3DXVECTOR3(-10, 0, 0);
		pVtx[3].pos = D3DXVECTOR3(10, 0, 0);

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
	g_pVtxBuffBillBoord->Unlock();
}
//=============================================================================
// �r���{�[�h�̍쐬
//=============================================================================
void SetBillBoord(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nType)
{
	for (int nCount = 0; nCount < MAX_BILLBOORD; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		if (g_BillBoord[nCount].bUse == false)
		{
			g_BillBoord[nCount].posBillBoord = pos;			//pos�l���
			g_BillBoord[nCount].rotBillBoord = rot;			//rot�l���
			g_BillBoord[nCount].nCounterAnim = 0;			//�J�E���^�[�����l�ݒ�
			g_BillBoord[nCount].nPatteunAnim = 0;			//�p�^�[��No.�����l�ݒ�
			g_BillBoord[nCount].nType = nType;				//��ނ���
			g_BillBoord[nCount].bUse = true;				//�g�p���Ă����Ԃɂ���

			if (g_BillBoord[nCount].nType !=4)
			{
				//�e������
				SetShadow(g_BillBoord[nCount].posBillBoord, g_BillBoord[nCount].rotBillBoord, 10.0f, 10.0f);

			}
			break;
		}
	}
}
//=========================================================================================================================
// �����r���{�[�h
//=========================================================================================================================
void DeleteBillBoord(int nCntBillBoord)
{
	if (g_BillBoord[nCntBillBoord].nType == 4)
	{
		//�g�p���Ă��Ȃ����
		g_BillBoord[nCntBillBoord].bUse = false;

		//�g���Ă���e��false
		DeleteShadow(g_BillBoord[nCntBillBoord].nIdxShadow);
	}
}
//=========================================================================================================================
// �r���{�[�h�̂����蔻��
//=========================================================================================================================
void CollisionBillBoord(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove)
{
	//�J�E���g
	int nCount = 0;

	//�J�E���g
	int nCntBillBoord;

	//�e�̃|�C���^
	Bullet *pBullet = GetBullet();



	for (int nCntBullet = 0; nCntBullet < 300; nCntBullet++)
	{
		if (pBullet[nCntBullet].bUse == true)
		{
			for (nCntBillBoord = 0; nCntBillBoord < MAX_BILLBOORD; nCntBillBoord++)
			{//�A�C�e�����J�E���g
				if (g_BillBoord[nCntBillBoord].bUse == true)
				{
					if (pBullet[nCntBullet].posBullet.y - 2 < g_BillBoord[nCntBillBoord].posBillBoord.y + 30 && pBullet[nCntBullet].posBullet.y > g_BillBoord[nCntBillBoord].posBillBoord.y)
					{//�����蔻��
						if (pBullet[nCntBullet].posBullet.x + 2 >= g_BillBoord[nCntBillBoord].posBillBoord.x - 15 && pBullet[nCntBullet].posBullet.x - 2 <= g_BillBoord[nCntBillBoord].posBillBoord.x + 15 && pBullet[nCntBullet].posBullet.z + 2 >= g_BillBoord[nCntBillBoord].posBillBoord.z - 15 && pBullet[nCntBullet].posBullet.z - 2 <= g_BillBoord[nCntBillBoord].posBillBoord.z + 15)
						{
							DeleteBillBoord(nCntBillBoord);
						}

					}
				}
			}
		}
	}
}
